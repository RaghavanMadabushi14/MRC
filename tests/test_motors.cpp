// Host-side tests for MRC motor control and command decoding.
// Build and run with tests/run_tests.sh (expects -DMOTOR_MIN_PWM=60).
#include <cstdio>
#include <string>

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include "../MRC/include/Pin_assignments.h"
#include "../MRC/include/Hardware.h"
#include "../MRC/include/MotorControls.h"
#include "../MRC/include/CommandDecodeExecute.h"

static int failures = 0;
static int checks = 0;

#define CHECK_EQ(actual, expected) do { \
    checks++; \
    auto a_ = (actual); auto e_ = (expected); \
    if (!(a_ == e_)) { \
        failures++; \
        std::printf("FAIL %s:%d  %s == %s\n", __FILE__, __LINE__, #actual, #expected); \
    } \
} while (0)

#define CHECK_STR(actual, expected) CHECK_EQ(std::string((actual).c_str()), std::string(expected))

static Motors Left, Right;
static Servo servoA, servoB;
static SoftwareSerial bt(BLUETOOTH_RX, BLUETOOTH_TX);

static void setUp(){
    fakeResetPins();
    servoA = Servo();
    servoB = Servo();
    bt.lastReply = String();
    bt.replyCount = 0;
    Init_Hardware(&Right, &Left, &servoA, &servoB, &bt);
}

static void expectSide(const Motors& m, int in13, int in24, int en){
    CHECK_EQ(fakeDigital[m.IN13], in13);
    CHECK_EQ(fakeDigital[m.IN24], in24);
    CHECK_EQ(fakeAnalog[m.EN], en);
}

static void send(const char* cmd){
    Command_Decode_Execute(String(cmd), &servoA, &servoB, &Left, &Right, &bt);
}

// ---------------- hardware init ----------------
static void test_init_hardware(){
    setUp();
    CHECK_EQ(Left.IN13, LEFT_MOTORS_IN13);
    CHECK_EQ(Left.IN24, LEFT_MOTORS_IN24);
    CHECK_EQ(Left.EN, EN_MOTORS_LEFT);
    CHECK_EQ(Right.IN13, RIGHT_MOTORS_IN13);
    CHECK_EQ(Right.IN24, RIGHT_MOTORS_IN24);
    CHECK_EQ(Right.EN, EN_MOTORS_RIGHT);
    CHECK_EQ(fakePinMode[EN_MOTORS_LEFT], OUTPUT);
    CHECK_EQ(fakePinMode[EN_MOTORS_RIGHT], OUTPUT);
    CHECK_EQ(servoA.attachedPin, SERVO_1);
    CHECK_EQ(servoB.attachedPin, SERVO_2);
    CHECK_EQ(bt.baud, 9600L);
}

// ---------------- Motors_Drive / Stop / Tank ----------------
static void test_drive_forward(){
    setUp();
    Motors_Drive(&Left, 150, false);
    expectSide(Left, HIGH, LOW, 150);
}

static void test_drive_reverse(){
    setUp();
    Motors_Drive(&Right, -150, false);
    expectSide(Right, LOW, HIGH, 150);
}

static void test_drive_zero_stops(){
    setUp();
    Motors_Drive(&Left, 200, false);
    Motors_Drive(&Left, 0, false);
    expectSide(Left, LOW, LOW, 0);
}

static void test_drive_clamps(){
    setUp();
    Motors_Drive(&Left, 300, false);
    expectSide(Left, HIGH, LOW, 255);
    Motors_Drive(&Left, -300, false);
    expectSide(Left, LOW, HIGH, 255);
}

static void test_drive_deadband(){
    setUp();
    Motors_Drive(&Left, 20, false);
    expectSide(Left, HIGH, LOW, MOTOR_MIN_PWM);
    Motors_Drive(&Left, -1, false);
    expectSide(Left, LOW, HIGH, MOTOR_MIN_PWM);
    Motors_Drive(&Left, MOTOR_MIN_PWM + 1, false);
    expectSide(Left, HIGH, LOW, MOTOR_MIN_PWM + 1);
}

static void test_drive_polarity_flip(){
    setUp();
    Motors_Drive(&Left, 150, true);
    expectSide(Left, LOW, HIGH, 150);
    Motors_Drive(&Left, -150, true);
    expectSide(Left, HIGH, LOW, 150);
}

static void test_stop(){
    setUp();
    Motors_Drive(&Right, 255, false);
    Motors_Stop(&Right);
    expectSide(Right, LOW, LOW, 0);
}

