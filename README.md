# st7735-stm32HAL
st7735 library for stm32 using stm32-hal library's.
library includes both hardware and software spi implementations

## Usage

Usage is straightforward just add spi.c & _st7735.c and their header files into the project. 
Repsitory is excluded the HAL library files, so user should add the required files themselves.

```
#include "_st7735.h"
#include "_spi.h"

SPI_HandleTypeDef 	hspi1;

int main(void)
{
  // ...
  
	SPI_INIT(&hspi1);
	//SPI_INIT(NULL); // <<< software spi call
	
	ST7735_INIT();
	ST7735_SetColor(0,0,scr_width,scr_height,0x0000);

	uint8_t r=0;
	uint8_t g=0;
	uint8_t b=0;


	ST7735_SetImage(&rgbArray[0]);	
					
	while(1)
	{		
		for(int y = 0;y<scr_height;y++){			
			rainbowValues(&r, &g,&b,true);
			for(int x = 0;x<scr_width;x++){
				rainbowValues(&r, &g,&b,false);	
				ST7735_SetPixel(x, y, ST7735_Color565(r,g,b));
			}
		}
	}
	
}

```
