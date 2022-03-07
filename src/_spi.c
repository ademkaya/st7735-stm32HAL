#include "_spi.h"

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi);
static SPI_HandleTypeDef* stc_spi_handle = NULL;
static void SPI_TX_sw(uint8_t* TXdata,uint32_t size);
static void SPI_RX_sw(uint8_t* RXdata,uint32_t size);
static void delay(uint16_t ticks);

#if (_SPI_MODE_==BIDIRECTIONAL)
	static bool MOSI_IN = false;
#endif

static inline void MOSI__SetInput(void);
static inline void MOSI__SetOutput(void);
static inline void SPI_SCK_LOW(void);
static inline void SPI_MOSI_LOW(void);
static inline void SPI_MOSI_HIGH(void);
static inline void SPI_SCK_HIGH(void);
static inline void SPI_READ(uint8_t* dataRX,uint8_t i);

bool SPI_INIT(SPI_HandleTypeDef* spi_handle)
{	
	if (spi_handle!=NULL)
	{
			stc_spi_handle = spi_handle;
		
			/* SPI1 parameter configuration*/
			spi_handle->Instance = SPI_MODULE;
			spi_handle->Init.Mode = SPI_MODE_MASTER;
		
			#if (_SPI_MODE_==BIDIRECTIONAL)
				spi_handle->Init.Direction = SPI_DIRECTION_1LINE;
			#elif (_SPI_MODE_==FULL_DUPLEX)
				spi_handle->Init.Direction = SPI_DIRECTION_2LINES;
			#endif
		
		
			spi_handle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
			spi_handle->Init.DataSize = SPI_DATASIZE_8BIT;
			spi_handle->Init.CLKPolarity = SPI_POLARITY_LOW;
			spi_handle->Init.CLKPhase = SPI_PHASE_1EDGE;
			spi_handle->Init.NSS = SPI_NSS_SOFT;		
			spi_handle->Init.FirstBit = SPI_FIRSTBIT_MSB;
			spi_handle->Init.TIMode = SPI_TIMODE_DISABLE;
			spi_handle->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
			spi_handle->Init.CRCPolynomial = 10;
			if (HAL_SPI_Init(spi_handle) != HAL_OK)
			{
				return false;
			}		

	}
	else{
	
			stc_spi_handle = NULL;

			GPIO_InitTypeDef GPIO_InitStruct = {0};
			
			SPI_GPIO_PORT_CLK();				
			
			
				GPIO_InitStruct.Pin 			= SPI_SCK|SPI_MOSI;
				GPIO_InitStruct.Mode 			= GPIO_MODE_OUTPUT_PP;
				GPIO_InitStruct.Pull 			= GPIO_PULLDOWN;//GPIO_NOPULL;
				GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
				HAL_GPIO_Init(SPI_PORT, &GPIO_InitStruct);			
			
			#if (_SPI_MODE_==FULL_DUPLEX)	
				GPIO_InitStruct.Pin 			= SPI_MISO;
				GPIO_InitStruct.Mode 			= GPIO_MODE_INPUT;
				GPIO_InitStruct.Pull 			= GPIO_NOPULL;
				GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
				HAL_GPIO_Init(SPI_PORT, &GPIO_InitStruct);			
			#endif			
			
			SPI_CS_PORT_CLK();				
			GPIO_InitStruct.Pin 			= SPI_CS;
			GPIO_InitStruct.Mode 			= GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull 			= GPIO_PULLUP;
			GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
			HAL_GPIO_Init(SPI_CS_PORT, &GPIO_InitStruct);

	}
	return true;
}

void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

			GPIO_InitTypeDef GPIO_InitStruct = {0};
		
			SPI_PORT_CLK();
			SPI_GPIO_PORT_CLK();				
			
			#if (_SPI_MODE_==BIDIRECTIONAL)
				GPIO_InitStruct.Pin 			= SPI_SCK|SPI_MOSI;
			#elif (_SPI_MODE_==FULL_DUPLEX)
				GPIO_InitStruct.Pin 			= SPI_SCK|SPI_MISO|SPI_MOSI;
			#endif
			
			GPIO_InitStruct.Mode 			= GPIO_MODE_AF_PP;
			GPIO_InitStruct.Pull 			= GPIO_NOPULL;
			GPIO_InitStruct.Speed 		= GPIO_SPEED_FREQ_VERY_HIGH;
			GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
			HAL_GPIO_Init(SPI_PORT, &GPIO_InitStruct);				
 				
			SPI_CS_PORT_CLK();				
			GPIO_InitStruct.Pin 	= SPI_CS;
			GPIO_InitStruct.Mode 	= GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull 	= GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
			HAL_GPIO_Init(SPI_CS_PORT, &GPIO_InitStruct);

}


