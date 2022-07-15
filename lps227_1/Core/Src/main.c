/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "stdio.h"
#include "string.h"

#include "rtc_timestamp.h"
#include "sensor_framework.h"
#include "lps277_i2c.h"
#include"lps277_spi.h"
#include "adc_tempsensor.h"
#include "lis2mdl_i2c.h"
#include "bme680_i2c.h"
#include "bh1750_i2c.h"
#include"lsm6dsox_i2c.h"
#include "lis3mdl_i2c.h"
#include "apds9960_i2c.h"
#include "adxl375_spi.h"
#include "adxl375_i2c.h"
#include "aht20_i2c.h"
#include "lsm6dso32_i2c.h"
#include "lsm6dso32_spi.h"
#include "set_drdy.h"
#include "test_file.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc4;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;
I2C_HandleTypeDef hi2c4;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t aShowTimeStamp[16] = "hh:ms:ss";

uint8_t aShowDateStamp[16] = "dd-mm-yyyy";
//__IO uint8_t  RTCStatus = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemPower_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_ICACHE_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
static void MX_ADC4_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C3_Init(void);
static void MX_I2C4_Init(void);
static void MX_SPI2_Init(void);
static void MX_SPI3_Init(void);
/* USER CODE BEGIN PFP */
//LPS27HHW sensor test functions
uint8_t lps277I2CTestInit(I2C_HandleTypeDef I2C_Handle);
uint8_t lps277SPITestInit(SPI_HandleTypeDef SPI_Handle);
uint8_t lps277I2CTestFunction(uint32_t *pres_final_data , I2C_HandleTypeDef I2C_Handle);
uint8_t lps277SPITestFunction(uint32_t *pres_final_data , SPI_HandleTypeDef SPI_Handle);

//LIS2MDL sensor test functions
uint8_t lis2mdlI2CTestInit(I2C_HandleTypeDef I2C_Handle);
uint8_t lis2mdlI2CTestFunction(float magn_final_data[] , I2C_HandleTypeDef I2C_Handle);

//LSM6DSOX sensor test functions
uint8_t lsm6dsoxI2CTestInit(I2C_HandleTypeDef I2C_Handle);
uint8_t lsm6dsoxI2CTestFunction(int16_t acc_final_data[] , int16_t gyro_final_data[], I2C_HandleTypeDef I2C_Handle , uint8_t *acc_flag , uint8_t *gyro_flag);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the System Power */
  SystemPower_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_ICACHE_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  MX_ADC4_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_I2C4_Init();
  MX_SPI2_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */

	//Initializes all the test sensors
	if(HAL_OK != sensorsInit(hi2c1, hi2c2, hi2c3, hi2c4,
			hspi1, hspi2 , hspi3 , hadc4))
		return HAL_ERROR;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

		//Main sensor framework
		sensor_framework(hi2c1, hi2c2, hi2c3, hi2c4,
				hspi1, hspi2 , hspi3 , hadc4 , huart1 , hrtc);
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Power Configuration
  * @retval None
  */
