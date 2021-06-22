#ifndef ST7735_H_
#define ST7735_H_

#define TFT_CLK_PORT   PORTB
#define TFT_CLK_PIN      5
#define TFT_CLK_DDR      DDRB
#define TFT_DOUT_PORT   PORTB
#define TFT_DOUT_PIN   3
#define TFT_DOUT_DDR   DDRB
#define TFT_CS_PORT      PORTB
#define TFT_CS_PIN      2
#define TFT_CS_DDR      DDRB
#define TFT_RS_PORT      PORTB
#define TFT_RS_PIN      1
#define TFT_RS_DDR      DDRB
#define TFT_BL_PORT     PORTB        //.kbv I have no BL
#define TFT_BL_PIN      7
#define TFT_BL_DDR      DDRB

#define TFT_RST_PORT     PORTB       //.kbv but I do have a RESET pin
#define TFT_RST_PIN      0
#define TFT_RST_DDR      DDRB

#define ST7735_NOP      (0x0)
#define ST7735_SWRESET  (0x01)
#define ST7735_SLPIN    (0x10)
#define ST7735_SLPOUT   (0x11)
#define ST7735_PTLON    (0x12)
#define ST7735_NORON    (0x13)
#define ST7735_INVOFF   (0x20)
#define ST7735_INVON    (0x21)
#define ST7735_DISPON   (0x29)
#define ST7735_CASET    (0x2A)
#define ST7735_RASET    (0x2B)
#define ST7735_RAMWR    (0x2C)
#define ST7735_COLMOD   (0x3A)
#define ST7735_MADCTL   (0x36)
#define ST7735_FRMCTR1  (0xB1)
#define ST7735_INVCTR   (0xB4)
#define ST7735_DISSET5  (0xB6)
#define ST7735_PWCTR1   (0xC0)
#define ST7735_PWCTR2   (0xC1)
#define ST7735_PWCTR3   (0xC2)
#define ST7735_VMCTR1   (0xC5)
#define ST7735_PWCTR6   (0xFC)
#define ST7735_GMCTRP1  (0xE0)
#define ST7735_GMCTRN1  (0xE1)

void tick(uint16_t i);
void tftBackLight(bool state);
void tftWriteCmd(uint8_t command);
void tftWriteData(uint8_t data);
void tftInit();
void tftIOInit();
void tftSetWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void tftPixel(uint16_t x, uint16_t y, uint16_t color);

#endif /* ST7735_H_ */  
