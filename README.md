# About this project

This repository contains a minimal "bring-up" project for initializing and testing a MKS TFT32_L V3.0 with a **240x320 TFT display** featuring an **ILI9325 controller** on an **STM32F107** microcontroller using the HAL library and a custom GPIO-based parallel bus driver.

The project demonstrates display initialization, backlight control, basic color filling, and text rendering (work in progress).


## Hardware / Board Specification

The firmware is configured for a specific hardware setup utilizing the STM32's high I/O capabilities for a parallel interface.

| Component | Specification | Details |
| :--- | :--- | :--- |
| **MCU** | **STM32F107VCT6** | Targets MCUs with **GPIOE** availability (e.g., VCT6 package or similar). |
| **Display Interface** | **16-bit Parallel Bus** | Uses a full 16-bit data bus (D0..D15) plus control signals (RS/WR/RD/CS). |
| **LCD Controller**| **ILI9325** | Resolution: 240×320. |
| **Power** | 3.3 V | The TFT data and control bus must operate at 3.3V logic levels. Supply through 5V of Auxiliar 1 port. |

### Pinout Configuration

The firmware's low-level I/O routines are hard-coded to the following pin assignments. Note that control signals are **Active LOW** (inactive state is HIGH).

| Display Signal | STM32 Pin (Port) | CubeMX Label (in firmware) | Initial Inactive State |
| :--- | :--- | :--- | :--- |
| **Data Bus (D0..D15)** | **PE0..PE15** (GPIOE) | `DB0_Pin ... DB15_Pin` | Configured as **Output**. |
| **Chip Select (CSn)** | **PC8** (GPIOC) | `CSn_Pin` | **HIGH** (`1`) |
| **Write Strobe (WRn)** | **PB14** (GPIOB) | `WRn_Pin` | **HIGH** (`1`) |
| **Read Strobe (RDn)** | **PD15** (GPIOD) | `RDn_Pin` | **HIGH** (`1`) |
| **Register Select (RS)** | **PD13** (GPIOD) | `RS_Pin` | **HIGH** (`1`) |
| **Backlight Control**| **GPIOD** (specific pin) | `BACKLIGHT_Pin` | Controlled by `LCD_IO_Bl_OnOff(1)` |

> **Note:** These pin names are sourced from the CubeMX `.ioc` file. Any changes to this hardware mapping require updating the `MX_GPIO_Init()` function and the macros within `lcd_io_gpio16.h`.

-----

## Structure

The project is structured into modular files to separate the hardware layer from the controller logic and the application demo.

### Key Files

  * `lcd_io_gpio16.h/.c`: Contains the **low-level primitives** for the parallel bus, implemented via **direct GPIO register manipulation (Bit-Banging)**.
  * `ili9325.h/.c`: The **driver layer** for the ILI9325 controller (initialization sequence, GRAM access, drawing lines, rectangles, etc.).
  * `fonts.h`: Monospaced 1-bit-per-pixel (1bpp) font data used for the demo.
  * `main.c`: HAL/Clock/GPIO initialization, LCD setup, and the **demonstration routine** (color bars and text).

### Essential Initialization Sequence

The core startup logic in `main.c` is performed in this critical order:

1.  Initialize low-level I/O: `LCD_IO_Init();`
2.  Turn on the backlight: `LCD_IO_Bl_OnOff(1);`
3.  **Ensure control lines are inactive (HIGH)** to stabilize the bus:
    ```c
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8,  GPIO_PIN_SET); // CSn
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); // WRn
    // ... other control pins
    ```
4.  Execute controller startup sequence: `ili9325_Init();`
5.  Set recommended **Entry Mode** (RGB and scan direction: right → down):
    ```c
    LCD_IO_WriteCmd16(0x03);
    LCD_IO_WriteData16(0x1030); // bit12=RGB, X_RIGHT, Y_DOWN
    ```

## 📝 TODO / Next Steps

  * **Refactor Color Mapping:** Consolidate the byte-order correction (`MAP()`) into a single layer (preferably `lcd_io_gpio16.h`).
  * **Optimization:** Move the `Entry Mode` setting from the `while(1)` loop to the post-initialization phase (it is a one-time setup).
  * **Driver Features:**
      * Add robust `DrawText` primitives with transparent backgrounds, line wrapping, and clipping.
      * (If applicable) Integrate **Touch Panel** support (the driver files currently contain unused sections for `ILI9325_TOUCH`).
  * **Validation:** Implement visual testing patterns (checkers, gradients) to confirm display orientation and color accuracy.
  