
#include "_spi.h"
#include "_st7735.h"

// some part of the code is based on https://github.com/LonelyWolf/stm32/tree/master/ST7735

static void ST7735_write(uint8_t w);
static void ST7735_data(uint8_t d);
static void ST7735_cmd(uint8_t c);
static void Delay_us(uint16_t d,uint16_t uSecTick);



void ST7735_INIT(void)
{
	
	 	GPIO_InitTypeDef GPIO_InitStruct = {0};			
		DC_PORT_CLK();
		GPIO_InitStruct.Pin 	= DC_PIN;
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull 	= GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		HAL_GPIO_Init(DC_PORT, &GPIO_InitStruct);
	
		RST_PORT_CLK();
		GPIO_InitStruct.Pin 	= RST_PIN;
		GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull 	= GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		HAL_GPIO_Init(RST_PORT, &GPIO_InitStruct);
		
	
  // Reset display
SPI_CS_HIGH();
  RST_H();
  Delay_us(5,uSecTickValue);
  RST_L();
  Delay_us(5,uSecTickValue);
  RST_H();
SPI_CS_HIGH();
  Delay_us(5,uSecTickValue);
SPI_CS_LOW();

  ST7735_cmd(0x11);     // Sleep out, booster on
  Delay_us(20,uSecTickValue);

  ST7735_cmd(0xb1);     // In normal mode (full colors):

  DC_H();
  ST7735_write(0x05);   //   RTNA set 1-line period: RTNA2, RTNA0
  ST7735_write(0x3c);   //   Front porch: FPA5,FPA4,FPA3,FPA2
  ST7735_write(0x3c);   //   Back porch: BPA5,BPA4,BPA3,BPA2

  ST7735_cmd(0xb2);     // In idle mode (8-colors):
  DC_H();
  ST7735_write(0x05);   //   RTNB set 1-line period: RTNAB, RTNB0
  ST7735_write(0x3c);   //   Front porch: FPB5,FPB4,FPB3,FPB2
  ST7735_write(0x3c);   //   Back porch: BPB5,BPB4,BPB3,BPB2

  ST7735_cmd(0xb3);     // In partial mode + full colors:
  DC_H();
  ST7735_write(0x05);   //   RTNC set 1-line period: RTNC2, RTNC0
  ST7735_write(0x3c);   //   Front porch: FPC5,FPC4,FPC3,FPC2
  ST7735_write(0x3c);   //   Back porch: BPC5,BPC4,BPC3,BPC2
  ST7735_write(0x05);   //   RTND set 1-line period: RTND2, RTND0
  ST7735_write(0x3c);   //   Front porch: FPD5,FPD4,FPD3,FPD2
  ST7735_write(0x3c);   //   Back porch: BPD5,BPD4,BPD3,BPD2


  ST7735_cmd(0xB4);     // 	Display dot inversion control:
  ST7735_data(0x03);    //   NLB,NLC

  ST7735_cmd(0x3a);     // Interface pixel format
	//ST7735_data(0x03);   // 12-bit/pixel RGB 4-4-4 (4k colors)
	ST7735_data(0x05);    	// 16-bit/pixel RGB 5-6-5 (65k colors)
	//ST7735_data(0x06);   // 18-bit/pixel RGB 6-6-6 (256k colors)

	ST7735_cmd(0x36);     // Memory data access control:
                        // MY MX MV ML RGB MH - -
	//ST7735_data(0x00);    // Normal: Top to Bottom; Left to Right; RGB
	//ST7735_data(0x80);    // Y-Mirror: Bottom to top; Left to Right; RGB
	//ST7735_data(0x40);  // X-Mirror: Top to Bottom; Right to Left; RGB
	ST7735_data(0xc0);    	// X-Mirror,Y-Mirror: Bottom to top; Right to left; RGB
	//ST7735_data(0x20);    // X-Y Exchange: X and Y changed positions
	//ST7735_data(0xA0);    // X-Y Exchange,Y-Mirror
	//ST7735_data(0x60);    // X-Y Exchange,X-Mirror
	//ST7735_data(0xE0);    // X-Y Exchange,X-Mirror,Y-Mirror

	 ST7735_cmd(0x20);    // Display inversion off
	//ST7735_cmd(0x21);    // Display inversion on

  ST7735_cmd(0x13);     // Partial mode off

  ST7735_cmd(0x26);     // Gamma curve set:
  //ST7735_data(0x01);   // Gamma curve 1 (G2.2) or (G1.0)
	//ST7735_data(0x02);    // Gamma curve 2 (G1.8) or (G2.5)
	//ST7735_data(0x04);    // Gamma curve 3 (G2.5) or (G2.2)
	ST7735_data(0x08);      // Gamma curve 4 (G1.0) or (G1.8)

  ST7735_cmd(0x29);     // Display on
SPI_CS_HIGH();
}

