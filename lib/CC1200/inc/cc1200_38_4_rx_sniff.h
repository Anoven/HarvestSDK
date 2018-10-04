//from cheap temp sensor, works tho LOL

static const registerSetting_t preferredSettings[]=
{
  {CC120X_IOCFG0,            0x06},
  {CC120X_IOCFG2,            0x13},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x99},
  {CC120X_MODCFG_DEV_E,      0x05},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x02},
  {CC120X_MDMCFG1,           0x42},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0xC9},
  {CC120X_SYMBOL_RATE1,      0x99},
  {CC120X_SYMBOL_RATE0,      0x99},
  {CC120X_AGC_REF,           0x2F},
  {CC120X_AGC_CS_THR,        0xEC},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG1,          0x13},   // Address checking
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},
  {CC120X_FREQ2,             0x5B}, //5B #915MHz
  {CC120X_FREQ1,             0x80}, //80
  {CC120X_FREQ0,             0x00},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x04},
  {CC120X_FS_DIG0,           0x50},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC1,           0xF7},
  {CC120X_FS_DVC0,           0x0F},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
};

// // Bit rate = 38.4
// // Deviation = 19.989014
// // Modulation format = 2-GFSK
// // RX filter BW = 104.166667
// // Packet length = 255
// // Address config = No address check
// // Packet length mode = Variable
// // Packet bit length = 0
// // Carrier frequency = 915.000000
// // Manchester enable = false
// // Whitening = false
// // Symbol rate = 38.4
// // Device address = 0
//

// Address Config = No address check
// Bit Rate = 38.4
// Carrier Frequency = 915.000000
// Deviation = 19.989014
// Device Address = 0
// Manchester Enable = false
// Modulation Format = 2-GFSK
// Packet Bit Length = 0
// Packet Length = 255
// Packet Length Mode = Variable
// RX Filter BW = 104.166667
// Symbol rate = 38.4
// Whitening = false


// Address Config = No address check
// Bit Rate = 50
// Carrier Frequency = 867.999878
// Deviation = 24.948120
// Device Address = 0
// Manchester Enable = false
// Modulation Format = 2-GFSK
// Packet Bit Length = 0
// Packet Length = 255
// Packet Length Mode = Variable
// RX Filter BW = 104.166667
// Symbol rate = 50
// Whitening = false


/*
static const registerSetting_t preferredSettings[]=
{
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC3,             0x55},
  {CC120X_SYNC2,             0x55},
  {CC120X_SYNC1,             0x7A},
  {CC120X_SYNC0,             0x0E},
  {CC120X_SYNC_CFG1,         0x48},
  {CC120X_SYNC_CFG0,         0x23},
  {CC120X_DEVIATION_M,       0x47},
  {CC120X_MODCFG_DEV_E,      0x0B},
  {CC120X_DCFILT_CFG,        0x56},
  {CC120X_PREAMBLE_CFG0,     0xBA},
  {CC120X_IQIC,              0xC8},
  {CC120X_CHAN_BW,           0x84},
  {CC120X_MDMCFG1,           0x40},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x94},
  {CC120X_SYMBOL_RATE1,      0x7A},
  {CC120X_SYMBOL_RATE0,      0xE1},
  {CC120X_AGC_REF,           0x3E},
  {CC120X_AGC_CS_THR,        0xF1},
  {CC120X_AGC_CFG1,          0x11},
  {CC120X_AGC_CFG0,          0x90},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_PA_CFG1,           0x77},
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x02},
  {CC120X_FREQ2,             0x56},
  {CC120X_FREQ1,             0xCC},
  {CC120X_FREQ0,             0xCC},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xAA},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x05},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
};
*/

/*
static const registerSetting_t preferredSettings[]=
{
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA9},
  {CC120X_MODCFG_DEV_E,      0x0B},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0xC8},
  {CC120X_CHAN_BW,           0x10},
  {CC120X_MDMCFG1,           0x42},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x8F},
  {CC120X_SYMBOL_RATE1,      0x75},
  {CC120X_SYMBOL_RATE0,      0x10},
  {CC120X_AGC_REF,           0x27},
  {CC120X_AGC_CS_THR,        0x01},
  {CC120X_AGC_CFG1,          0x11},
  {CC120X_AGC_CFG0,          0x94},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_PA_CFG1,           0x77},
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x1C},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x02},
  {CC120X_FREQ2,             0x5B},
  {CC120X_FREQ1,             0x80},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x04},
  {CC120X_FS_DIG0,           0x55},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x09},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
};
*/

