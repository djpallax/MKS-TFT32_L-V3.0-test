/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "ili9325.h"
#include "lcd.h"
#include "lcd_io_gpio16.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// Invertir bytes del 16-bit (LSB<->MSB en el bus):
#define MAP(c) (swap16(c))

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ---- utilidades de remapeo de color 565 sin tocar la lib ----
static inline uint8_t rev8(uint8_t x) { // invierte bits dentro del byte
  x = (x & 0xF0) >> 4 | (x & 0x0F) << 4;
  x = (x & 0xCC) >> 2 | (x & 0x33) << 2;
  x = (x & 0xAA) >> 1 | (x & 0x55) << 1;
  return x;
}
static inline uint16_t swap16(uint16_t v) { // invierte los bytes
  return (uint16_t)((v << 8) | (v >> 8));
}
static inline uint16_t
swap_rb(uint16_t c) { // intercambia R y B (RGB565 <-> BGR565)
  return (uint16_t)(((c & 0xF800) >> 11) | (c & 0x07E0) | ((c & 0x001F) << 11));
}

static void DrawChar_1bpp(uint16_t x, uint16_t y, char ch,

                          const sFONT *font,

                          uint16_t fg, uint16_t bg)

{

  if (ch < 32 || ch > 126)
    ch = '?';

  uint16_t w = font->Width;

  uint16_t h = font->Height;

  // bytes por fila = ceil(w/8)

  uint16_t rowBytes = (w + 7) >> 3;

  // offset del caracter dentro de la tabla

  uint32_t off = (uint32_t)(ch - 32) * h * rowBytes;

  for (uint16_t yy = 0; yy < h; yy++) {

    const uint8_t *row = &font->table[off + yy * rowBytes];

    uint8_t mask = 0x80;

    uint8_t byte = row[0];

    uint16_t bx = 0;

    for (uint16_t xx = 0; xx < w; xx++) {

      if ((xx & 7) == 0) {
        mask = 0x80;
        byte = row[xx >> 3];
      }

      uint16_t col = (byte & mask) ? fg : bg;

      mask >>= 1;

      ili9325_WritePixel(x + xx, y + yy, MAP(col));

      bx++;
    }
  }
}

void DrawString(uint16_t x, uint16_t y, const char *s,

                const sFONT *font, uint16_t fg, uint16_t bg)

{

  uint16_t cx = x;

  while (*s) {

    if (*s == '\n') {
      y += font->Height;
      cx = x;
      s++;
      continue;
    }

    DrawChar_1bpp(cx, y, *s, font, fg, bg);

    cx += font->Width;

    s++;
  }
}

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick.
   */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  LCD_IO_Init();
  LCD_IO_Bl_OnOff(1);

  // CS inactivo = 1, WR=1, RD=1, RS=1
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);  // CS
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); // WR
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET); // RD
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET); // RS

  ili9325_Init();
  ili9325_FillRect(0, 0, 240, 320, 0xF8F0);
  ili9325_FillRect(0, 0, 240, 320, 0xFFFF);

  HAL_Delay(200);

  ili9325_FillRect(0, 0, 240, 320, 0x0000);
  DrawString(10, 10, "ABCD", &Font24, 0xFFFF, 0x07E0);
  DrawString(10, 40, "TEST", &Font24, 0xF800, 0x0000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    // Cambiar a RGB (bit12 = 1) + I/D = “right then down” (0x0030)
    LCD_IO_WriteCmd16(0x03);
    LCD_IO_WriteData16(0x1030); // RGB + X_RIGHT + Y_DOWN

    // Sin espejo (SS=0, GS=0), 320 líneas (NL = 0x27)
    LCD_IO_WriteCmd16(0x01);
    LCD_IO_WriteData16(0x0000); // SS=0

    // Barras de color
    ili9325_FillRect(0, 0, 240, 80, MAP(0xF800));   // ROJO
    ili9325_FillRect(0, 80, 240, 80, MAP(0x07E0));  // VERDE
    ili9325_FillRect(0, 160, 240, 80, MAP(0x001F)); // AZUL
    ili9325_FillRect(0, 240, 240, 80, MAP(0xFFFF)); // BLANCO

    DrawString(10, 10, "ROJO", &Font24, MAP(0xFFFF), MAP(0x0000));
    DrawString(10, 90, "VERDE", &Font24, MAP(0x0000), MAP(0x07E0));
    DrawString(10, 170, "AZUL", &Font24, MAP(0xFFFF), MAP(0x001F));

    HAL_Delay(1000);
  }
  /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {

  // --- Limpieza de reloj para evitar el guard de PLL2 ---
  /* 1) Asegurar HSI encendido y conmutar SYSCLK a HSI */
  SET_BIT(RCC->CR, RCC_CR_HSION);
  while ((RCC->CR & RCC_CR_HSIRDY) == 0) { /* wait */
  }

  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_HSI);
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) { /* wait */
  }

  /* 2) Apagar PLL principal y PLL2 si estaban activos */
  if (RCC->CR & RCC_CR_PLLON) {
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (RCC->CR & RCC_CR_PLLRDY) { /* wait off */
    }
  }
  if (RCC->CR & RCC_CR_PLL2ON) {
    CLEAR_BIT(RCC->CR, RCC_CR_PLL2ON);
    while (RCC->CR & RCC_CR_PLL2RDY) { /* wait off */
    }
  }

  /* 3) (Opcional) Devolver PREDIV1SRC a HSE para que HAL pueda reconfigurar
   * PLL2 */
  CLEAR_BIT(RCC->CFGR2, RCC_CFGR2_PREDIV1SRC); // 0 = HSE como fuente de PREDIV1

  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
   * in the RCC_OscInitTypeDef structure.
   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
  RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
  RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
    Error_Handler();
  }

  /** Configure the Systick interrupt time
   */
  __HAL_RCC_PLLI2S_ENABLE();
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE,
                    DB2_Pin | DB3_Pin | DB4_Pin | DB5_Pin | DB6_Pin | DB7_Pin |
                        DB8_Pin | DB9_Pin | DB10_Pin | DB11_Pin | DB12_Pin |
                        DB13_Pin | DB14_Pin | DB15_Pin | DB0_Pin | DB1_Pin,
                    GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(WRn_GPIO_Port, WRn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, RS_Pin | BACKLIGHT_Pin | RDn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CSn_GPIO_Port, CSn_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : DB2_Pin DB3_Pin DB4_Pin DB5_Pin
                           DB6_Pin DB7_Pin DB8_Pin DB9_Pin
                           DB10_Pin DB11_Pin DB12_Pin DB13_Pin
                           DB14_Pin DB15_Pin DB0_Pin DB1_Pin */
  GPIO_InitStruct.Pin = DB2_Pin | DB3_Pin | DB4_Pin | DB5_Pin | DB6_Pin |
                        DB7_Pin | DB8_Pin | DB9_Pin | DB10_Pin | DB11_Pin |
                        DB12_Pin | DB13_Pin | DB14_Pin | DB15_Pin | DB0_Pin |
                        DB1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : WRn_Pin */
  GPIO_InitStruct.Pin = WRn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(WRn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RS_Pin BACKLIGHT_Pin RDn_Pin */
  GPIO_InitStruct.Pin = RS_Pin | BACKLIGHT_Pin | RDn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : CSn_Pin */
  GPIO_InitStruct.Pin = CSn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(CSn_GPIO_Port, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1) {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line
     number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
     line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
