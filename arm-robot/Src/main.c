/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
#include "string.h"
#include "stdio.h"
#include "stm32f4xx_it.h"

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

/* USER CODE BEGIN PV */
#ifdef _GNUC_
#define PUTCHAR_PROTOTYPE int __io_putcahr(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch,FILE *f)
#endif  /* _GNUC_ */
PUTCHAR_PROTOTYPE{
		HAL_UART_Transmit(&huart2 ,(uint8_t *)&ch ,1,10);
	return ch;
}
uint32_t echo2,delay;
float dist2;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim11;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char dists[16];
int i__1 = 72;
int i__2 = 45;
int i__3 = 52;
int i__4 = 59;
int countCatch = 0;
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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_TIM11_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
	lcd_init ();
	HAL_TIM_Base_Start(&htim11);
	HAL_TIM_Base_Start(&htim1);
	HAL_TIM_PWM_Start(&htim11,TIM_CHANNEL_1);
	HAL_TIM_IC_Start(&htim1,TIM_CHANNEL_2);
	
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_4);
	TIM11->CCR1 = 3;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	reset_Start(i__1,i__2,i__3,i__4);
	lcd_send_cmd (0x01);
	HAL_Delay(500);
	displayLCD_Manual_mode();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		manualMode();			
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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/**********************************************************/
void displayLCD_auto_mode(float dist){
	sprintf(dists,"distance:%.2f",dist);
	lcd_send_cmd (0xc0);
	lcd_send_string (dists);
	HAL_Delay(50);
}
void displayLCD_Manual_mode(){
	lcd_send_cmd (0x80);
	lcd_send_string ("MANUAL MODE");
	HAL_Delay(100);
}
void reset_Start(int i_1,int i_2,int i_3,int i_4){
		htim3.Instance ->CCR1= i_1; 
		HAL_Delay(50);
	  htim3.Instance ->CCR2 = i_2;
		HAL_Delay(50);
	  htim3.Instance ->CCR3 = i_3;
		HAL_Delay(50);
		htim3.Instance ->CCR4 = i_4;
		HAL_Delay(50);
}
/**********************************************************/

	  /*
		  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)== GPIO_PIN_RESET){
				HAL_UART_Transmit(&huart2, (uint8_t*)"TEST",strlen("TEST"),1000);
				HAL_Delay(1000);
			}
	  */

/******************Manual Mode start*****************************/
void catchs(int i ){
		htim3.Instance ->CCR2 = i;
		HAL_Delay(20);
}
void UpAndDown(int i ,int i2){
	  htim3.Instance ->CCR3 = i;
		HAL_Delay(10);
		htim3.Instance ->CCR4 = i2;
		HAL_Delay(10);
}
void forwordAndbackword(int i ,int i2){
		htim3.Instance ->CCR3 = i;
		HAL_Delay(10);
		htim3.Instance ->CCR4 = i2;
		HAL_Delay(10);
}
void cycle(int i){
		htim3.Instance ->CCR1 = i;
		HAL_Delay(10);
}
void manualMode(){
			 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6) == GPIO_PIN_SET && i__1>25){
				cycle(i__1);
				i__1--;
			}if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7) == GPIO_PIN_SET && i__1<126){
				cycle(i__1);
				i__1++;
			}if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)==GPIO_PIN_SET && i__3 < 55){
				UpAndDown(i__3 ,i__4);
				i__3++;
		  }if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)==GPIO_PIN_SET && i__3>25){
		    if(i__4 < 40 && i__3 <40){
						UpAndDown(i__3 ,i__4);
						i__3--;
						i__4++;	
					}else{
						UpAndDown(i__3 ,i__4);
						i__3--;
					}	
			}if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==GPIO_PIN_SET && i__4<61){
				forwordAndbackword(i__3 ,i__4);
				i__4++;
			}if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)==GPIO_PIN_SET && i__4>25){
		    if(i__4 < 54 && i__3 <35){
						forwordAndbackword(i__3 ,i__4);
						i__3++;
						i__4--;	
					}else{
						forwordAndbackword(i__3 ,i__4);
						i__4--;
					}	
			}else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_8) == GPIO_PIN_SET){
					 if(countCatch==1){
						catchs(45);
						countCatch = 0; 
					}else if(countCatch == 0){
						catchs(25);
						countCatch =1;
					}
					HAL_Delay(500);
		}
}
/******************Manual Mode end*****************************/

/******************Auto Mode start*****************************/
void catchOffAuto(int i_2,int i_3,int i_4){
	while(1){
			if(i_2 != 45 ){  
				htim3.Instance ->CCR2 = i_2;
				HAL_Delay(30);
				i_2++;
			}else if(i_4 != 59 ){  
				htim3.Instance ->CCR4= i_4; 
				HAL_Delay(30);
				i_4++;
			}else if(i_3 != 52){  
				htim3.Instance ->CCR3 = i_3;
				HAL_Delay(30);
				i_3++;
			}if(i_2 == 45 && i_4 == 59 && i_3 == 52){
				return;
		 }
	}
}
void catchOnAuto1(int i_2,int i_3,int i_4){
	while(1){
		 if(i_2 != 25 ){  
				htim3.Instance ->CCR2 = i_2;
				HAL_Delay(30);
				i_2--;
			}else if(i_3 != 28 ){  
				htim3.Instance ->CCR3 = i_3;
				HAL_Delay(30);
				i_3--;
			}else if(i_4 != 50){
				htim3.Instance ->CCR4 = i_4;
				HAL_Delay(30);
				i_4--;
		  }else if(i_2 == 25 &&i_3 == 28 &&i_4 == 50 ){
				catchOffAuto(i_2,i_3,i_4);
			  return;
		 }
	}
}

void catchOnAuto2(int i_2,int i_3,int i_4){
	while(1){
		  if(i_4 != 35){
				htim3.Instance ->CCR4 = i_4;
				HAL_Delay(30);
				i_4--;
		  }else if(i_3 != 28 ){  
				htim3.Instance ->CCR3 = i_3;
				HAL_Delay(30);
				i_3--;
			}else if(i_2 != 25 ){  
				htim3.Instance ->CCR2 = i_2;
				HAL_Delay(30);
				i_2--;
			}if(i_2 == 25 &&i_3 == 28 &&i_4 == 35 ){
			  catchOffAuto(i_2,i_3,i_4);
			  return;
		 }
	}
}
void AutoCyle(int i_1,int i_2,int i_3,int i_4){
	while(i_1>26){
		htim3.Instance ->CCR1 = i_1;
		HAL_Delay(30);
		i_1--;
	}
	HAL_Delay(500);
	catchOnAuto2(i_2,i_3,i_4);
	HAL_Delay(500);
	while(i_1<73){
		htim3.Instance ->CCR1 = i_1;
		HAL_Delay(30);
		i_1++;
	}
}
void AutoMode(){
	int i1 = 72;
	int i2 = 45;
	int i3 = 52;
	int i4 = 59;
	reset_Start(i1,i2,i3,i4);
	if(HAL_GetTick() - delay >=100){
			delay = HAL_GetTick();
			echo2 = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2);
			dist2 = echo2 / 58.0f;
			//printf("Echo2: %u  dist2: %.2f    \r\n",echo2,dist2);
			displayLCD_auto_mode(dist2);
			if(dist2 <6.00){
					catchOnAuto1(i2,i3,i4);
					HAL_Delay(500);
					AutoCyle(i1,i2,i3,i4);
			}	
	 }
}
/******************Auto Mode end*****************************/

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
