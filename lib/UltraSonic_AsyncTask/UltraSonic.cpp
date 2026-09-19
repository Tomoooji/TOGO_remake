#include "UltraSonic.h"

HCSR04::HCSR04(const int send_pulse_length, const int send_span_min, const int read_timeout)
    : send_pulse_length(send_pulse_length), send_span_min(send_span_min),
      read_timeout(read_timeout), distance(0.0f) {};

void HCSR04::begin(const uint8_t *trigPin, const uint8_t *echoPin) {
  this->pin_trig = trigPin;
  this->pin_echo = echoPin;
  pinMode(*this->pin_trig, OUTPUT);
  digitalWrite(*(this->pin_trig), LOW);
  pinMode(*(this->pin_echo), INPUT);
  xTaskCreatePinnedToCore(task_starter, "HCSR04_Task", 2048, this, 1, &taskHandle, 0);
}

void HCSR04::read() {
  digitalWrite(*this->pin_trig, HIGH);
  delayMicroseconds(this->send_pulse_length);
  digitalWrite(*this->pin_trig, LOW);
  unsigned long pulse = pulseIn(*this->pin_echo, HIGH, this->read_timeout * 1000);
  this->distance.store(pulse > 0 ? this->calcDistance(pulse) : -1.0f);
}