static void test_tank_pivot(){
    setUp();
    Motors_Tank(&Left, &Right, 120, -120);
    expectSide(Left, HIGH, LOW, 120);
    expectSide(Right, LOW, HIGH, 120);
}

// ---------------- command decoding ----------------
static void test_cmd_move_both(){
    setUp();
    send("move both 150");
    expectSide(Left, HIGH, LOW, 150);
    expectSide(Right, HIGH, LOW, 150);
    CHECK_STR(bt.lastReply, "OK both 150");
}

static void test_cmd_move_both_reverse(){
    setUp();
    send("move both -150");
    expectSide(Left, LOW, HIGH, 150);
    expectSide(Right, LOW, HIGH, 150);
    CHECK_STR(bt.lastReply, "OK both -150");
}

static void test_cmd_move_left_only(){
    setUp();
    send("move left 100");
    expectSide(Left, HIGH, LOW, 100);
    CHECK_EQ(fakeAnalog[Right.EN], -1);   // right side untouched
    CHECK_STR(bt.lastReply, "OK left 100");
}

static void test_cmd_move_right_only(){
    setUp();
    send("move right -90");
    expectSide(Right, LOW, HIGH, 90);
    CHECK_EQ(fakeAnalog[Left.EN], -1);
    CHECK_STR(bt.lastReply, "OK right -90");
}

static void test_cmd_spin(){
    setUp();
    send("move spin 130");
    expectSide(Left, HIGH, LOW, 130);
    expectSide(Right, LOW, HIGH, 130);
    CHECK_STR(bt.lastReply, "OK spin 130");
}

static void test_cmd_stop(){
    setUp();
    send("move both 200");
    send("move stop");
    expectSide(Left, LOW, LOW, 0);
    expectSide(Right, LOW, LOW, 0);
    CHECK_STR(bt.lastReply, "OK stop");
}

static void test_cmd_carriage_return_and_case(){
    setUp();
    send("  MOVE Both 150\r");
    expectSide(Left, HIGH, LOW, 150);
    expectSide(Right, HIGH, LOW, 150);
    CHECK_STR(bt.lastReply, "OK both 150");
}

static void test_cmd_non_numeric_value_stops(){
    setUp();
    send("move both 200");
    send("move both fast");
    expectSide(Left, LOW, LOW, 0);
    expectSide(Right, LOW, LOW, 0);
    CHECK_STR(bt.lastReply, "OK both 0");
}

static void test_cmd_too_many_words(){
    setUp();
    send("move both 150 extra");
    CHECK_EQ(fakeAnalog[Left.EN], -1);
    CHECK_EQ(fakeAnalog[Right.EN], -1);
    CHECK_STR(bt.lastReply, "Invalid command: Enter only 3 words");
}

static void test_cmd_single_word_rejected(){
    setUp();
    send("move");
    CHECK_EQ(fakeAnalog[Left.EN], -1);
    CHECK_STR(bt.lastReply, "Invalid command: Enter 2 or 3 words");
}

static void test_cmd_bad_side(){
    setUp();
    send("move middle 150");
    CHECK_EQ(fakeAnalog[Left.EN], -1);
    CHECK_STR(bt.lastReply, "Motor(s) not detected");
}

static void test_cmd_empty(){
    setUp();
    send("");
    send(" \r\n");
    CHECK_EQ(bt.replyCount, 0);
}

static void test_cmd_bad_device(){
    setUp();
    send("fly up 10");
    CHECK_STR(bt.lastReply, "Device type not detected");
}

static void test_cmd_servos(){
    setUp();
    send("servo bottom 45");
    CHECK_EQ(servoA.lastAngle, 45);
    send("servo top 120");
    CHECK_EQ(servoB.lastAngle, 120);
    send("servo side 10");
    CHECK_STR(bt.lastReply, "Servo not detected");
}

int main(){
    test_init_hardware();
    test_drive_forward();
    test_drive_reverse();
    test_drive_zero_stops();
    test_drive_clamps();
    test_drive_deadband();
    test_drive_polarity_flip();
    test_stop();
    test_tank_pivot();
    test_cmd_move_both();
    test_cmd_move_both_reverse();
    test_cmd_move_left_only();
    test_cmd_move_right_only();
    test_cmd_spin();
    test_cmd_stop();
    test_cmd_carriage_return_and_case();
    test_cmd_non_numeric_value_stops();
    test_cmd_too_many_words();
    test_cmd_single_word_rejected();
    test_cmd_bad_side();
    test_cmd_empty();
    test_cmd_bad_device();
    test_cmd_servos();

    std::printf("%d checks, %d failures\n", checks, failures);
    return failures == 0 ? 0 : 1;
}
