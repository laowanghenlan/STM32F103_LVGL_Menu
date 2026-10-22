/**
 * ST7789 240x240 SPI 驱动 (SPI1, 8位模式, 36MHz)
 * SCL=PA5  SDA=PA7  CS=PA4  DC=PA3  RES=PA2  BLK=PB9
 */
#include "bsp_lcd.h"
#include "bsp_sys.h"

#define LCD_CS_H()   GPIO_SetBits(GPIOA, GPIO_Pin_4)
#define LCD_CS_L()   GPIO_ResetBits(GPIOA, GPIO_Pin_4)
#define LCD_DC_H()   GPIO_SetBits(GPIOA, GPIO_Pin_3)
#define LCD_DC_L()   GPIO_ResetBits(GPIOA, GPIO_Pin_3)
#define LCD_RES_H()  GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define LCD_RES_L()  GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define LCD_BLK_H()  GPIO_SetBits(GPIOB, GPIO_Pin_9)

static void LCD_SPI_Send(uint8_t data)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
}

static void LCD_WriteCmd(uint8_t cmd)
{
    LCD_DC_L();
    LCD_CS_L();
    LCD_SPI_Send(cmd);
    LCD_CS_H();
}

static void LCD_WriteData8(uint8_t data)
{
    LCD_DC_H();
    LCD_CS_L();
    LCD_SPI_Send(data);
    LCD_CS_H();
}

static void LCD_WriteData16(uint16_t data)
{
    LCD_DC_H();
    LCD_CS_L();
    LCD_SPI_Send(data >> 8);
    LCD_SPI_Send(data & 0xFF);
    LCD_CS_H();
}

static void LCD_GPIO_SPI_Init(void)
{
    GPIO_InitTypeDef gpio;
    SPI_InitTypeDef  spi;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_SPI1 | RCC_APB2Periph_AFIO, ENABLE);

    /* PA5=SCK, PA7=MOSI 复用推挽 */
    gpio.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_7;
    gpio.GPIO_Mode  = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);

    /* PA2=RES, PA3=DC, PA4=CS 推挽输出 */
    gpio.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    gpio.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &gpio);

    /* PB9=BLK 背光 */
    gpio.GPIO_Pin   = GPIO_Pin_9;
    GPIO_Init(GPIOB, &gpio);

    SPI_Cmd(SPI1, DISABLE);
    spi.SPI_Direction         = SPI_Direction_1Line_Tx;
    spi.SPI_Mode              = SPI_Mode_Master;
    spi.SPI_DataSize          = SPI_DataSize_8b;
    spi.SPI_CPOL              = SPI_CPOL_High;
    spi.SPI_CPHA              = SPI_CPHA_2Edge;
    spi.SPI_NSS               = SPI_NSS_Soft;
    spi.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;   /* 72/2 = 36MHz */
    spi.SPI_FirstBit          = SPI_FirstBit_MSB;
    spi.SPI_CRCPolynomial     = 7;
    SPI_Init(SPI1, &spi);
    SPI_Cmd(SPI1, ENABLE);
}

void LCD_SetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    x0 += LCD_X_OFFSET; x1 += LCD_X_OFFSET;
    y0 += LCD_Y_OFFSET; y1 += LCD_Y_OFFSET;

    LCD_WriteCmd(0x2A);
    LCD_WriteData8(x0 >> 8); LCD_WriteData8(x0 & 0xFF);
    LCD_WriteData8(x1 >> 8); LCD_WriteData8(x1 & 0xFF);

    LCD_WriteCmd(0x2B);
    LCD_WriteData8(y0 >> 8); LCD_WriteData8(y0 & 0xFF);
    LCD_WriteData8(y1 >> 8); LCD_WriteData8(y1 & 0xFF);

    LCD_WriteCmd(0x2C);
}

/* 连续写像素数据(RGB565大端字节流), LVGL flush 调用 */
void LCD_WritePixels(const uint8_t *data, uint32_t len)
{
    uint32_t i;
    LCD_DC_H();
    LCD_CS_L();
    for (i = 0; i < len; i++)
    {
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, data[i]);
    }
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET);
    LCD_CS_H();
}

void LCD_Fill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint32_t i, total = (uint32_t)(x1 - x0 + 1) * (y1 - y0 + 1);
    LCD_SetWindow(x0, y0, x1, y1);
    LCD_DC_H();
    LCD_CS_L();
    for (i = 0; i < total; i++)
    {
        LCD_SPI_Send(color >> 8);
        LCD_SPI_Send(color & 0xFF);
    }
    LCD_CS_H();
}

void LCD_Init(void)
{
    LCD_GPIO_SPI_Init();

    /* 硬复位 */
    LCD_RES_L();
    BSP_DelayMs(50);
    LCD_RES_H();
    BSP_DelayMs(120);

    LCD_WriteCmd(0x11);              /* Sleep out */
    BSP_DelayMs(120);

    LCD_WriteCmd(0x36);              /* MADCTL */
#if LCD_COLOR_BGR
    LCD_WriteData8(0x08);            /* BGR 顺序 */
#else
    LCD_WriteData8(0x00);            /* RGB 顺序 */
#endif

    LCD_WriteCmd(0x3A);              /* 16bit/pixel */
    LCD_WriteData8(0x05);

    LCD_WriteCmd(0xB2);
    LCD_WriteData8(0x0C); LCD_WriteData8(0x0C);
    LCD_WriteData8(0x00); LCD_WriteData8(0x33); LCD_WriteData8(0x33);

    LCD_WriteCmd(0xB7);  LCD_WriteData8(0x35);
    LCD_WriteCmd(0xBB);  LCD_WriteData8(0x19);
    LCD_WriteCmd(0xC0);  LCD_WriteData8(0x2C);
    LCD_WriteCmd(0xC2);  LCD_WriteData8(0x01);
    LCD_WriteCmd(0xC3);  LCD_WriteData8(0x12);
    LCD_WriteCmd(0xC4);  LCD_WriteData8(0x20);
    LCD_WriteCmd(0xC6);  LCD_WriteData8(0x0F);
    LCD_WriteCmd(0xD0);  LCD_WriteData8(0xA4); LCD_WriteData8(0xA1);

    LCD_WriteCmd(0xE0);
    LCD_WriteData8(0xD0); LCD_WriteData8(0x04); LCD_WriteData8(0x0D); LCD_WriteData8(0x11);
    LCD_WriteData8(0x13); LCD_WriteData8(0x2B); LCD_WriteData8(0x3F); LCD_WriteData8(0x54);
    LCD_WriteData8(0x4C); LCD_WriteData8(0x18); LCD_WriteData8(0x0D); LCD_WriteData8(0x0B);
    LCD_WriteData8(0x1F); LCD_WriteData8(0x23);

    LCD_WriteCmd(0xE1);
    LCD_WriteData8(0xD0); LCD_WriteData8(0x04); LCD_WriteData8(0x0C); LCD_WriteData8(0x11);
    LCD_WriteData8(0x13); LCD_WriteData8(0x2C); LCD_WriteData8(0x3F); LCD_WriteData8(0x44);
    LCD_WriteData8(0x51); LCD_WriteData8(0x2F); LCD_WriteData8(0x1F); LCD_WriteData8(0x1F);
    LCD_WriteData8(0x20); LCD_WriteData8(0x23);

    LCD_WriteCmd(0x21);              /* 反显开 */
    LCD_WriteCmd(0x29);              /* 显示开 */

    LCD_BLK_H();                     /* 开背光 */
    LCD_Fill(0, 0, LCD_W - 1, LCD_H - 1, 0x0000);
}
