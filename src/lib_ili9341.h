#include <avr/io.h>

/* Level 1 Commands (from the display Datasheet) */
#define ILI9341_CMD_NOP 0x00
// 0x02
#define ILI9341_CMD_SOFTWARE_RESET 0x01
#define ILI9341_CMD_READ_DISP_ID 0x04
#define ILI9341_CMD_READ_DISP_STATUS 0x09
#define ILI9341_CMD_READ_DISP_POWER_MODE 0x0A
#define ILI9341_CMD_READ_DISP_MADCTRL 0x0B
#define ILI9341_CMD_READ_DISP_PIXEL_FORMAT 0x0C
#define ILI9341_CMD_READ_DISP_IMAGE_FORMAT 0x0D
#define ILI9341_CMD_READ_DISP_SIGNAL_MODE 0x0E
#define ILI9341_CMD_READ_DISP_SELF_DIAGNOSTIC 0x0F
#define ILI9341_CMD_ENTER_SLEEP_MODE 0x10
#define ILI9341_CMD_SLEEP_OUT 0x11
#define ILI9341_CMD_PARTIAL_MODE_ON 0x12
#define ILI9341_CMD_NORMAL_DISP_MODE_ON 0x13
#define ILI9341_CMD_DISP_INVERSION_OFF 0x20
#define ILI9341_CMD_DISP_INVERSION_ON 0x21
#define ILI9341_CMD_GAMMA_SET 0x26
#define ILI9341_CMD_DISPLAY_OFF 0x28
#define ILI9341_CMD_DISPLAY_ON 0x29
#define ILI9341_CMD_COLUMN_ADDRESS_SET 0x2A
#define ILI9341_CMD_PAGE_ADDRESS_SET 0x2B
#define ILI9341_CMD_MEMORY_WRITE 0x2C
#define ILI9341_CMD_COLOR_SET 0x2D
#define ILI9341_CMD_MEMORY_READ 0x2E
#define ILI9341_CMD_PARTIAL_AREA 0x30
#define ILI9341_CMD_VERT_SCROLL_DEFINITION 0x33
#define ILI9341_CMD_TEARING_EFFECT_LINE_OFF 0x34
#define ILI9341_CMD_TEARING_EFFECT_LINE_ON 0x35
#define ILI9341_CMD_MEMORY_ACCESS_CONTROL 0x36
#define ILI9341_CMD_VERT_SCROLL_START_ADDRESS 0x37
#define ILI9341_CMD_IDLE_MODE_OFF 0x38
#define ILI9341_CMD_IDLE_MODE_ON 0x39
#define ILI9341_CMD_COLMOD_PIXEL_FORMAT_SET 0x3A
#define ILI9341_CMD_WRITE_MEMORY_CONTINUE 0x3C
#define ILI9341_CMD_READ_MEMORY_CONTINUE 0x3E
#define ILI9341_CMD_SET_TEAR_SCANLINE 0x44
#define ILI9341_CMD_GET_SCANLINE 0x45
#define ILI9341_CMD_WRITE_DISPLAY_BRIGHTNESS 0x51
#define ILI9341_CMD_READ_DISPLAY_BRIGHTNESS 0x52
#define ILI9341_CMD_WRITE_CTRL_DISPLAY 0x53
#define ILI9341_CMD_READ_CTRL_DISPLAY 0x54
#define ILI9341_CMD_WRITE_CONTENT_ADAPT_BRIGHTNESS 0x55
#define ILI9341_CMD_READ_CONTENT_ADAPT_BRIGHTNESS 0x56
#define ILI9341_CMD_WRITE_MIN_CAB_LEVEL 0x5E
#define ILI9341_CMD_READ_MIN_CAB_LEVEL 0x5F
#define ILI9341_CMD_READ_ID1 0xDA
#define ILI9341_CMD_READ_ID2 0xDB
#define ILI9341_CMD_READ_ID3 0xDC
 
