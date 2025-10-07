# Wall-E-Robot
Life-size WALL·E robot controlled with Arduino Mega and FlySky transmitter. Uses Adafruit PCA9685 servo driver to move head, arms, and eyes. Includes DC motor drive, smooth servo motion, and control via 10 RC channels for realistic robot animation and movement.

# 🤖 Life-Size WALL·E Robot – Arduino Mega + FlySky Controller

This project brings **Pixar’s WALL·E** to life — a full-size robot replica controlled wirelessly using an **Arduino Mega 2560** and a **FlySky FS-i6 transmitter**.  
The robot can move, rotate, lift arms, blink eyes, and move its head using servo motors and DC motor control.

![WALL-E](https://upload.wikimedia.org/wikipedia/en/5/58/WALL-E_character.jpg)

---

## 🧠 Features

- Fully functional **WALL·E** replica, controlled via FlySky RC transmitter  
- **Adafruit PCA9685 16-channel servo driver** for smooth servo control  
- **Dual DC motors** for movement (tank-style control)  
- **Head, arm, hand, and eyebrow servos** for expressive animations  
- Adjustable **motor speed** and **turning sensitivity** via transmitter potentiometers  
- Smooth input filtering to prevent servo jitter  
- Safety **Stop / Play / Pause / Light** control buttons  

---

## 🧩 Hardware Used

| Component | Description |
|------------|-------------|
| **Arduino Mega 2560** | Main controller |
| **Adafruit PCA9685 Servo Driver** | 16-channel PWM driver (I²C) |
| **Dual H-Bridge Motor Driver** | Controls DC drive motors |
| **FlySky FS-i6 Transmitter + Receiver** | 10-channel RC control |
| **DC Motors** | Left/right drive motors |
| **Servos** | Head, arms, hands, eyebrows |
| **Custom Buttons** | Stop, Play, Pause, Lights |

---

## ⚙️ Wiring Overview

- PCA9685 connected to Arduino via **I²C (SDA/SCL)**  
- RC receiver channels connected to Arduino **digital pins 23–41**  
- Motor driver connected via **pins 22–28**  
- Control buttons (Stop, Play, Pause, Light) on **pins 30–36**  

You can modify pin assignments inside the code for your setup.

---

## 📦 Required Libraries

Install the following Arduino libraries:

1. **Adafruit PWM Servo Driver Library**  
   📥 [Download here](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)  
   *(Use Arduino Library Manager → “Adafruit PWM Servo Driver”)*

2. **Wire.h** *(included by default in Arduino IDE)*

---

## 🚀 Uploading the Code

1. Open the `.ino` file in **Arduino IDE**  
2. Select **Board:** “Arduino Mega 2560”  
3. Select the correct **Port**  
4. Click **Upload** and enjoy controlling your WALL·E! 🦾  

---

## 🎮 Controls (Example Mapping)

| Channel | Function |
|----------|-----------|
| CH1 | Left/Right turning |
| CH2 | Forward/Backward |
| CH3 | Head vertical movement |
| CH4 | Head horizontal movement |
| CH5 | Activation toggle |
| CH6 | Eyebrow animation |
| CH7 / CH8 | Potentiometers (speed tuning) |
| CH9 / CH10 | Reserved for future functions |

---

## 🧠 Code Highlights


### Dual motor control with differential drive:
```cpp
motor(greitis - apsisukimo_greitis, greitis + apsisukimo_greitis);

