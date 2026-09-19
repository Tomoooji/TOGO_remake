#include "UltraSonic.h"

void HCSR04::task_starter(void *arg) {
  HCSR04 *self = static_cast<HCSR04 *>(arg);
  for (;;) {
    self->read();
    vTaskDelay(pdMS_TO_TICKS(self->send_span_min));
  }
}

HCSR04::HCSR04(const uint8_t &pin_trig, const uint8_t &pin_echo, const int send_pulse_length, const int send_span_min, const int read_timeout)
    : pin_trig(pin_trig), pin_echo(pin_echo), send_pulse_length(send_pulse_length), send_span_min(send_span_min),
      read_timeout(read_timeout), distance(0.0f) {};

HCSR04::HCSR04(const uint8_t (&pins)[2], const int send_pulse_length, const int send_span_min, const int read_timeout)
    : HCSR04(pins[0], pins[1], send_pulse_length, send_span_min, read_timeout) {}
    
void HCSR04::begin() {
  pinMode(this->pin_trig, OUTPUT);
  digitalWrite(this->pin_trig, LOW);
  pinMode(this->pin_echo, INPUT);
  xTaskCreatePinnedToCore(task_starter, "HCSR04_Task", 2048, this, 1, &taskHandle, 0);
}

void HCSR04::read() {
  digitalWrite(this->pin_trig, HIGH);
  delayMicroseconds(this->send_pulse_length);
  digitalWrite(this->pin_trig, LOW);
  unsigned long pulse = pulseIn(this->pin_echo, HIGH, this->read_timeout * 1000);
  this->distance.store(pulse > 0 ? this->calcDistance(pulse) : -1.0f);
}