// Address Config = Address check, 0x00 broadcast
// Bit Rate = 1000
// Carrier Frequency = 914.991760
// Deviation = 399.169922
// Device Address = 0
// Manchester Enable = false
// Modulation Format = 4-GFSK
// Packet Bit Length = 0
// Packet Length = 255
// Packet Length Mode = Variable
// RX Filter BW = 1666.666667
// Symbol rate = 500
// Whitening = false
//Sends but doesn't receive (at least it seems like it sends)
/*
static const registerSetting_t preferredSettings[]=
{
  {CC120X_IOCFG3,            0x30},
  {CC120X_IOCFG2,            0x06},
  {CC120X_IOCFG0,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_MODCFG_DEV_E,      0x2F},
  {CC120X_PREAMBLE_CFG1,     0x30},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x01},
  {CC120X_MDMCFG1,           0x42},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0xC9},
  {CC120X_SYMBOL_RATE1,      0x99},
  {CC120X_SYMBOL_RATE0,      0x99},
  {CC120X_AGC_REF,           0x2F},
  {CC120X_AGC_CS_THR,        0xF8},
  {CC120X_AGC_CFG1,          0x00},
  {CC120X_AGC_CFG0,          0x80},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_SETTLING_CFG,      0x03},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG1,          0x03},
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_RFEND_CFG0,        0x09},
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x1C},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},
  {CC120X_FREQ2,             0x5B},
  {CC120X_FREQ1,             0x7F},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xA0},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
};*/
/*
static const registerSetting_t preferredSettings[]=
{
  {CC120X_IOCFG2,            0x08},
  {CC120X_IOCFG0,            0x09},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x23},
  {CC120X_DEVIATION_M,       0x47},
  {CC120X_MODCFG_DEV_E,      0x0C},
  {CC120X_DCFILT_CFG,        0x4B},
  {CC120X_PREAMBLE_CFG1,     0x00},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0xD8},
  {CC120X_CHAN_BW,           0x08},
  {CC120X_MDMCFG1,           0x06},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0xA4},
  {CC120X_SYMBOL_RATE1,      0x7A},
  {CC120X_SYMBOL_RATE0,      0xE1},
  {CC120X_AGC_REF,           0x2A},
  {CC120X_AGC_CS_THR,        0xF6},
  {CC120X_AGC_CFG1,          0x12},
  {CC120X_AGC_CFG0,          0x80},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x14},
  {CC120X_PKT_CFG2,          0x01},
  {CC120X_PKT_CFG1,          0x00},
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x1C},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x02},
  {CC120X_FREQ2,             0x56},
  {CC120X_FREQ1,             0xCC},
  {CC120X_FREQ0,             0xCC},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x04},
  {CC120X_FS_DIG0,           0x50},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC1,           0xF7},
  {CC120X_FS_DVC0,           0x0F},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x09},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
  {CC120X_SERIAL_STATUS,     0x08},
};
*/
/*
static const registerSetting_t preferredSettings[]= 
{
  {CC120X_IOCFG2,            0x06},
  {CC120X_SYNC_CFG1,         0xA8},
  {CC120X_SYNC_CFG0,         0x13},
  {CC120X_DEVIATION_M,       0x99},
  {CC120X_MODCFG_DEV_E,      0x05},
  {CC120X_DCFILT_CFG,        0x26},
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0x00},
  {CC120X_CHAN_BW,           0x02},
  {CC120X_MDMCFG1,           0x42},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0xC9},
  {CC120X_SYMBOL_RATE1,      0x99},
  {CC120X_SYMBOL_RATE0,      0x99},
  {CC120X_AGC_REF,           0x2F},
  {CC120X_AGC_CS_THR,        0xEC},
  {CC120X_AGC_CFG1,          0x16},
  {CC120X_AGC_CFG0,          0x84},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_FS_CFG,            0x12},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},
  {CC120X_FREQ2,             0x56},
  {CC120X_FREQ1,             0xCC},
  {CC120X_FREQ0,             0xCC},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x04},
  {CC120X_FS_DIG0,           0x50},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC1,           0xF7},
  {CC120X_FS_DVC0,           0x0F},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x0D},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
};
*/