static void SystemPower_Config(void)
{
  HAL_PWREx_EnableVddIO2();

  /*
   * Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
   */
  HAL_PWREx_DisableUCPDDeadBattery();

  /*
   * Switch to SMPS regulator instead of LDO
   */
  if (HAL_PWREx_ConfigSupply(PWR_SMPS_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC4_Init(void)
{

  /* USER CODE BEGIN ADC4_Init 0 */

  /* USER CODE END ADC4_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC4_Init 1 */

  /* USER CODE END ADC4_Init 1 */

  /** Common config
  */
  hadc4.Instance = ADC4;
  hadc4.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV4;
  hadc4.Init.Resolution = ADC_RESOLUTION_12B;
  hadc4.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc4.Init.ScanConvMode = ADC4_SCAN_DISABLE;
  hadc4.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc4.Init.LowPowerAutoPowerOff = ADC_LOW_POWER_NONE;
  hadc4.Init.LowPowerAutoWait = DISABLE;
  hadc4.Init.ContinuousConvMode = ENABLE;
  hadc4.Init.NbrOfConversion = 1;
  hadc4.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc4.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc4.Init.DMAContinuousRequests = DISABLE;
  hadc4.Init.TriggerFrequencyMode = ADC_TRIGGER_FREQ_LOW;
  hadc4.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
  hadc4.Init.SamplingTimeCommon1 = ADC4_SAMPLETIME_1CYCLE_5;
  hadc4.Init.SamplingTimeCommon2 = ADC4_SAMPLETIME_1CYCLE_5;
  hadc4.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC4_CHANNEL_TEMPSENSOR;
  sConfig.Rank = ADC4_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC4_SAMPLINGTIME_COMMON_1;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc4, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC4_Init 2 */

	//Calibration a must for accurate values
	if(HAL_OK != HAL_ADCEx_Calibration_Start(&hadc4, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED))
		Error_Handler();
  /* USER CODE END ADC4_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x30B09DEB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x30909DEC;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.Timing = 0x30909DEC;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief I2C4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C4_Init(void)
{

  /* USER CODE BEGIN I2C4_Init 0 */

  /* USER CODE END I2C4_Init 0 */

  /* USER CODE BEGIN I2C4_Init 1 */

  /* USER CODE END I2C4_Init 1 */
  hi2c4.Instance = I2C4;
  hi2c4.Init.Timing = 0x30909DEC;
  hi2c4.Init.OwnAddress1 = 0;
  hi2c4.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c4.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c4.Init.OwnAddress2 = 0;
  hi2c4.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c4.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c4.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
  if (HAL_I2C_Init(&hi2c4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c4, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c4, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C4_Init 2 */

  /* USER CODE END I2C4_Init 2 */

}

/**
  * @brief ICACHE Initialization Function
  * @param None
  * @retval None
  */
static void MX_ICACHE_Init(void)
{

  /* USER CODE BEGIN ICACHE_Init 0 */

  /* USER CODE END ICACHE_Init 0 */

  /* USER CODE BEGIN ICACHE_Init 1 */

  /* USER CODE END ICACHE_Init 1 */

  /** Enable instruction cache in 1-way (direct mapped cache)
  */
  if (HAL_ICACHE_ConfigAssociativityMode(ICACHE_1WAY) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_ICACHE_Enable() != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ICACHE_Init 2 */

  /* USER CODE END ICACHE_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_PrivilegeStateTypeDef privilegeState = {0};
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  hrtc.Init.OutPutPullUp = RTC_OUTPUT_PULLUP_NONE;
  hrtc.Init.BinMode = RTC_BINARY_NONE;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  privilegeState.rtcPrivilegeFull = RTC_PRIVILEGE_FULL_NO;
  privilegeState.backupRegisterPrivZone = RTC_PRIVILEGE_BKUP_ZONE_NONE;
  privilegeState.backupRegisterStartZone2 = RTC_BKP_DR0;
  privilegeState.backupRegisterStartZone3 = RTC_BKP_DR0;
  if (HAL_RTCEx_PrivilegeModeSet(&hrtc, &privilegeState) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_THURSDAY;
  sDate.Month = RTC_MONTH_JUNE;
  sDate.Date = 0x9;
  sDate.Year = 0x22;
  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the TimeStamp
  */
  if (HAL_RTCEx_SetTimeStamp_IT(&hrtc, RTC_TIMESTAMPEDGE_RISING, RTC_TIMESTAMPPIN_DEFAULT) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

	//Subtracts a fraction of a second
	//Reference: RM0456 Rev 3
	__HAL_RTC_WRITEPROTECTION_DISABLE(hrtc);

	hrtc.Instance->SHIFTR = 0x00000001;   //1 msec

	__HAL_RTC_WRITEPROTECTION_ENABLE(hrtc);
  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  SPI_AutonomousModeConfTypeDef HAL_SPI_AutonomousMode_Cfg_Struct = {0};

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 0x7;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi1.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi1.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi1.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi1.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi1.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi1.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi1.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi1.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi1.Init.ReadyPolarity = SPI_RDY_POLARITY_LOW;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerState = SPI_AUTO_MODE_DISABLE;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerSelection = SPI_GRP1_GPDMA_CH0_TCF_TRG;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerPolarity = SPI_TRIG_POLARITY_RISING;
  if (HAL_SPIEx_SetConfigAutonomousMode(&hspi1, &HAL_SPI_AutonomousMode_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  SPI_AutonomousModeConfTypeDef HAL_SPI_AutonomousMode_Cfg_Struct = {0};

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 0x7;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi2.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi2.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi2.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi2.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi2.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi2.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi2.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi2.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi2.Init.ReadyPolarity = SPI_RDY_POLARITY_LOW;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerState = SPI_AUTO_MODE_DISABLE;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerSelection = SPI_GRP1_GPDMA_CH0_TCF_TRG;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerPolarity = SPI_TRIG_POLARITY_RISING;
  if (HAL_SPIEx_SetConfigAutonomousMode(&hspi2, &HAL_SPI_AutonomousMode_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  SPI_AutonomousModeConfTypeDef HAL_SPI_AutonomousMode_Cfg_Struct = {0};

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 0x7;
  hspi3.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;
  hspi3.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  hspi3.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  hspi3.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  hspi3.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  hspi3.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  hspi3.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  hspi3.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  hspi3.Init.ReadyMasterManagement = SPI_RDY_MASTER_MANAGEMENT_INTERNALLY;
  hspi3.Init.ReadyPolarity = SPI_RDY_POLARITY_LOW;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerState = SPI_AUTO_MODE_DISABLE;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerSelection = SPI_GRP1_GPDMA_CH0_TCF_TRG;
  HAL_SPI_AutonomousMode_Cfg_Struct.TriggerPolarity = SPI_TRIG_POLARITY_RISING;
  if (HAL_SPIEx_SetConfigAutonomousMode(&hspi3, &HAL_SPI_AutonomousMode_Cfg_Struct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin : VBUS_SENSE_Pin */
  GPIO_InitStruct.Pin = VBUS_SENSE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_SENSE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DRDY_LSM6DSOX_INT2_Pin DRDY_LSM6DSOX_INT1_Pin DRDY_LIS3MDL_Pin DRDY_LSM6DSO32_INT1_Pin
                           DRDY_LSM6DSO32_INT2_Pin */
  GPIO_InitStruct.Pin = DRDY_LSM6DSOX_INT2_Pin|DRDY_LSM6DSOX_INT1_Pin|DRDY_LIS3MDL_Pin|DRDY_LSM6DSO32_INT1_Pin
                          |DRDY_LSM6DSO32_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : DRDY_ADXL375_Pin */
  GPIO_InitStruct.Pin = DRDY_ADXL375_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DRDY_ADXL375_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PG2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : DRDY_LPS27HHW_Pin */
  GPIO_InitStruct.Pin = DRDY_LPS27HHW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DRDY_LPS27HHW_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA11 PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_USB;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI6_IRQn);

  HAL_NVIC_SetPriority(EXTI7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI7_IRQn);

  HAL_NVIC_SetPriority(EXTI8_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI8_IRQn);

  HAL_NVIC_SetPriority(EXTI9_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_IRQn);

  HAL_NVIC_SetPriority(EXTI10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI10_IRQn);

  HAL_NVIC_SetPriority(EXTI11_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI11_IRQn);

  HAL_NVIC_SetPriority(EXTI12_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI12_IRQn);

}

/* USER CODE BEGIN 4 */

/**
 * @brief Interrupt callback for INT_DRDY pin from sensor (PC-6)
 * @param uint16_t GPIO_Pin: GPIO Pin number where interrupt is triggered
 * @retval None
 */
//void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
//{
//	//LPS27HHW data ready pin
//	if(GPIO_Pin == DRDY_LPS27HHW_Pin)
//		lps27_drdy = 1;
//
//	//LSM6DSOX data ready pin gyroscope
//	if(GPIO_Pin == DRDY_LSM6DSOX_INT2_Pin)
//		lsm6dsox_gyro_drdy = 1;
//
//	//LSM6DSOX data ready pin accelerometer
//	if(GPIO_Pin == DRDY_LSM6DSOX_INT1_Pin)
//		lsm6dsox_acc_drdy = 1;
//
//	if(GPIO_Pin == DRDY_LSM6DSO32_INT1_Pin)
//		lsm6dso32_acc_drdy = 1;
//
//	if(GPIO_Pin == DRDY_LSM6DSO32_INT2_Pin)
//		lsm6dso32_gyro_drdy = 1;
//
//	//LISM3DL data ready pin magnetometer
//	if(GPIO_Pin == DRDY_LIS3MDL_Pin)
//		lism3dl_drdy = 1;
//
//}
//
//void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
//{
//
//	//ADXL375 Data ready pin accelerometer
//	if(GPIO_Pin == DRDY_ADXL375_Pin)
//		adxl375_drdy = 1;
//}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
//{
//	adc_irq = 1;
//}

/**
 * @brief  Timestamp callback
 * @param  hrtc : hrtc handle
 * @retval None
 */
void HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *RTC_Handle)
{
	//	RTCStatus = 1;
	RTC_DateTypeDef sTimeStampDateget;
	RTC_TimeTypeDef sTimeStampget;

	HAL_RTCEx_GetTimeStamp(&hrtc, &sTimeStampget, &sTimeStampDateget, RTC_FORMAT_BIN);

	//Convert sub-seconds into milliseconds
	uint16_t millisec = (1000 * (sTimeStampget.SecondFraction - sTimeStampget.SubSeconds)) / (sTimeStampget.SecondFraction + 1);

	/* Display time Format : hh:mm:ss */
	sprintf((char *)aShowTimeStamp, "%.2d:%.2d:%.2d:%.3hu", sTimeStampget.Hours, sTimeStampget.Minutes, sTimeStampget.Seconds, millisec);
	/* Display date Format : mm-dd */
	sprintf((char *)aShowDateStamp, "%.2d-%.2d-%.2d", sTimeStampDateget.Month, sTimeStampDateget.Date, 2020);
}



/**
 * @brief LPS27 Sensor Test Function Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CTestInit(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != lps227I2CWhoami(I2C_Handle))
		ret_status = HAL_ERROR;


	//Start-up sequence
	if(HAL_OK != lps277I2CSetup(I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief LPS27 Sensor Test Function Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CTestInit(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != lis2mdlI2CWhoami(I2C_Handle))
		ret_status = HAL_ERROR;


	//Start-up sequence
	if(HAL_OK != lis2mdlI2CSetup(I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief LSM6DSOX Sensor Test Function Initialization
 * @param I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CTestInit(I2C_HandleTypeDef I2C_Handle)
{
	uint8_t ret_status = HAL_OK;

	//	if(HAL_OK != lsm6dsoxI2CWhoami(I2C_Handle))
	//		ret_status = HAL_ERROR;

	if(HAL_OK != lsm6dso32I2CWhoami(I2C_Handle))
		ret_status = HAL_ERROR;


	//	//Start-up sequence
	//	if(HAL_OK != lsm6dsoxI2CSetup(I2C_Handle))
	//		ret_status = HAL_ERROR;

	//Start-up sequence
	if(HAL_OK != lsm6dso32I2CSetup(I2C_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief LPS27 Sensor Test Function I2C
 * @param uint32_t *pres_final_data: Final pressure data in hPa
 * 		  I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277I2CTestFunction(uint32_t *pres_final_data , I2C_HandleTypeDef I2C_Handle)
{
	uint8_t pres_raw_data[3];

	uint8_t ret_status = HAL_OK;


	if(HAL_OK == lps277I2CPressureRawData(pres_raw_data , I2C_Handle))
		*pres_final_data = lps277I2CPressureFinalData(pres_raw_data, 3);
	else
		ret_status = HAL_ERROR;



	return ret_status;
}

/**
 * @brief LIS2MDL Sensor Test Function I2C
 * @param int16_t *mag_final_data: Final magnetic data in mG
 * 		  I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lis2mdlI2CTestFunction(float magn_final_data[] , I2C_HandleTypeDef I2C_Handle)
{
	uint8_t magn_raw_data[6];

	uint8_t ret_status = HAL_OK;


	if(HAL_OK == lis2mdlMagneticRawData(magn_raw_data, I2C_Handle))
		lis2mdlI2CMagneticFinalData(magn_raw_data, 6, magn_final_data);
	else
		ret_status = HAL_ERROR;



	return ret_status;
}

/**
 * @brief LSM6DSOX Sensor Test Function I2C
 * @param int16_t acc_final_data: Final linear acceleration
 * 	      int16_t gyro_final_data: Final angular acceleration
 * 		  I2C_HandleTypeDef: The I2C peripheral on the micro-controller
 * 		  uint8_t *acc_flag: Flag to indicate new data read
 * 		  uint8_t *gyro_flag: Flag to indicate new data read
 * @retval ret_status: Error status
 */
uint8_t lsm6dsoxI2CTestFunction(int16_t acc_final_data[] , int16_t gyro_final_data[], I2C_HandleTypeDef I2C_Handle , uint8_t *acc_flag , uint8_t *gyro_flag)
{
	uint8_t ret_status = HAL_OK;

	//	if(lsm_acc_drdy == 1)
	//	{
	//		lsm_acc_drdy = 0;
	*acc_flag = 1;
	//		if(HAL_OK != lsm6dsoxI2CAccRawData(I2C_Handle, acc_final_data))
	//			ret_status = HAL_ERROR;
	//		if(HAL_OK != lsm6dso32I2CAccRawData(I2C_Handle, acc_final_data))
	//			ret_status = HAL_ERROR;

	if(HAL_OK != lsm6dso32SPIAccData(hspi1, acc_final_data))
		ret_status = HAL_ERROR;
	//	}

	//	if(lsm_gyro_drdy == 1)
	//	{
	//		lsm_gyro_drdy = 0;
	*gyro_flag = 1;
	//		if(HAL_OK != lsm6dsoxI2CGyroRawData(I2C_Handle, gyro_final_data))
	//			ret_status = HAL_ERROR;
	//		if(HAL_OK != lsm6dso32I2CGyroRawData(I2C_Handle, gyro_final_data))
	//			ret_status = HAL_ERROR;

	if(HAL_OK != lsm6dso32SPIGyroData(hspi1, gyro_final_data))
		ret_status = HAL_ERROR;
	//	}

	return ret_status;
}

/**
 * @brief LPS27 Sensor Test Function Initialization
 * @param SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277SPITestInit(SPI_HandleTypeDef SPI_Handle)
{
	uint8_t ret_status = HAL_OK;

	if(HAL_OK != lps227SPIWhoami(SPI_Handle))
		ret_status = HAL_ERROR;


	//Start-up sequence
	if(HAL_OK != lps277SPISetup(SPI_Handle))
		ret_status = HAL_ERROR;

	return ret_status;

}

/**
 * @brief LPS27 Sensor Test Function SPI
 * @param uint32_t *pres_final_data: Final pressure data in hPa
 * 		  SPI_HandleTypeDef: The SPI peripheral on the micro-controller
 * @retval ret_status: Error status
 */
uint8_t lps277SPITestFunction(uint32_t *pres_final_data , SPI_HandleTypeDef SPI_Handle)
{
	uint8_t pres_raw_data[3];
	//	uint8_t con_flag =  0;

	uint8_t ret_status = HAL_OK;

	if(HAL_OK == lps277SPIPressureRawData(pres_raw_data , SPI_Handle))
	{
		//		if(con_flag == 1)
		*pres_final_data = lps277SPIPressureFinalData(pres_raw_data, 3);
		//		else
		//			ret_status = 2;
	}
	else
		ret_status = HAL_ERROR;

	return ret_status;
}


//		if(HAL_OK != adxl375SPIWhoami(hspi1))
//			return HAL_ERROR;

//		if(HAL_OK != adxl375SPISetup(hspi1))
//			return HAL_ERROR;


//		if(HAL_OK != aht20TempHumiditySetup(hi2c1))
//			return HAL_ERROR;
//
//		if(HAL_OK != aht20TempHumidityData(hi2c1, &temp, &humidity))
//			return HAL_ERROR;
//		else
//		{
//			RTCTimestamp(time_stamp, date_stamp, hrtc);
//			sprintf((char *)print_string ,"%s Temp: %.3f RH: %.3f\r\n", time_stamp, temp , humidity);
//			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//			memset(print_string , 0 , sizeof(print_string));
//
//		}
//
//		HAL_Delay(100);

//		if (HAL_OK != adxl375SPIAccData(hspi1, acc_data))
//			return HAL_ERROR;

//		if (HAL_OK != adxl375I2CAccData(acc_data , hi2c1))
//			return HAL_ERROR;
//		if(HAL_OK != adxl375SPIAccData(hspi1, acc_data))
//			;
//		if(adxl375_drdy == 1)
//		{
//			adxl375_drdy = 0;
//			if (HAL_OK != adxl375SPIAccData(hspi1, acc_data))
//				return HAL_ERROR;
//			//			if (HAL_OK != adxl375I2CAccData(acc_data , hi2c1))
//			//				return HAL_ERROR;
//			else
//			{
//				sprintf((char *)print_string ,"%s ACC: X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp,acc_data[0], acc_data[1], acc_data[2]);
//				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//				memset(print_string , 0 , sizeof(print_string));
//
//			}
//		}




//		if(HAL_OK != apds9960ProximitySetup(hi2c1))
//			return HAL_ERROR;
//
//
//		//		if(HAL_OK != apds9960ProximityData(hi2c1, &proximity))
//		//			return HAL_ERROR;
//
//		//		if(apds9960_drdy == 1)
//		//		{
//		//			apds9960_drdy = 0;
//		if(HAL_OK != apds9960ProximityData(hi2c1, &proximity))
//			return HAL_ERROR;
//
//		sprintf((char *)print_string ,"%s Proximity: %d\r\n", time_stamp,proximity);
//		HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//		memset(print_string , 0 , sizeof(print_string));

//		}

//if(HAL_OK != adxl375I2CWhoami(hi2c1))
//		return HAL_ERROR;
//	if(HAL_OK != adxl375I2CSetup(hi2c1))
//		return HAL_ERROR;

//	if(HAL_OK != adxl375SPIWhoami(hspi1))
//		return HAL_ERROR;
//	if(HAL_OK != adxl375SPISetup(hspi1))
//		return HAL_ERROR;
//
//		if(adxl375_drdy == 1)
//		{
//			adxl375_drdy = 0;
//			//			if (HAL_OK != adxl375SPIAccData(hspi1, acc_data))
//			if(HAL_OK != adxl375I2CAccData(acc_data, hi2c1))
//				return HAL_ERROR;
//			else
//			{
//				RTCTimestamp(time_stamp, date_stamp, hrtc);
//				sprintf((char *)print_string ,"%s ACC: X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp,acc_data[0], acc_data[1], acc_data[2]);
//				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//				memset(print_string , 0 , sizeof(print_string));
//
//			}
//		}

//if(HAL_OK != aht20TempHumidityData(hi2c1, &temp, &humidity))
//			return HAL_ERROR;
//		else
//		{
//			RTCTimestamp(time_stamp, date_stamp, hrtc);
//			sprintf((char *)print_string ,"%s Temp: %.3f RH: %.3f\r\n", time_stamp, temp , humidity);
//			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//			memset(print_string , 0 , sizeof(print_string));
//
//		}
//
//if(HAL_OK != aht20TempHumiditySetup(hi2c1))
//		return HAL_ERROR;

//if(lism3dl_drdy == 1)
//		{
//			RTCTimestamp(time_stamp, date_stamp, hrtc);
//			lism3dl_drdy = 0;
//			if(HAL_OK != lis3mdlMagneticData(mag_data, hi2c1))
//				return HAL_ERROR;
//			else
//			{
//				sprintf((char *)print_string ,"%s X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp, mag_data[0], mag_data[1], mag_data[2]);
//				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//				memset(print_string , 0 , sizeof(print_string));
//
//			}
//			HAL_Delay(100);
//		}

//if(lsm_acc_drdy == 1)
//		{
//			lsm_acc_drdy = 0;
//
//			if(HAL_OK != lsm6dso32SPIAccData(hspi1, acc_data))
//				return HAL_ERROR;
//			else
//			{
//				RTCTimestamp(time_stamp, date_stamp, hrtc);
//				sprintf((char *)print_string ,"%s ACC: X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp,acc_data[0], acc_data[1], acc_data[2]);
//				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//				memset(print_string , 0 , sizeof(print_string));
//
//			}
//		}
//
//		if(lsm_gyro_drdy == 1)
//		{
//			lsm_gyro_drdy = 0;
//
//			if(HAL_OK != lsm6dso32SPIGyroData(hspi1, gyro_data))
//				return HAL_ERROR;
//			else
//			{
//				RTCTimestamp(time_stamp, date_stamp, hrtc);
//				sprintf((char *)print_string ,"%s GYRO: X:%.3d Y:%.3d Z:%.3d\r\n", time_stamp,gyro_data[0], gyro_data[1], gyro_data[2]);
//				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//				memset(print_string , 0 , sizeof(print_string));
//
//			}
//
//
//		}

//if(data_rdy_flag == 1)
//		{
//			data_rdy_flag = 0;
//
//			if(HAL_OK != lps277I2CTestFunction(&pres_data, hi2c1))
//				return HAL_ERROR;
//			else
//			{
//				RTCTimestamp(time_stamp, date_stamp, hrtc);
//				sprintf((char *)print_string ,"%s Pres: %lu\r\n", time_stamp, pres_data);
//				HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//				memset(print_string , 0 , sizeof(print_string));
//
//			}
//		}

//uint8_t time_stamp[7] , date_stamp[12];
//	float mag_data[3];
//	//	int16_t acc_data[3], gyro_data[3];
//	//	uint32_t pres_data;
//	//	uint16_t light_data;
//	uint8_t print_string[50];

//if(HAL_OK != lis2mdlI2CTestFunction(mag_data, hi2c1))
//			return HAL_ERROR;
//		else
//		{
//			sprintf((char *)print_string ,"%s X:%.3f Y:%.3f Z:%.3f\r\n", time_stamp, mag_data[0], mag_data[1], mag_data[2]);
//			HAL_UART_Transmit(&huart1, print_string, sizeof(print_string), 100);
//			memset(print_string , 0 , sizeof(print_string));
//		}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
