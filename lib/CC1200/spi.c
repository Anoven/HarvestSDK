#include "spi.h"

uint8_t SPIRx[RXTXBufferSize];
uint8_t SPITx[RXTXBufferSize]={0};

void spi2_init(unsigned int clocksettings) {

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); //done in pins
    // Reset SPI Interface
    SPI_I2S_DeInit(CC1200_SPI);

	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(CC1200_SPI, &SPI_InitStructure);

	/* Enable SPI */
	SPI_Cmd(CC1200_SPI, ENABLE);
}



void SPI_Slave_and_DMA_Configuration(void)
{
    SPI_InitTypeDef SPI_InitStructure; //Variable used to setup the SPI
    DMA_InitTypeDef DMA_InitStructure; //Variable used to setup the DMA


    //--Enable the SPI2 periph
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    // Reset SPI Interface
    SPI_I2S_DeInit(SPI2);

    //== SPI2 configuration
    SPI_StructInit(&SPI_InitStructure);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure);


    //--Enable DMA1 clock--
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    //==Configure DMA1 - Channel4== (SPI -> memory)
    DMA_DeInit(DMA1_Channel4); //Set DMA registers to default values
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR; //Address of peripheral the DMA must map to
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&SPIRx;//Variable to which received data will be stored
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = RXTXBufferSize; //Buffer size
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure); //Initialise the DMA
    DMA_Cmd(DMA1_Channel4, ENABLE); //Enable the DMA1 - Channel4

    //==Configure DMA1 - Channel5== (memory -> SPI)
    DMA_DeInit(DMA1_Channel5); //Set DMA registers to default values
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPI2->DR; //Address of peripheral the DMA must map to
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&SPITx;  //Variable from which data will be transmitted
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = RXTXBufferSize; //Buffer size
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure); //Initialise the DMA
    DMA_Cmd(DMA1_Channel5, ENABLE); //Enable the DMA1 - Channel5

    // Enable SPI2
    SPI_Cmd(SPI2, ENABLE);

    // Enable the SPI2 RX & TX DMA requests
    SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx | SPI_I2S_DMAReq_Tx, ENABLE);

    DMA_ITConfig(DMA1_Channel4, DMA_IT_TC|DMA_IT_HT, ENABLE);

}

/*void spi2_init(unsigned int clocksettings) {
	SPI_InitTypeDef SPI_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(CC1200_SPI, &SPI_InitStructure);
	 Enable SPI
	SPI_Cmd(RPI_SPI, ENABLE);
}*/
unsigned char rf_spi_send_receive(unsigned char send) {
	/* nSS signal activation - low */

	/* SPI byte send */
	SPI_I2S_SendData(CC1200_SPI, send);
	/* Wait for SPIx Busy flag */
	while (SPI_I2S_GetFlagStatus(CC1200_SPI, SPI_I2S_FLAG_BSY) != RESET);
	/* nSS signal deactivation - high */

	return((uint8_t)(SPI_I2S_ReceiveData(CC1200_SPI)));
}

void cc1200_select( void ){
  	GPIO_ResetBits(CC1200_nSS_Port, CC1200_nSS_Pin);
}

void cc1200_unselect( void ) {
  	//for(int i=0;i<100;i++);
	GPIO_SetBits(CC1200_nSS_Port, CC1200_nSS_Pin);
}

void cc1200_wait_miso( void ){
  while(GPIO_ReadInputDataBit(CC1200_SPI_PORT, CC1200_MISO_Pin)!= RESET);
}
