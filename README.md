# T.O.G.O. remake
自己満リファクタリング by Tomoooji

---

```
TOGO_remake/
├─ include/                        # ヘッダーファイルフォルダ
│  ├─ Components.h
│  ├─ GainConfig.h
│  ├─ PinConfig.h
│  └─ README
├─ lib/                             # ライブラリフォルダ(ほぼ自作)
│  ├─ ESP32Stepper/                 # ESP32用ステッピングモータ制御ライブラリ
│  │  ├─ ESP32Stepper.cpp
│  │  └─ ESP32Stepper.h
│  ├─ PID/                          # PID制御用ライブラリ
│  │  ├─ PID.cpp
│  │  └─ PID.h
│  ├─ LinearActuator/               # 直動機構(DCモーター+超音波センサ)用ライブラリ
│  │  ├─ LinearActuator.cpp
│  │  └─ LinearActuator.h
│  ├─ RotaryActuator/               # 回転機構(DCモーター+エンコーダ)用ライブラリ
│  │  ├─ RotaryActuator.cpp
│  │  └─ RotaryActuator.h
│  └─ README
├─ src/                             # メインのコードフォルダ(動作確認用含む)
│  ├─ check_linear_actuator.cpp
│  ├─ check_rotary_actuator.cpp
│  ├─ check_ultrasonic.cpp
│  └─ main.cpp
├─ test/                            # 使ってない(そもそもテストなんて文化しらない)
│  └─ README
├─ platformio.ini
└─ README.md
```

# クラス図
```mermaid
classDiagram
%% =========================
%% Component
%% =========================

class Hand {
    +PCAServo svLeft
    +PCAServo svMiddle
    +PCAServo svRight
    +Stepper stRotate
    +Stepper stExpand
}

class SortGate {
    +PCAServo svLeft
    +PCAServo svRight
}


%% =========================
%% Mechanism
%% =========================

class LinearActuator {
    -PCAMotor motor
    -HCSR04Async ultrasonic
    -PID pid
    -float targetDistance
    -float sensor_position_offset
    -float min_distance_error
    +begin()
    +update() bool
    +setTargetDistance(float)
    +getTargetDistance() float
    +getCurrentDistance() float
}

class RotaryActuator {
    -PCAMotor motor
    -ESP32Encoder encoder
    -PID pid
    -float targetAngle
    -float encoder_gear_ratio
    -float angle_cash
    +begin()
    +update()
    +setTargetAngle(float)
    +getCurrentAngle() float
    +getTargetAngle() float
}


%% =========================
%% Motor / Sensor
%% =========================

class PCAMotor {
}

class PCAServo {
}

class Stepper {
    -uint8_t pins
    -float gear_ratio
}

class HCSR04Async {
    -float distance
    +begin()
    +read()
    +getDistance() float
}

class ESP32Encoder {
    +attachFullQuad()
    +clearCount()
    +getCount() int
}

class PID {
    -float target
    +setTarget(float)
    +reset()
    +update(float) float
}

class PCA9685 {
}


%% =========================
%% Math
%% =========================

class RadianAbsPi {
}


%% =========================
%% Relationships
%% =========================

Hand *-- PCAServo : svLeft
Hand *-- PCAServo : svMiddle
Hand *-- PCAServo : svRight
Hand *-- Stepper : stRotate
Hand *-- Stepper : stExpand

SortGate *-- PCAServo : svLeft
SortGate *-- PCAServo : svRight

LinearActuator *-- PCAMotor : motor
LinearActuator *-- HCSR04Async : ultrasonic
LinearActuator *-- PID : pid

RotaryActuator *-- PCAMotor : motor
RotaryActuator *-- ESP32Encoder : encoder
RotaryActuator *-- PID : pid

PCAServo --> PCA9685
PCAMotor --> PCA9685

RotaryActuator --> RadianAbsPi
```