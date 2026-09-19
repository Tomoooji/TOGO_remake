#pragma once

#include <Arduino.h>
#include <atomic>

constexpr int SONIC_SPEED = 340;

class HCSR04 {
private:
  const uint8_t &pin_trig;
  const uint8_t &pin_echo;
  const int send_pulse_length; //[microsec]
  const int send_span_min;     //[millisec]
  const int read_timeout;      //[millisec]
  TaskHandle_t taskHandle;
  std::atomic<float> distance{0.0f};

  static void task_starter(void *arg);

public:
  HCSR04(const uint8_t &pin_trig, const uint8_t &pin_echo,
         const int send_pulse_length = 10 /*microsec*/,
         const int send_span_min = 200 /*millisec*/,
         const int read_timeout = 1000 /*millisec*/);
  HCSR04(const uint8_t (&pins)[2],
         const int send_pulse_length = 10 /*microsec*/,
         const int send_span_min = 200 /*millisec*/,
         const int read_timeout = 1000 /*millisec*/);

  void begin();
  void read();
  const float getDistance() const { return this->distance.load(); }
  static float calcDistance(unsigned long pulseWidth) {
    return SONIC_SPEED / 2 * pulseWidth * 0.0001;
  }
};