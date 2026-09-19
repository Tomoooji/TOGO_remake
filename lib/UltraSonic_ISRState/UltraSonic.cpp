#if 0
#include "UltraSonic.h"

HCSR04::HCSR04(const int send_pulse_length, const int send_span_min, const int read_timeout)
    : send_pulse_length(send_pulse_length), send_span_min(send_span_min),
      read_timeout(read_timeout), distance(0.0f) {};

void HCSR04::begin(const uint8_t *trigPin, const uint8_t *echoPin) {
  this->pin_trig = trigPin;
  this->pin_echo = echoPin;
  pinMode(*this->pin_trig, OUTPUT);
  digitalWrite(*this->pin_trig, LOW);
  pinMode(*this->pin_echo, INPUT);
  this->last_send_time = 0;
  this->status = HCSR04::READY;
  attachInterruptArg(digitalPinToInterrupt(*this->pin_echo),
                     readPulseISR, this, CHANGE);
}

void HCSR04::begin(const uint8_t *pin) { this->begin(&pin[0], &pin[1]); }

void HCSR04::sendTrigPulse() {
  digitalWrite(*this->pin_trig, HIGH);
  delayMicroseconds(this->send_pulse_length);
  digitalWrite(*this->pin_trig, LOW);
  this->last_send_time = millis();
}

void HCSR04::update() {
  if (this->status == HCSR04::WAITING &&
      millis() - this->last_send_time > this->read_timeout) {
    // timeout
    this->status = HCSR04::READY;
    this->last_send_time = 0;
    this->pulse = 0;
  }
  if (this->status == HCSR04::READY) {
    // ここでこれをやると応答がpulse_span_minより先に返ってきた後の待ってる状態の時に不要な計算が挟まる...
    // ただisrにdistanceをいじらせたくないしcalcDistanceが重たい処理になるかもしれない...
    // statusいじらせてる時点でミューテックス系の処置をするのは変わらんのか？
    if (pulse > 0)
      this->distance = this->calcDistance(this->pulse);

    // 応答pulseとsend_span_minを待ってから再送
    if (millis() - this->last_send_time >= this->send_span_min) {
      this->sendTrigPulse();
      this->status = HCSR04::WAITING;
    }
  }
}

void IRAM_ATTR HCSR04::readPulseISR(void *arg) {
  HCSR04 *self = static_cast<HCSR04 *>(arg);
  if (digitalRead(*self->pin_echo) == HIGH) {
    if (self->status == HCSR04::WAITING) {
      self->pulse = micros();
      self->status = HCSR04::READING;
    }
  } else {
    if (self->status == HCSR04::READING) {
      unsigned long now = micros();
      self->pulse = now > self->pulse ? now - self->pulse
                                      : (2 << 32) - 1 - self->pulse + now;
      self->status = HCSR04::READY;
    }
  }
}
#endif