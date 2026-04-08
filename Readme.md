# 🎤 ESP32 Voice Controlled RGB LED (Offline)

## 🚀 Project Overview

This project demonstrates a **voice-controlled RGB LED system** using **ESP32** and **offline speech recognition (Vosk)**.

You can control LEDs using simple voice commands like:

* green on
* blue off
* all on
* blink

All voice processing is done **offline** (no internet required).

---

## 🧠 Features

* 🎤 Offline voice recognition (Vosk)
* 🌐 ESP32 Web Server
* 💡 Control individual LEDs
* ⚡ Control all LEDs
* 🔁 Blink mode

---

## 🏗️ System Architecture

Voice → Python (Vosk) → HTTP → ESP32 → LED Control

---

## 📁 Project Structure

```text
ESP32-Voice-Control-RGB/
├── src/
│   └── main.cpp
├── model/              (⚠️ download manually)
├── voice.py
├── platformio.ini
└── README.md
```

---

## ⚠️ Voice Model Setup (IMPORTANT)

The `model/` folder is **not included** because it is large.

### 👉 Download Vosk Model:

* Website: https://alphacephei.com/vosk/models
* Recommended: `vosk-model-small-en-us-0.15`

### 👉 Setup:

1. Download and extract
2. Rename folder to:

```
model
```

3. Place inside project:

```
ESP32-Voice-Control-RGB/model/
```

---

## 🧠 Voice Model Reference (Used in this project)

```python
model = Model("model")
```

👉 This means the model must be inside the project folder as `model/`

---

## 🔌 Hardware Requirements

* ESP32 NodeMCU (ESP-32S)
* 3 LEDs (Red, Green, Blue)
* 3 × 220Ω resistors
* Breadboard & jumper wires

---

## 🔧 Pin Configuration

| LED   | GPIO |
| ----- | ---- |
| Red   | 25   |
| Green | 26   |
| Blue  | 27   |

---

## 📡 WiFi Setup

Update in `main.cpp`:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

---

## ⚙️ Installation & Setup

### 1️⃣ Upload Code to ESP32

```bash
pio run --target upload
```

### 2️⃣ Get ESP32 IP

```bash
pio device monitor -b 115200
```

---

### 3️⃣ Install Python Libraries

```bash
pip install vosk sounddevice requests
```

---

### 4️⃣ Update ESP32 IP in Python

```python
ESP_IP = "YOUR_ESP32_IP"
```

---

### 5️⃣ Run Voice Control

```bash
python voice.py
```

---

## 🎤 Voice Commands

green on
green off
blue on
blue off
red on
red off
all on
all off
blink
stop

---

## 🔌 Circuit

GPIO → Resistor → LED → GND

---

## ⚠️ Notes

* Do NOT upload `model/` folder to GitHub
* Use same WiFi network for ESP32 and PC
* Speak commands clearly
* Always use resistors

---

## 📌 Author

Manjunath Alagawadi

---

## ⭐ If you like this project

Give it a star ⭐ 