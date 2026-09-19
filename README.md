# T.O.G.O. remake
自己満リファクタリング by Tomoooji

---

```
TOGO_remake/
├─ include/                        # ヘッダーファイルフォルダ
│  ├─ Components.h
│  ├─ GainConfig.h
│  ├─ LinearActuator.cpp
│  ├─ LinearActuator.h
│  ├─ PinConfig.h
│  ├─ README
│  ├─ RotaryActuator.cpp
│  └─ RotaryActuator.h
├─ lib/                             # ライブラリフォルダ(ほぼ自作)
│  ├─ ESP32Stepper/                 # ESP32用ステッピングモータ制御ライブラリ
│  │  ├─ ESP32Stepper.cpp
│  │  └─ ESP32Stepper.h
│  ├─ PCA9685/                      # PCA9685用I2C制御ライブラリ(秋月電子製)
│  │  ├─ examples/
│  │  │  └─ PCA9685_Sample/
│  │  │     └─ PCA9685_Sample.ino
│  │  ├─ PCA9685.cpp
│  │  ├─ PCA9685.h
│  │  └─ readme.txt
│  ├─ PCAMotor/                     # PCA9685用モータ制御ライブラリ
│  │  ├─ PCAMotor.cpp
│  │  └─ PCAMotor.h
│  ├─ PCAServo/                     # PCA9685用サーボモータ制御ライブラリ
│  │  ├─ PCAServo.cpp
│  │  └─ PCAServo.h
│  ├─ PID/                          # PID制御用ライブラリ
│  │  ├─ PID.cpp
│  │  └─ PID.h
│  ├─ UltraSonic/                   # 超音波センサ用ライブラリ
│  │  ├─ UltraSonic.cpp
│  │  └─ UltraSonic.h
│  └─ README
├─ src/                             # メインのコード(動作確認用含む)
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

class PCA9685
class PCAMotor
class PCAServo
class Stepper
class HCSR04
class ESP32Encoder
class PID

class LinearActuator
class RotaryActuator

class BaseRotate {
    PCAMotor dcMotor
    ESP32Encoder encoder
    PID pid
}

class BaseExpand {
    PCAMotor dcMotor
    HCSR04 ultrasonic
    PID pid
}

class BaseLift {
    PCAMotor dcMotor
    HCSR04 ultrasonic
    PID pid
}

class Hand {
    PCAServo svCatch1
    PCAServo svCatch2
    PCAServo svCatch3
    Stepper stRotate
    Stepper stExpand
}

class SortSlide {
    PCAMotor dcMotor
    HCSR04 ultrasonic
    PID pid
}

class SortGate {
    PCAServo svLeft
    PCAServo svRight
}

BaseRotate *-- PCAMotor
BaseRotate *-- ESP32Encoder
BaseRotate *-- PID

BaseExpand *-- PCAMotor
BaseExpand *-- HCSR04
BaseExpand *-- PID

BaseLift *-- PCAMotor
BaseLift *-- HCSR04
BaseLift *-- PID

Hand *-- PCAServo
Hand *-- Stepper

SortSlide *-- PCAMotor
SortSlide *-- HCSR04
SortSlide *-- PID

SortGate *-- PCAServo

LinearActuator --> PCAMotor
LinearActuator --> HCSR04
LinearActuator --> PID

RotaryActuator --> PCAMotor
RotaryActuator --> ESP32Encoder
RotaryActuator --> PID

BaseRotate --> RotaryActuator
BaseExpand --> LinearActuator
BaseLift --> LinearActuator
SortSlide --> LinearActuator
```