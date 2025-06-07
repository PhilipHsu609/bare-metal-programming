# Bare Metal Programming

This project is my learning journey into bare metal programming, focusing on ARM Cortex-M microcontrollers.

I'm using the NUCLEO-F446RE STM32F446RE Mbed board with the following resources and learning materials:

- [Low Byte Productions Series Youtube Playlist](https://www.youtube.com/playlist?list=PLP29wDx6QmW7HaCrRydOnxcy8QmW0SNdQ)
- [Low Byte Productions Series GitHub Repository](https://github.com/lowbyteproductions/bare-metal-series)
- [STM32F446RE Datasheet](https://www.st.com/resource/en/datasheet/stm32f446mc.pdf)
- [STM32F446RE Reference Manual](https://www.st.com/resource/en/reference_manual/rm0390-stm32f446xx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [NUCLEO-F446RE User Manual](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
- [ST-LINK](https://github.com/stlink-org/stlink)
- [libopencm3](https://libopencm3.org/)
- [簡單入門 LibOpenCM3 STM32 嵌入式系統開發](https://ithelp.ithome.com.tw/users/20151756/ironman/5382)

## Series

### 1. Hello World Blinky!

- Set up the development environment
  - ST-LINK
    - Flash the board with `st-flash`
      - `st-flash write $(BINARY).bin 0x8000000`
      - `st-flash reset`
    - Debugging with `st-util`
  - libopencm3
- `rcc`
  - Reset and clock control
- `pll`
  - Phase-locked loop
- `hsi`
  - High-speed internal oscillator
- `lsi`
  - Low-speed internal oscillator
- `hse`
  - High-speed external oscillator
- `lse`
  - Low-speed external oscillator
- `gpio`
  - General-purpose input/output
  - Pull-up and pull-down resistors

### 2. Interrupts and Memory Mapped I/O

- Datasheet
  - Memory map
  - Peripheral registers
- `systick`
  - SysTick timer
  - SysTick Counter
  - SysTick interrupt
    - `NVIC`
    - Nested Vectored Interrupt Controller
    - Interrupt table
    - Interrupt handlers

### 3. PWM and Timers

- PWM;
  - Pulse Width Modulation
  - Auto reload register (ARR) controls the period
  - Capture/Compare register (CCR) controls the duty cycle (the ratio of on time to off time)
    - duty cycle = (CCR / ARR) * 100%
- Timers
  - General-purpose timers
  - Advanced-control timers
  - Basic timers
