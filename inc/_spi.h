#ifndef __SPI_H
#define __SPI_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define BIDIRECTIONAL	1
#define FULL_DUPLEX	0
							
							
							#define _SPI_MODE_					BIDIRECTIONAL

/* common defines	*/
							#define SPI_CS_PORT					GPIOA
							#define SPI_CS_PORT_CLK()		__HAL_RCC_GPIOA_CLK_ENABLE()
							#define SPI_CS							GPIO_PIN_4

							#define	SPI_MODULE					SPI1
							#define SPI_PORT_CLK()			__HAL_RCC_SPI1_CLK_ENABLE()	
							
							#define SPI_PORT						GPIOA
							#define SPI_GPIO_PORT_CLK()	__HAL_RCC_GPIOA_CLK_ENABLE()											
							#define SPI_SCK							GPIO_PIN_5
							#define SPI_MOSI						GPIO_PIN_7
							
							#if (_SPI_MODE_==BIDIRECTIONAL)
								#define SPI_MISO						SPI_MOSI 
							#elif (_SPI_MODE_==FULL_DUPLEX)
								#define SPI_MISO						GPIO_PIN_6
							#endif


							bool SPI_INIT(SPI_HandleTypeDef* spi_handle);						// if spi_handle is NULL, starts as soft spi
							void SPI_TX(uint8_t* data,uint32_t size);
							void SPI_RX(uint8_t* rxdata,uint32_t size);
							void SPI_CS_LOW(void);
							void SPI_CS_HIGH(void);
					
					
					
					
					
					
					
					
					
					
					
					
#endif