void SPI_TX(uint8_t* txdata,uint32_t size){
	if (stc_spi_handle!=NULL)
		HAL_SPI_Transmit(stc_spi_handle, txdata,size, 1000);
	else
	{		
		// software spi
		SPI_TX_sw( txdata,size);
	}
}

void SPI_RX(uint8_t* rxdata,uint32_t size){
	if (stc_spi_handle!=NULL)
		HAL_SPI_Receive(stc_spi_handle, rxdata,size, 1000);
	else
	{		
		// software spi
		SPI_RX_sw( rxdata,size);
	}
}

static void SPI_TX_sw(uint8_t* TXdata,uint32_t size){

	#define mode2
	
	#if (_SPI_MODE_==BIDIRECTIONAL)
		if (MOSI_IN) 			// input
			MOSI__SetOutput();
	#endif
	
	for(uint16_t i  =0;i< size;i++)
	{
			for(uint16_t b  =0;b< 8;b++)
			{
				#ifdef mode1
					SPI_SCK_LOW();
					delay(1);
					SPI_SCK_HIGH();
				#endif 
				
				#ifdef mode3
					SPI_SCK_HIGH();
					delay(1);
					SPI_SCK_LOW();
				#endif
				
					bool r = (bool)((TXdata[i]>>(7-b))&0x01);
					if (r)
						SPI_MOSI_HIGH();
					else
						SPI_MOSI_LOW();		
				
				#ifdef mode0
					SPI_SCK_LOW();
					SPI_SCK_HIGH();
				#endif
				
				#ifdef mode2
					SPI_SCK_HIGH();										
					SPI_SCK_LOW();
				#endif
			}
	}
}

static void SPI_RX_sw(uint8_t* RXdata,uint32_t size){

	#if (_SPI_MODE_==BIDIRECTIONAL)
		if (!MOSI_IN)	//output
			MOSI__SetInput();
	#endif
	
	uint8_t dataRX = 0;
	for(uint16_t i  =0;i< size;i++)
	{
			for(uint16_t b  =0;b< 8;b++)
			{
					SPI_SCK_HIGH();			
						SPI_READ(&dataRX,b);
					SPI_SCK_LOW();
			}
			RXdata[i] = dataRX;
	}
}

void SPI_CS_LOW(void){
	SPI_PORT->BSRR = (uint32_t)SPI_CS << 16U;
}
void SPI_CS_HIGH(void){
	SPI_PORT->BSRR = SPI_CS;
}

static inline void SPI_SCK_HIGH(void){
SPI_PORT->BSRR = (uint32_t)SPI_SCK;
}
static inline void SPI_SCK_LOW(void){
SPI_PORT->BSRR = (uint32_t)SPI_SCK << 16U;
}
static inline void SPI_MOSI_LOW(void){
	SPI_PORT->BSRR = (uint32_t)SPI_MOSI << 16U;
}
static inline void SPI_MOSI_HIGH(void){
	SPI_PORT->BSRR = SPI_MOSI;
}
static inline void SPI_READ(uint8_t* dataRX,uint8_t i){
	
	if (SPI_PORT->IDR & SPI_MISO)
			*dataRX |= (0x01 << (7-i));
	else
			*dataRX &= ~(0x01 << (7-i));
	
}

static inline void MOSI__SetInput(void){
	
  GPIO_InitTypeDef  GPIO_InitStruct;
  
	SPI_PORT_CLK();
	SPI_GPIO_PORT_CLK();
	
  GPIO_InitStruct.Pin = SPI_MOSI;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  
  HAL_GPIO_Init(SPI_PORT, &GPIO_InitStruct);
	
	MOSI_IN = true;
	
}

static inline void MOSI__SetOutput(void){
	
  GPIO_InitTypeDef  GPIO_InitStruct;
  
	SPI_PORT_CLK();
	SPI_GPIO_PORT_CLK();
	
  GPIO_InitStruct.Pin = SPI_MOSI;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  
  HAL_GPIO_Init(SPI_PORT, &GPIO_InitStruct);
	
	MOSI_IN = false;
}


static void delay(uint16_t ticks){
	for(uint16_t i  =0;i< ticks;i++){
		__NOP();
	}
}
