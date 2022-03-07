#ifndef __ST7735_H
#define __ST7735_H

#include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

#define uSecTickValue											(uint16_t)(192)		
#define d_SPI_TX(data_pointer,size_data)	SPI_TX((uint8_t*)data_pointer,size_data)


#define DC_PORT						GPIOA
#define DC_PORT_CLK()			__HAL_RCC_GPIOA_CLK_ENABLE()
#define DC_PIN						GPIO_PIN_3

#define RST_PORT					GPIOA
#define RST_PORT_CLK()		__HAL_RCC_GPIOA_CLK_ENABLE()
#define RST_PIN						GPIO_PIN_2


// DC pin macros
#define DC_L() 						DC_PORT->BSRR = (uint32_t)DC_PIN << 16U
#define DC_H() 						DC_PORT->BSRR = DC_PIN

// RESET pin macros
#define RST_L() 					RST_PORT->BSRR = (uint32_t)RST_PIN << 16U
#define RST_H() 					RST_PORT->BSRR = RST_PIN



#define scr_width         128
#define scr_height        160

#define ST7735_INVOFF  			0x20
#define ST7735_INVON   			0x21
#define ST7735_SOFTRESET		0x01
#define ST7735_IDLE_MODEON	0x39
#define ST7735_IDLE_MODEOFF	0x38



void 		 ST7735_INIT(void);

void 		 ST7735_write(uint8_t w);
void 		 ST7735_SetPixel(uint16_t X, uint16_t Y, uint16_t color);
void 		 ST7735_AddrSet(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE);


void 		 ST7735_SetImage(uint16_t* array);
void 		 ST7735_SetColor(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE,uint16_t color);

void 		 ST7735_InvertDisplay(const uint8_t mode);

uint16_t ST7735_Color565(uint8_t r, uint8_t g, uint8_t b);
void 		 rainbowValues(uint8_t* r, uint8_t* g, uint8_t* b,bool reset);



#endif
