# Dig Out - Console Adventure Game ⛏️

![DigOut Gameplay Demo](assets/demo.gif)

A feature-rich console-based adventure game written in **C++**, inspired by *Boulder Dash*. This project demonstrates procedural programming, custom physics logic, and memory management without relying on game engines.

## Key Features
* **Gravity Physics Engine:** Stones and items obey gravity. [cite_start]Falling objects can crush the player or enemies[cite: 356, 475].
* [cite_start]**Smart Enemies:** Includes Robot enemies implemented with dynamic memory allocation, capable of interacting with the player [cite: 391-401, 357].
* [cite_start]**Persistence System:** Uses File I/O to save high scores, player names, and game configurations[cite: 423, 542].
* [cite_start]**Configurable Settings:** A dynamic menu allows runtime modification of grid size, object density, and health points[cite: 418, 537].
* **Interactive Elements:**
  * `$` Coins (Score)
  * [cite_start]`+` Potions (Health Restoration) [cite: 399]
  * [cite_start]`*` Bombs (Health Damage) [cite: 396]

## Technical Info
* **Language:** C++ (Standard 11+)
* **Core Concepts:** Pointers, Dynamic Arrays, Structs, File Streams (`fstream`).
* **Platform:** Windows (Optimized for Console).

## How to Run
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/pooya-rz2/DigOut-CPP.git](https://github.com/pooya-rz2/DigOut-CPP.git)
