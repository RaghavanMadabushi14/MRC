// Host-side stand-in for the Arduino core. Records the last value written to each pin
// so tests can assert exact pin states. Not compiled into the firmware.
#pragma once

#include <cctype>
#include <cstdlib>
#include <string>

#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define INPUT 0

#define FAKE_NUM_PINS 20

inline int fakePinMode[FAKE_NUM_PINS];
inline int fakeDigital[FAKE_NUM_PINS];
inline int fakeAnalog[FAKE_NUM_PINS];

inline void fakeResetPins(){
    for (int i = 0; i < FAKE_NUM_PINS; i++){
        fakePinMode[i] = -1;
        fakeDigital[i] = -1;
        fakeAnalog[i] = -1;
    }
}

inline void pinMode(int pin, int mode){ fakePinMode[pin] = mode; }
inline void digitalWrite(int pin, int value){ fakeDigital[pin] = value; }
inline void analogWrite(int pin, int value){ fakeAnalog[pin] = value; }

class String {
public:
    String() {}
    String(const char* s) : s_(s) {}
    String(const std::string& s) : s_(s) {}
    explicit String(int v) : s_(std::to_string(v)) {}

    unsigned int length() const { return s_.length(); }
    char charAt(unsigned int i) const { return i < s_.length() ? s_[i] : 0; }

    String substring(unsigned int from) const {
        return from >= s_.length() ? String() : String(s_.substr(from));
    }
    String substring(unsigned int from, unsigned int to) const {
        if (from > to){ unsigned int t = from; from = to; to = t; }
        if (from >= s_.length()) return String();
        return String(s_.substr(from, to - from));
    }

    // Arduino's toInt() is atol(): leading number only, 0 if not numeric
    long toInt() const { return std::atol(s_.c_str()); }

    void trim(){
        size_t b = 0, e = s_.length();
        while (b < e && std::isspace((unsigned char)s_[b])) b++;
        while (e > b && std::isspace((unsigned char)s_[e - 1])) e--;
        s_ = s_.substr(b, e - b);
    }
    void toLowerCase(){
        for (char& c : s_) c = (char)std::tolower((unsigned char)c);
    }

    bool operator==(const char* o) const { return s_ == o; }
    bool operator==(const String& o) const { return s_ == o.s_; }

    friend String operator+(const char* a, const String& b){ return String(std::string(a) + b.s_); }
    friend String operator+(const String& a, const String& b){ return String(a.s_ + b.s_); }

    const char* c_str() const { return s_.c_str(); }

private:
    std::string s_;
};
