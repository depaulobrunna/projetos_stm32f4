#include "main.h"
#include "mpu60x.h"
#include "string.h"

#define MASTER_BOARD

#define REGISTERS_NUM        118

static void SystemClock_Config(void);
static void Error_Handler(void);

static void i2c_init(void);

static I2C_HandleTypeDef I2cHandle;
static uint8_t aTxBuffer;
static uint8_t aRxBuffer[REGISTERS_NUM];

int main(void)
{    
  HAL_Init();
	SystemClock_Config();
	
	i2c_init();
	mpu60x_set_i2c(&I2cHandle);

	memset(&aRxBuffer[0], 0xFF, REGISTERS_NUM);
	
	for(uint32_t i=35; i <= REGISTERS_NUM; i++)
	{
		aRxBuffer[i] = mpu60x_read_register(i);
	}
	
	while (1);
}

static void Error_Handler(void)
{
  while(1);
}

static void i2c_init(void)
{
	
	I2cHandle.Instance             = I2C1;
  I2cHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
  I2cHandle.Init.ClockSpeed      = 400000;
  I2cHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE_16_9;
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
  I2cHandle.Init.OwnAddress1     = 0;
  I2cHandle.Init.OwnAddress2     = 0;
	
  if(HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    Error_Handler();    
  }
}

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  if (HAL_GetREVID() == 0x1001)
  {
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
  }
}
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *I2cHandle)
{
  /* Turn LED5 on: Transfer error in reception/transmission process */
//  BSP_LED_On(LED5); 
}