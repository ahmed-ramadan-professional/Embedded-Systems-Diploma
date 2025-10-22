# AVR Calculator Project

This project implements a **fully functional calculator** on an **AVR microcontroller** using a **16x2 LCD** and **4x4 Keypad**.  
The main challenge and what makes this project technically impressive is that **the entire equation is written and processed on a single LCD line (16 characters only)**.  
Despite this limitation, the program handles multi-digit arithmetic, input cleanup, and correct operator precedence.

![Alt Text](.media/Showcase%201.jpg)

## ⚙️ Features

- Supports the operators: `+`, `-`, `*`, `/`
- Handles **multi-digit positive numbers** (e.g., `123 + 45`)
- Displays **negative results correctly** (e.g., `3-9 = -6`)
- **Equation input and display are limited to one LCD line (16 characters)**  
  - No scrolling or second-line input
  - Requires precise memory and cursor management  
- Cleans invalid or repeated operators (`--`, `++`, etc.)
- Detects and displays `"ERR DIV BY 0"` when dividing by zero
- Provides **backspace (`<`)** and **equals (`=`)** functionality
- Real-time expression evaluation once `=` is pressed


## ⚠️ Limitations

- **Negative numbers as input are not supported**  
  You can subtract numbers (e.g., `9-3=6`), but you cannot start an equation with a negative value like `-5+3`.
- Supports up to **16 visible characters** (LCD line width)
- No parentheses `()` or floating-point numbers

