# 🚴‍♂️ Power Bike – Energy-Generating Bicycle System

This repository contains the complete source code and system description for an **interactive energy-generating bicycle** that monitors, transmits, and visualizes real-time electrical parameters such as **RPM, voltage, current, and power output**.

---

## 🔧 System Overview

The project integrates multiple hardware components, including:

- 🧠 **Raspberry Pi 4** – acts as the main display unit
- 📡 **Two ESP32 microcontrollers** – for sensor reading and control logic
- ⚙️ **Dynamo** – generates electricity as the user pedals
- 💡 **120V LED strips** – visually indicate energy production via relays

---

## 🔁 How It Works

1. As the user **pedals**, the **dynamo** generates electricity.
2. A dedicated **ESP32**:
   - Reads raw sensor data (RPM, voltage, current).
   - Scales and processes the values.
   - Sends the data via **Bluetooth** to the **Raspberry Pi 4**.
   - Simultaneously **broadcasts** the power data over **Wi-Fi** (MAC-based protocol) to a second ESP32.
3. The **Raspberry Pi 4**:
   - Receives the data via Bluetooth.
   - Displays real-time metrics on a connected screen using a **Python GUI (Tkinter)** dashboard.
4. The **second ESP32**:
   - Receives power data over Wi-Fi.
   - Controls **relay modules** to turn on/off high-voltage **LED strips**.
   - The number of LEDs turned on increases with the pedaling effort and power output.

---

## 📊 Features

- Real-time data visualization:
  - 🔵 **Voltage**
  - 🟢 **Current**
  - 🔁 **RPM**
  - 🔌 **Power (W)**
- Bluetooth communication for dashboard data
- Wi-Fi-based broadcast to auxiliary control system
- LED feedback system representing physical effort
- Modular and scalable architecture
- Educational and interactive energy awareness system

---

## 📸 Screenshots

![WhatsApp Image 2025-07-02 at 12 19 26 PM (1)](https://github.com/user-attachments/assets/1e5ae4fc-ae23-4544-899d-012a0a7748b5)


---

## 📦 Requirements

- Python 3.x
- `tkinter` for GUI (pre-installed on Raspberry Pi OS)
- Serial libraries for ESP32 code (e.g., Arduino framework)
- Bluetooth configuration (for Raspberry Pi)
- Relay modules compatible with 120V LED strips

---

## 👨‍💻 Author

**Martín Felipe Bermúdez Romero**  
Student of Electronic Engineering  
Universidad Distrital Francisco José de Caldas  
martimrome13@gmail.com*
mfbermudezr@udistrital.edu.co*

---


## 🚀 Future Improvements (optional)

- Data logging to CSV or database
- Web dashboard for remote monitoring
- Energy storage monitoring (e.g., batteries or capacitors)
- Support for multiple bikes or users

---



