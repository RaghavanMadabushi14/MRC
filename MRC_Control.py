import serial
import time
ser = serial.Serial("/dev/cu.team3Module", 9600, timeout=2)
print(f"Connected to {ser.port}")
# HC-06 link needs a moment after the port opens before data flows reliably
time.sleep(2)
try:
    ser.reset_input_buffer()
    while True:
        print("-" * 30)
        command = input("Enter command to send (or 'quit' to exit): ")
        if command.lower() == 'quit':
            break
        command_with_newline = command + '\n'
        ser.write(command_with_newline.encode('utf-8'))
        response_bytes = ser.readline()
        if response_bytes:
            response = response_bytes.decode('utf-8')
            print(f"Received: {response}")
        else:
            print("Received no response within the timeout period.")
except KeyboardInterrupt:
    print("Exiting.")
finally:
    ser.close()
    print("Serial port closed.")