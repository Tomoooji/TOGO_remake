#pragma once
#include <Arduino.h>

constexpr int SONIC_SPEED = 340;

class HCSR04{
  private:
    const uint8_t* pin_trig;
    const uint8_t* pin_echo;
    const int send_pulse_length;//[microsec]
    const int send_span_min;//[millisec]
    const int read_timeout; //[millisec]
    unsigned long last_send_time;
    unsigned long pulse;
    enum {READY,WAITING,READING} status;
    float distance;

  public:
    HCSR04(const int send_pulse_length = 10/*microsec*/, const int send_span_min = 200/*millisec*/, const int read_timeout = 1000/*millisec*/);
    void begin(const uint8_t* trigPin, const uint8_t* echoPin);
    void begin(const uint8_t *pin);
    void update();
    const float getDistance() const{
      return this->distance;
    }
    static float calcDistance(unsigned long pulseWidth){
      return SONIC_SPEED/2*pulseWidth*0.0001;
    }
  private:
    void sendTrigPulse();
    static void IRAM_ATTR readPulseISR(void* arg);
};