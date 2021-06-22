#include <avr/io.h>
#include <util/delay.h>
#define _BV(x)    (1<<(x))

#include "lib_7735.h"

#define  cbi(sfr, bit) (sfr &= ~_BV(bit))
#define  sbi(sfr, bit) (sfr |= _BV(bit))
#define  tbi(a, b) ((a) & (1<<(b)))

#define ticks(x) while(--x);

// external
static void _spi_init(uint8_t mode)
{
    PORTB |= (1<<2);              // SSHI
    DDRB |= (1<<5)|(1<<3)|(1<<2); // SCK,MOSI,SS
    if (mode == 3) SPCR = (1<<CPOL)|(1<<CPHA);
    SPCR |= (1<<SPE)|(1<<MSTR)|(0<<SPR0); // Fosc/16
    SPSR = (1<<SPI2X);
}

// external
static uint8_t _spi_transfer(uint8_t c)
{
    SPDR = c;
    while ((SPSR & (1<<SPIF)) == 0);
    return SPDR;
}

void tftIOInit()
{
   sbi(TFT_CLK_DDR, TFT_CLK_PIN);
   sbi(TFT_DOUT_DDR, TFT_DOUT_PIN);
   sbi(TFT_CS_DDR, TFT_CS_PIN);
   sbi(TFT_RS_DDR, TFT_RS_PIN);
   sbi(TFT_BL_DDR, TFT_BL_PIN);

   sbi(TFT_CS_PORT, TFT_CS_PIN);
   cbi(TFT_CLK_PORT, TFT_CLK_PIN);
   cbi(TFT_DOUT_PORT, TFT_DOUT_PIN);
   cbi(TFT_RS_PORT, TFT_RS_PIN);
   cbi(TFT_BL_PORT, TFT_BL_PIN);

   sbi(TFT_RST_PORT, TFT_RST_PIN);
   sbi(TFT_RST_DDR, TFT_RST_PIN);

   spi_init(3);
}

void tftBackLight(bool state)
{
   if(state) sbi(TFT_BL_PORT, TFT_BL_PIN);
   else cbi(TFT_BL_PORT, TFT_BL_PIN);
}

void tftWriteCmd(uint8_t command)
{
   uint8_t i = 8;

   cbi(TFT_CS_PORT, TFT_CS_PIN);   /* Setup Chip Select */
   cbi(TFT_RS_PORT, TFT_RS_PIN);   /* R/S = 0 for Command */

   spi_transfer(command);
   sbi(TFT_CS_PORT, TFT_CS_PIN);   /* Deselect Chip Select */
}

void tftWriteData(uint8_t data)
{
   uint8_t i = 8;

   cbi(TFT_CS_PORT, TFT_CS_PIN);   /* Setup Chip Select */
   sbi(TFT_RS_PORT, TFT_RS_PIN);   /* R/S = 1 for Command */

   spi_transfer(data);
   sbi(TFT_CS_PORT, TFT_CS_PIN);   /* Deselect Chip Select */
}

void tftInit()
{

   tftIOInit();

   tftWriteCmd(ST7735_SWRESET); // software reset
   ticks(50);
   tftWriteCmd(ST7735_SLPOUT);  // out of sleep mode
   ticks(500);

   tftWriteCmd(ST7735_COLMOD);  // set color mode
   tftWriteData(0x05);          // 16-bit color
   ticks(10);

   tftWriteCmd(ST7735_FRMCTR1); // frame rate control
   tftWriteData(0x00);          // fastest refresh
   tftWriteData(0x06);          // 6 lines front porch
   tftWriteData(0x03);          // 3 lines backporch
   ticks(10);

   tftWriteCmd(ST7735_MADCTL);  // memory access control (directions)
   tftWriteData(0xC8);          // row address/col address, bottom to top refresh

   tftWriteCmd(ST7735_DISSET5); // display settings #5
   tftWriteData(0x15);          // 1 clock cycle nonoverlap, 2 cycle gate rise, 3 cycle oscil. equalize
   tftWriteData(0x02);          // fix on VTL

   tftWriteCmd(ST7735_INVCTR);  // display inversion control
   tftWriteData(0x0);           // line inversion
/*
   TFTWriteCmd(ST7735_PWCTR1);  // power control
   TFTWriteData(0x02);          // GVDD = 4.7V
   TFTWriteData(0x70);          // 1.0uA
   ticks(10);
   TFTWriteCmd(ST7735_PWCTR2);  // power control
   TFTWriteData(0x05);          // VGH = 14.7V, VGL = -7.35V
   TFTWriteCmd(ST7735_PWCTR3);  // power control
   TFTWriteData(0x01);          // Opamp current small
   TFTWriteData(0x02);          // Boost frequency


   TFTWriteCmd(ST7735_VMCTR1);  // power control
   TFTWriteData(0x3C);          // VCOMH = 4V
   TFTWriteData(0x38);          // VCOML = -1.1V
   ticks(10);

   TFTWriteCmd(ST7735_PWCTR6);  // power control
   TFTWriteData(0x11);
   TFTWriteData(0x15);
*/
   tftWriteCmd(ST7735_GMCTRP1);
   tftWriteData(0x09);
   tftWriteData(0x16);
   tftWriteData(0x09);
   tftWriteData(0x20);
   tftWriteData(0x21);
   tftWriteData(0x1B);
   tftWriteData(0x13);
   tftWriteData(0x19);
   tftWriteData(0x17);
   tftWriteData(0x15);
   tftWriteData(0x1E);
   tftWriteData(0x2B);
   tftWriteData(0x04);
   tftWriteData(0x05);
   tftWriteData(0x02);
   tftWriteData(0x0E);
   tftWriteCmd(ST7735_GMCTRN1);
   tftWriteData(0x0B);
   tftWriteData(0x14);
   tftWriteData(0x08);
   tftWriteData(0x1E);
   tftWriteData(0x22);
   tftWriteData(0x1D);
   tftWriteData(0x18);
   tftWriteData(0x1E);
   tftWriteData(0x1B);
   tftWriteData(0x1A);
   tftWriteData(0x24);
   tftWriteData(0x2B);
   tftWriteData(0x06);
   tftWriteData(0x06);
   tftWriteData(0x02);
   tftWriteData(0x0F);
   ticks(10);
/*
   TFTWriteCmd(ST7735_CASET);   // Set window area X
   TFTWriteData(0x00);
   TFTWriteData(0x02);
   TFTWriteData(0x00);
   TFTWriteData(0x81);

   TFTWriteCmd(ST7735_RASET);   // Set window area Y
   TFTWriteData(0x00);
   TFTWriteData(0x02);
   TFTWriteData(0x00);
   TFTWriteData(0x81);
*/
   tftWriteCmd(ST7735_NORON);   // normal display on
   ticks(10);

   tftWriteCmd(ST7735_DISPON);
   ticks(500);

   tftBackLight(1);

}

void tftSetWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
   tftWriteCmd(ST7735_CASET);   /* col address command */
   tftWriteData(0x00);
   tftWriteData(x0);          /* X Start */
   tftWriteData(0x00);
   tftWriteData(x1);          /* X end */

   tftWriteCmd(ST7735_RASET);   /* row address command */
   tftWriteData(0x00);
   tftWriteData(y0);          /* Y Start */
   tftWriteData(0x00);
   tftWriteData(y1);          /* Y end */
}

void tftPixel(uint16_t x, uint16_t y, uint16_t color)
{
   tftSetWindow(x, y, x , y);
   tftWriteCmd(ST7735_RAMWR);      /* RAM Access */
   tftWriteData(color >> 8);
   tftWriteData(color);
}
