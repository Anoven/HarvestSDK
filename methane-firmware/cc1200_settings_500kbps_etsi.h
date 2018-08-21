#ifndef CC1200_SETTINGS_500KBPS_ETSI_H
#define CC1200_SETTINGS_500KBPS_ETSI_H

static const registerSetting_t preferredSettings[]= 
{
  {CC120X_IOCFG0,            0x06},
  {CC120X_IOCFG2,            0x13},
  {CC120X_IOCFG3,            0x30},
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
  {CC120X_PKT_CFG1,          0x0B},   // Address checking
  {CC120X_PKT_CFG0,          0x20},
  {CC120X_RFEND_CFG0,        0x30}, // TXOFF mode = RX, Drop bad packets
  {CC120X_PKT_LEN,           0xFF},
  {CC120X_IF_MIX_CFG,        0x18},
  {CC120X_TOC_CFG,           0x03},
  {CC120X_MDMCFG2,           0x00},
  {CC120X_FREQ2,             0x5B},//0x5B
  {CC120X_FREQ1,             0x80},//0x80
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

#endif