static void Delay_us(uint16_t d,uint16_t uSecTick){
	uint32_t T = (d*(uSecTickValue));
	for(uint16_t i = 0;i<T;i++){
		__NOP();
	}
}

static void ST7735_cmd(uint8_t c){
		DC_L();
		ST7735_write(c);
}

static void ST7735_data(uint8_t d){
		DC_H();
		ST7735_write(d);
}

void ST7735_write(uint8_t w){
	d_SPI_TX(&w,1);
}






static void ST7735_AddrSet(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE){
  ST7735_cmd(0x2a); // Column address set
  DC_H();
  ST7735_write(XS >> 8);
  ST7735_write(XS);
  ST7735_write(XE >> 8);
  ST7735_write(XE);

  ST7735_cmd(0x2b); // Row address set
  DC_H();
  ST7735_write(YS >> 8);
  ST7735_write(YS);
  ST7735_write(YE >> 8);
  ST7735_write(YE);

  ST7735_cmd(0x2c); // Memory write
}


uint16_t ST7735_Color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


void ST7735_InvertDisplay(const uint8_t mode) {
	SPI_CS_LOW();
	ST7735_cmd(mode);
	SPI_CS_HIGH();
}
void ST7735_SetColor(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE,uint16_t color) {
	
  uint16_t i;
  uint8_t  CH,CL;

  CH = color >> 8;
  CL = (uint8_t)color;

  SPI_CS_LOW();
  ST7735_AddrSet(XS,YS,XE-1,YE-1);			// scr_width - 1,scr_height - 1
  DC_H();
  for (i = 0; i <(XE-XS)*(YE-YS) ; i++) // scr_width * scr_height
  {
    ST7735_write(CH);
    ST7735_write(CL);
  }
  SPI_CS_HIGH();
}
void ST7735_SetPixel(uint16_t X, uint16_t Y, uint16_t color){
  SPI_CS_LOW();
  ST7735_AddrSet(X,Y,X,Y);
  DC_H();
  ST7735_write(color >> 8);
  ST7735_write((uint8_t)color);
  SPI_CS_HIGH();
}

void ST7735_SetImage(uint16_t* array){	
		for(int y = 0;y<scr_height;y++){
			for(int x = 0;x<scr_width;x++){
				ST7735_SetPixel(x, y, array[y*scr_width+x]);
			}
		}
}




void rainbowValues(uint8_t* r, uint8_t* g, uint8_t* b,bool reset){
static uint8_t level =1;
uint8_t inc = 15;		// 1,5,15,17 or 51	
	if (reset){
		*r = 255;
		*g = 0;
		*b = 0;
		level = 1;		
	}	
	if (level == 1){				//G+
		*g+=inc;
		if (*g==0xFF)
			level+=1;
	}
	else if (level == 2){		//R-
		*r-=inc;
		if (*r==0)
			level+=1;
	}
	else if (level == 3){		//B+
		*b+=inc;
		if (*b==255)
			level+=1;
	}
	else if (level == 4){		//G-
		*g-=inc;
		if (*g==0)
			level+=1;
	}
	else if (level == 5){		//R+
		*r+=inc;
		if (*r==255)
			level+=1;
	}
	else if (level == 6){		//B-
		*b-=inc;
		if (*b==0)
			level=1;		
	}
}
