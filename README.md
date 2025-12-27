# Scientific CLI Calculator (ECE-Oriented)

A **Linux-based Scientific Command Line Calculator** written in **C**, designed with an **Electronics & Communication Engineering (ECE)** focus.  
The tool supports basic arithmetic, scientific math, Ohm’s Law, and DSP-related helpers, built using **CMake** and tested on **Ubuntu (WSL)**.

---

## 🚀 Features

### 🔢 Basic Arithmetic
- Addition
- Subtraction
- Multiplication
- Division

### 📐 Scientific Functions
- Power (`pow`)
- Square root (`sqrt`)
- Logarithmic calculations (`log10`, `ln`)

### ⚡ Electronics (ECE Focus)
- **Ohm’s Law**
    - Voltage calculation
    - Current calculation
    - Resistance calculation

### 📊 DSP Utilities
- RMS value calculation
- Power in decibels (dB)
- Nyquist frequency helper

### 🔁 Unit & Conversion Tools
- ADC resolution calculation
- Voltage ↔ digital value conversion
- Bit-depth based calculations

---

## 🛠️ Build Instructions (Linux / WSL)

### Prerequisites
- Ubuntu / WSL
- GCC
- CMake (≥ 3.1)

### Build Steps
```bash
cd ~/CLion\ Projects/CLI\ Calculator
mkdir -p cmake-build-debug-wsl
cd cmake-build-debug-wsl
cmake ..
make
