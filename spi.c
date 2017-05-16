#include "spi.h"

void SPI_config(uint32_t RCC_APB_SPI,uint32_t RCC_AHB_SPI,GPIO_TypeDef* GPIOx_SPI,GPIO_TypeDef* GPIOx_CS,uint16_t GPIO_PinSPI,uint16_t GPIO_PinCS,
				uint16_t GPIO_PinSourceSCK,uint16_t GPIO_PinSourceMISO,uint16_t GPIO_PinSourceMOSI,uint8_t GPIO_AF,SPI_TypeDef* SPIx)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	// enable clock for used IO pins SCK MISO MOSI CS
	RCC_AHB1PeriphClockCmd(RCC_AHB_SPI, ENABLE);
	
	/* configure pins used by SPI1
	 * PA5 = SCK
	 * PA6 = MISO
	 * PA7 = MOSI
	 */
	GPIO_InitStruct.GPIO_Pin = GPIO_PinSPI;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOx_SPI, &GPIO_InitStruct);
	
	// connect SPI1 pins to SPI alternate function
	GPIO_PinAFConfig(GPIOx_SPI, GPIO_PinSourceSCK, GPIO_AF);
	GPIO_PinAFConfig(GPIOx_SPI, GPIO_PinSourceMISO, GPIO_AF);
	GPIO_PinAFConfig(GPIOx_SPI, GPIO_PinSourceMOSI, GPIO_AF);
	
	// enable clock for used IO pins
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	/* Configure the chip select pin
	   in this case we will use PE7 */
	GPIO_InitStruct.GPIO_Pin = GPIO_PinCS;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOx_CS, &GPIO_InitStruct);
	
	GPIOE->BSRRL |= GPIO_PinCS; // set PE7 high
	
	// enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB_SPI, ENABLE);
	
	/* configure SPI1 in Mode 0 
	 * CPOL = 0 --> clock is low when idle
	 * CPHA = 0 --> data is sampled at the first edge
	 */
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first
	SPI_Init(SPIx, &SPI_InitStruct); 
	
	SPI_Cmd(SPIx, ENABLE); // enable SPI1
}

void SPI_send(SPI_TypeDef* SPIx,uint8_t address, uint8_t data)
{
  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, address);
  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
  SPI_I2S_ReceiveData(SPI1);

  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, data);
  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
  SPI_I2S_ReceiveData(SPIx);
}

uint8_t SPI_read(SPI_TypeDef* SPIx,uint8_t address)
{
  address = 0x80 | address;                         // 0b10 - reading and clearing status

  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, address);
  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
  SPI_I2S_ReceiveData(SPI1);

  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, 0x00);
  while(SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);

  return SPI_I2S_ReceiveData(SPIx);
}
