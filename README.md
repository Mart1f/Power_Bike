This repository contains the complete source code for an energy-generating bicycle system designed to measure, transmit, and display electrical parameters such as RPM, 
voltage, current, and power generated in real time. The project combines a Raspberry Pi 4, two ESP32 microcontrollers, a dynamo, and high-voltage LED strips controlled by relays.

As the user pedals, the dynamo produces electricity. A dedicated ESP32 reads the raw data from connected sensors, scales the values, and sends the processed data via Bluetooth to 
a Raspberry Pi 4. It also broadcasts the power data over Wi-Fi using the MAC address protocol to a second ESP32 module.

The Raspberry Pi 4 receives the sensor data via Bluetooth and displays all information on a connected screen. Users can view live metrics including RPM, voltage, current, 
and total power output. This allows for continuous and intuitive feedback on energy generation performance.

The second ESP32 receives the broadcasted data and uses it to control a series of 120V LED strips through relays. As the cyclist pedals harder and generates more power, more LED 
strips light up, providing a visual representation of the pedaling effort and energy output.

This system provides an engaging and educational experience, promoting awareness about energy consumption and production. It also showcases real-time wireless communication between 
embedded systems and the integration of visual feedback for user interaction.
