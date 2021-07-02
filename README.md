# MIDI Light

This project connects musical DAWs to RGB lighting by transforming MIDI signals into light.

## Getting Started

### Prerequisites

Latest version of Arduino IDE: https://www.arduino.cc/en/software
Arduino Leonardo board

### Installing

1. Clone this repository: https://github.com/DanOlert/Arduino-MIDI-light.git
2. Install latest version of Arduino IDE
3. Open the desired sketch in Arduino IDE and upload it to the Arduino Leonardo board

### Usage

Usage depends on the sketch uploaded to the Arduino Leonardo. In most instances, open your DAW and select Arduino Leonardo as a MIDI device. Send cc MIDI signals to cc 14, 15, or 16 to fade Hue, Saturation and Brightness. You may use an amplification circuit in order to use higher powered LED lights.

## Authors

* **Daniel Olert** - [Dan Olert](https://github.com/DanOlert/)