/* Level 2 Commands (from the display Datasheet) */
#define ILI9341_CMD_RGB_SIGNAL_CONTROL 0xB0
#define ILI9341_CMD_FRAME_RATE_CONTROL_NORMAL 0xB1
#define ILI9341_CMD_FRAME_RATE_CONTROL_IDLE_8COLOR 0xB2
#define ILI9341_CMD_FRAME_RATE_CONTROL_PARTIAL 0xB3
#define ILI9341_CMD_DISPLAY_INVERSION_CONTROL 0xB4
#define ILI9341_CMD_BLANKING_PORCH_CONTROL 0xB5
#define ILI9341_CMD_DISPLAY_FUNCTION_CONTROL 0xB6
#define ILI9341_CMD_ENTRY_MODE_SET 0xB7
#define ILI9341_CMD_BACKLIGHT_CONTROL_1 0xB8
#define ILI9341_CMD_BACKLIGHT_CONTROL_2 0xB9
#define ILI9341_CMD_BACKLIGHT_CONTROL_3 0xBA
#define ILI9341_CMD_BACKLIGHT_CONTROL_4 0xBB
#define ILI9341_CMD_BACKLIGHT_CONTROL_5 0xBC
#define ILI9341_CMD_BACKLIGHT_CONTROL_6 0xBD
#define ILI9341_CMD_BACKLIGHT_CONTROL_7 0xBE
#define ILI9341_CMD_BACKLIGHT_CONTROL_8 0xBF
#define ILI9341_CMD_POWER_CONTROL_1 0xC0
#define ILI9341_CMD_POWER_CONTROL_2 0xC1
#define ILI9341_CMD_VCOM_CONTROL_1 0xC5
#define ILI9341_CMD_VCOM_CONTROL_2 0xC7
#define ILI9341_CMD_POWER_ON_SEQ_CONTROL 0xCB
#define ILI9341_CMD_POWER_CONTROL_A 0xCD
#define ILI9341_CMD_POWER_CONTROL_B 0xCF
#define ILI9341_CMD_NVMEM_WRITE 0xD0
#define ILI9341_CMD_NVMEM_PROTECTION_KEY 0xD1
#define ILI9341_CMD_NVMEM_STATUS_READ 0xD2
#define ILI9341_CMD_READ_ID4 0xD3
#define ILI9341_CMD_POSITIVE_GAMMA_CORRECTION 0xE0
#define ILI9341_CMD_NEGATIVE_GAMMA_CORRECTION 0xE1
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_1 0xE2
#define ILI9341_CMD_DIGITAL_GAMMA_CONTROL_2 0xE3
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_A 0xE8
#define ILI9341_CMD_DRIVER_TIMING_CONTROL_B 0xEA
#define ILI9341_CMD_ENABLE_3_GAMMA_CONTROL 0xF2
#define ILI9341_CMD_INTERFACE_CONTROL 0xF6
#define ILI9341_CMD_PUMP_RATIO_CONTROL 0xF7

#define MAX_X   239
#define MAX_Y   319

#define FONT_SPACE 6
#define FONT_X 8
#define FONT_Y 8

#define PORTRAIT 0
#define LANDSCAPE 1

unsigned int max_x, max_y;
unsigned int bgcolor = black;

void glcd_cs_low() {
    DDRD |= 0b100000; // PD5 is output
    PORTD &=~ 0b100000; // PD5 is 0
}
void glcd_cs_high() {
    DDRD |= 0b100000;
    PORTD |=  0b100000;
}
void glcd_dc_low() {
    DDRD |= 0b1000000; // PD6
    PORTD &=~ 0b1000000;
}
void glcd_dc_high() {
    DDRD |= 0b1000000;
    PORTD |=  0b1000000;
}
void glcd_led_off() {
    DDRD |= 0b10000000; // PD7
    PORTD &=~ 0b10000000;
}
void glcd_led_on() {
    DDRD |= 0b10000000;
    PORTD |=  0b10000000;
}
void glcd_rst_off() {
    DDRD |= 0b10000; // PD4
    PORTD |=  0b10000;
}
void glcd_rst_on() {
    DDRD |= 0b10000;
    PORTD &=~ 0b10000;
}

const unsigned char simpleFont[][8];
unsigned char glcd_orientation;

void glcd_sendCmd(unsigned char data);
void glcd_sendData(unsigned char data);
void glcd_sendData16(unsigned int data);
void glcd_init(void);
void glcd_setX(unsigned int x0,unsigned int x1);
void glcd_setY(unsigned int y0,unsigned int y1);
void glcd_setOrientation(char orientation);
void glcd_setXY(unsigned int x0, unsigned int y0);
void glcd_line(unsigned int x0,unsigned int y0,unsigned int x1, unsigned int y1, unsigned int color);
void glcd_hline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color);
void glcd_vline(unsigned int x0, unsigned int y0, unsigned int length, unsigned int color);
void glcd_rectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color);
void glcd_fillRectangle(unsigned int x0, unsigned int y0, unsigned int length, unsigned int width, unsigned int color);
void glcd_circle(int x0, int y0, int r, unsigned int color);
void glcd_fillCircle(int x0, int y0, int r, unsigned int color);
void glcd_char(unsigned char ascii, unsigned int x0, unsigned int y0,unsigned int size, unsigned int fgcolor);
void glcd_string(char *argstring, unsigned int x0, unsigned int y0, unsigned int size,unsigned int fgcolor);
unsigned char glcd_number(unsigned int long_num,unsigned int x0, unsigned int y0,unsigned int size,unsigned int fgcolor);
unsigned char glcd_float(float floatNumber, unsigned int x0, unsigned int y0, unsigned int size, unsigned int fgcolor);
void glcd_kocka(unsigned int x0, unsigned int y0, unsigned int koliko, unsigned int size, unsigned int fgcolor);
void glcd_clr(unsigned int x0, unsigned int y0, unsigned int size);
void glcd_clrLine(unsigned int y0, unsigned int size);
void glcd_pixel(unsigned int x0, unsigned int y0, unsigned int color);
void glcd_bar(unsigned int x0, unsigned int y0, unsigned int koliko, unsigned int bar_max, unsigned int size, unsigned int fgcolor, unsigned int rectangle_color);
void glcd_bg(unsigned int color);
void glcd_arc(int x, int y, int r, int startAngle, int endAngle, int thickness, unsigned int color);
void glcd_title(char *string, unsigned int size, unsigned int fgcolor, unsigned int bgcolor);
