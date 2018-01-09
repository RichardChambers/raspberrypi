
 
#define SPI_CHAN_CONFIG_SINGLE  8
#define SPI_CHAN_CONFIG_DIFF    0
 
int spiOpen (int spiChannel, int channelConfig);
int spiClose (void);
int spiAnalogRead(int spiChannel,int channelConfig,int analogChannel);