//Koshy's legit one
/*
static const registerSetting_t preferredSettings[]=
{
  {CC120X_IOCFG0,            0x06},
  {CC120X_IOCFG2,            0x13},
  {CC120X_IOCFG3,            0x30},
  {CC120X_SYNC_CFG1,         0xA9},
  {CC120X_MODCFG_DEV_E,      0x0B},
  {CC120X_PREAMBLE_CFG1,     0x30}, //24 byte preamble
  {CC120X_PREAMBLE_CFG0,     0x8A},
  {CC120X_IQIC,              0xC8},
  {CC120X_CHAN_BW,           0x10},
  {CC120X_MDMCFG1,           0x42},
  {CC120X_MDMCFG0,           0x05},
  {CC120X_SYMBOL_RATE2,      0x8F},
  {CC120X_SYMBOL_RATE1,      0x75},
  {CC120X_SYMBOL_RATE0,      0x10},
  {CC120X_AGC_REF,           0x27},
  {CC120X_AGC_CS_THR,        0xE4},
  {CC120X_AGC_CFG1,          0x11}, //0x11
  {CC120X_AGC_CFG0,          0x94},
  {CC120X_FIFO_CFG,          0x00},
  {CC120X_SETTLING_CFG,      0x0B},
  {CC120X_FS_CFG,            0x12},
  //{CC120X_WOR_CFG1,          0x08}, //normal mode
  //{CC120X_WOR_CFG0,          0x21},
  //{CC120X_WOR_EVENT0_LSB,    0x21},
  {CC120X_PKT_CFG2,          0x00},
  {CC120X_PKT_CFG1,          0x13},   // Address checking, no broadcast
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_RFEND_CFG0,        0x00}, //0x30=TXOFF_MODE = RX ie radio goes straight to rx after tx , and terminate on bad packet (OFF)
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x1C},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x02},
  {CC120X_FREQ2,             0x5B},
  {CC120X_FREQ1,             0x70},
  {CC120X_IF_ADC1,           0xEE},
  {CC120X_IF_ADC0,           0x10},
  {CC120X_FS_DIG1,           0x07},
  {CC120X_FS_DIG0,           0xAF},
  {CC120X_FS_CAL1,           0x40},
  {CC120X_FS_CAL0,           0x0E},
  {CC120X_FS_DIVTWO,         0x03},
  {CC120X_FS_DSM0,           0x33},
  {CC120X_FS_DVC0,           0x17},
  {CC120X_FS_PFD,            0x00},
  {CC120X_FS_PRE,            0x6E},
  {CC120X_FS_REG_DIV_CML,    0x1C},
  {CC120X_FS_SPARE,          0xAC},
  {CC120X_FS_VCO0,           0xB5},
  {CC120X_IFAMP,             0x09},
  {CC120X_XOSC5,             0x0E},
  {CC120X_XOSC1,             0x03},
};*/

// Bit rate = 38.4
// Deviation = 19.989014
// Modulation format = 2-GFSK
// RX filter BW = 104.166667
// Packet length = 255
// Address config = No address check
// Packet length mode = Variable
// Packet bit length = 0
// Carrier frequency = 915.000000
// Manchester enable = false
// Whitening = false
// Symbol rate = 38.4
// Device address = 0

// static const registerSetting_t preferredSettings[]=
// {
//   {CC120X_IOCFG0,            0x06},
//   {CC120X_IOCFG2,            0x13},
//   {CC120X_SYNC_CFG1,         0xA9},
//   {CC120X_MODCFG_DEV_E,      0x0B},
//   {CC120X_PREAMBLE_CFG1,     0x30}, //24 byte preamble
//   {CC120X_PREAMBLE_CFG0,     0x8A},
//   {CC120X_IQIC,              0xC8},
//   {CC120X_CHAN_BW,           0x10},
//   {CC120X_MDMCFG1,           0x42},
//   {CC120X_MDMCFG0,           0x05},
//   {CC120X_SYMBOL_RATE2,      0x8F},
//   {CC120X_SYMBOL_RATE1,      0x75},
//   {CC120X_SYMBOL_RATE0,      0x10},
//   {CC120X_AGC_REF,           0x27},
//   {CC120X_AGC_CS_THR,        0xE4},
//   {CC120X_AGC_CFG1,          0x11}, //00
//   {CC120X_AGC_CFG0,          0x94}, //90
//   {CC120X_FIFO_CFG,          0x00},
//   {CC120X_SETTLING_CFG,      0x03},
//   {CC120X_FS_CFG,            0x12},
//   {CC120X_WOR_CFG0,          0x20},
//   {CC120X_WOR_EVENT0_LSB,    0xC3},
//   {CC120X_PKT_CFG2,          0x00},
//   {CC120X_PKT_CFG1,          0x13},   // Address checking
//   {CC120X_PKT_CFG0,          0x20},
//   {CC120X_RFEND_CFG0,        0x00},
//   {CC120X_PKT_LEN,           0xFF},
//   {CC120X_IF_MIX_CFG,        0x1C},
//   {CC120X_TOC_CFG,           0x03},
//   {CC120X_MDMCFG2,           0x02},
//   {CC120X_FREQ2,             0x5B},
//   {CC120X_FREQ1,             0x80},
//   {CC120X_IF_ADC1,           0xEE},
//   {CC120X_IF_ADC0,           0x10},
//   {CC120X_FS_DIG1,           0x07},
//   {CC120X_FS_DIG0,           0xAF},
//   {CC120X_FS_CAL1,           0x40},
//   {CC120X_FS_CAL0,           0x0E},
//   {CC120X_FS_DIVTWO,         0x03},
//   {CC120X_FS_DSM0,           0x33},
//   {CC120X_FS_DVC0,           0x17},
//   {CC120X_FS_PFD,            0x00},
//   {CC120X_FS_PRE,            0x6E},
//   {CC120X_FS_REG_DIV_CML,    0x1C},
//   {CC120X_FS_SPARE,          0xAC},
//   {CC120X_FS_VCO0,           0xB5},
//   {CC120X_IFAMP,             0x09},
//   {CC120X_XOSC5,             0x0E},
//   {CC120X_XOSC1,             0x03},
// };
