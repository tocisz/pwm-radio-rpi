#include "rpiPWM1.h"

#include <sstream>
#include <string>
#include <iostream>

#include <cctype>

const long frameTime = 100000;
void send(rpiPWM1 &pwm, char c);

class sender {
public:
  sender() : pwm(1000.0, 256, 100.0/12, rpiPWM1::MSMODE) {}

  void begin();
  void send(char c);
  void idle();

private:
  rpiPWM1 pwm;

  unsigned char last_nibble;

  void send1(unsigned char c);
  void send2(unsigned char c);
};

int main(int argc, char *args[]) {

  std::string line;
  sender s;

  while (std::getline(std::cin, line))
  {
     s.begin();
     for (std::string::iterator p = line.begin(); line.end() != p; ++p) {
       char c = toupper(*p);
       if (c >= 32 && c < 96) {
         std::cout << c << std::flush;

         s.send(c-32);
       }
     }
     s.idle();
     std::cout << std::endl;
  }

  return 0;
}

void sender::begin() {
  send1(0);
  send1(7);
}

void sender::send(char c) {
  unsigned char b1 = c & 0b111;
  unsigned char b2 = (c >> 3) & 0b111;
  send1(b2);
  send1(b1);
}

void sender::send1(unsigned char c) {
  send2(0);
  usleep(3*frameTime);
  send2(c+1);
  usleep(3*frameTime);
}

void sender::send2(unsigned char c) {
  pwm.setDutyCycle((2+c)*100.0/12);
}

void sender::idle() {
  pwm.setDutyCycle(100.0/12);
}
