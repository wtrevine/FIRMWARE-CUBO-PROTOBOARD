#include "SSD1306.h"

uint8_t buffer_display[1024];

static void CS_active(uint8_t display)
{
  switch(display)
  {
  case 1:
    HAL_GPIO_WritePin(GPIOB, CS2_Pin, SET);
    HAL_GPIO_WritePin(GPIOB, CS1_Pin, RESET);
    break;
    
  case 2:
    HAL_GPIO_WritePin(GPIOB, CS1_Pin, SET);
    HAL_GPIO_WritePin(GPIOB, CS2_Pin, RESET);
    break;
  }
}
void ssd1306_send_command(uint8_t command, uint8_t data)
{
  uint8_t data_send [3] = {OLED_CONTROL_BYTE_CMD_STREAM, command, data};
  HAL_I2C_Master_Transmit(&hi2c1, ADDRESS, data_send, 3, 1);
  
  HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, RESET);
  CS_active(1);
  HAL_SPI_Transmit(&hspi2, data_send, 3, 10);
  CS_active(2);
  HAL_SPI_Transmit(&hspi2, data_send, 3, 10);
}

void ssd1306_WriteCommand(uint8_t command)
{
 HAL_I2C_Mem_Write(&hi2c1, ADDRESS, 0x00, 1, &command, 1, 1);
}

void ssd1306_clear_display()
{
  memset(&buffer_display[0], 0, 1024); 
}
void ssd1306_init()
{  
 ssd1306_send_command(OLED_CMD_DISPLAY_OFF, 0);
 ssd1306_send_command(OLED_CMD_SET_MEMORY_ADDR_MODE,0x10);
 ssd1306_send_command(0xB0,0x00);
 ssd1306_send_command(OLED_CMD_SET_COM_SCAN_MODE,0x00);
 ssd1306_send_command(0x00,0x00);
 ssd1306_send_command(0x10,0x00);
 ssd1306_send_command(0x40,0x00);
 ssd1306_send_command(OLED_CMD_SET_CONTRAST, 0xFF);
 ssd1306_send_command(OLED_CMD_SET_SEGMENT_REMAP,0x00);
 ssd1306_send_command(OLED_CMD_DISPLAY_NORMAL,0x00);
 ssd1306_send_command(OLED_CMD_SET_MUX_RATIO,0x3F);
 ssd1306_send_command(OLED_CMD_DISPLAY_RAM, 0);
 ssd1306_send_command(OLED_CMD_SET_DISPLAY_OFFSET,0x00);
 ssd1306_send_command(OLED_CMD_SET_DISPLAY_CLK_DIV,0xF0);
 ssd1306_send_command(OLED_CMD_SET_PRECHARGE,0x22);
 ssd1306_send_command(OLED_CMD_SET_COM_PIN_MAP,0x12);
 ssd1306_send_command(OLED_CMD_SET_VCOMH_DESELCT,0x20);
 ssd1306_send_command(OLED_CMD_SET_CHARGE_PUMP,0x14);
 ssd1306_send_command(OLED_CMD_DISPLAY_ON, 0);
 

  
//  ssd1306_WriteCommand(0xAE); //display off
//  ssd1306_WriteCommand(0x20); //Set Memory Addressing Mode   
//  ssd1306_WriteCommand(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
//  ssd1306_WriteCommand(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
//  ssd1306_WriteCommand(0xC8); //Set COM Output Scan Direction
//  ssd1306_WriteCommand(0x00); //---set low column address
//  ssd1306_WriteCommand(0x10); //---set high column address
//  ssd1306_WriteCommand(0x40); //--set start line address
//  ssd1306_WriteCommand(0x81); //--set contrast control register
//  ssd1306_WriteCommand(0xFF);
//  ssd1306_WriteCommand(0xA1); //--set segment re-map 0 to 127
//  ssd1306_WriteCommand(0xA6); //--set normal display
//  ssd1306_WriteCommand(0xA8); //--set multiplex ratio(1 to 64)
//  ssd1306_WriteCommand(0x3F); //
//  ssd1306_WriteCommand(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
//  ssd1306_WriteCommand(0xD3); //-set display offset
//  ssd1306_WriteCommand(0x00); //-not offset
//  ssd1306_WriteCommand(0xD5); //--set display clock divide ratio/oscillator frequency
//  ssd1306_WriteCommand(0xF0); //--set divide ratio
//  ssd1306_WriteCommand(0xD9); //--set pre-charge period
//  ssd1306_WriteCommand(0x22); //
//  ssd1306_WriteCommand(0xDA); //--set com pins hardware configuration
//  ssd1306_WriteCommand(0x12);
//  ssd1306_WriteCommand(0xDB); //--set vcomh
//  ssd1306_WriteCommand(0x20); //0x20,0.77xVcc
//  ssd1306_WriteCommand(0x8D); //--set DC-DC enable
//  ssd1306_WriteCommand(0x14); //
//  ssd1306_WriteCommand(0xAF); //--turn on SSD1306 panel
}

void ssd1306_write_display(uint8_t display)
{
  uint8_t column_ [4] = {OLED_CONTROL_BYTE_CMD_STREAM, OLED_CMD_SET_COLUMN_RANGE, 0, 127};
  uint8_t page_ [4] = {OLED_CONTROL_BYTE_CMD_STREAM, OLED_CMD_SET_PAGE_RANGE, 0, 7};
  
  switch(display)
  {
  case 1:
    CS_active(1);
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, RESET);
    HAL_SPI_Transmit(&hspi2, column_, 4, 1);
    HAL_SPI_Transmit(&hspi2, page_, 4, 1);
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, SET);
    HAL_SPI_Transmit(&hspi2, buffer_display, 1024, 150);
    break;
  case 2:
    CS_active(2);
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, RESET);
    HAL_SPI_Transmit(&hspi2, column_, 4, 1);
    HAL_SPI_Transmit(&hspi2, page_, 4, 1);
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, SET);
    HAL_SPI_Transmit(&hspi2, buffer_display, 1024, 150);
    break;
  case 3:
    HAL_I2C_Master_Transmit(&hi2c1, ADDRESS, column_, 4, 1);
    HAL_I2C_Master_Transmit(&hi2c1, ADDRESS, page_, 4, 1);
    HAL_I2C_Mem_Write(&hi2c1, ADDRESS, 0x40, 1, buffer_display, 1024, 150);
    break;
  }
}

//void ssd1306_write_text(uint8_t font, uint8_t column_start, uint8_t page_start, uint8_t *string)
//{
//  uint8_t column_end;
//  uint8_t page_end;
//  uint8_t text;
//  uint8_t p;
//  
//  uint8_t *bitmap;
//  font_char_info *descriptors;
//  font_info *info;
//  
//  switch(font)
//  {
//  case 1:
//    bitmap = font_1_bitmap;
//    descriptors = font_1_descriptors;
//    info = font_1_info;
//    break;
//  case 2:
//    bitmap = font_2_bitmap;
//    descriptors = font_2_descriptors;
//    info = font_2_info;
//    break;
//  case 3:
//    bitmap = font_3_bitmap;
//    descriptors = font_3_descriptors;
//    info = font_3_info;            
//    break;
//  }
//  
//  for(p = 0; string[p] != 0; p++)
//  {  
//  text = string[p] - info->start_character;
//  column_end = column_start + descriptors[text].width - 1;
//  page_end = page_start + info->height - 1;
//
//  uint16_t s_data, n_data, n_page;
//  for(n_page = 0; n_page < page_end - page_start + 1; n_page++)
//  {
//    s_data = column_start + ((page_start + n_page) * 128); // Calcula posição da RAM referente a coluna * pagina
//    n_data = column_end - column_start + 1; // Calcula a quantidade de colunas atualizado na pagina da RAM
//    memcpy(&buffer_display[s_data], (uint8_t*)&bitmap[descriptors[text].offset + (n_data * n_page)], n_data); //Atualiza pagina da RAM hardfalt
//  }
// 
//  column_start = column_end + info->space; //Prepara para proximo caracter
//  }
//}

void ssd1306_write_text(uint8_t font, uint8_t column_start, uint8_t line_start, uint8_t *string)
{
  uint8_t column_end;
  uint8_t line_end;
  uint8_t page_start, page_end;
  uint8_t rigth_column, left_column;
  uint8_t text;
  uint8_t p;
  
  uint8_t *bitmap;
  font_char_info *descriptors;
  font_info *info;
  
  switch(font)
  {
  case 1:
    bitmap = font_1_bitmap;
    descriptors = font_1_descriptors;
    info = font_1_info;
    break;
  case 2:
    bitmap = font_2_bitmap;
    descriptors = font_2_descriptors;
    info = font_2_info;
    break;
  case 3:
    bitmap = font_3_bitmap;
    descriptors = font_3_descriptors;
    info = font_3_info;            
    break;
  }
  
  for(p = 0; string[p] != 0; p++)
  {  
  text = string[p] - info->start_character;
  column_end = column_start + descriptors[text].width - 1;
  line_end = line_start + (info->height * 8) - 1;
  page_start = line_start / 8;
  page_end = page_start + info->height - 1;
  
  rigth_column = line_start - ((page_start) * 8);
  left_column = 8 - (line_start - ((page_start) * 8));

  uint16_t pos_ram, n_data, n_page;
  for(n_page = 0; n_page < page_end - page_start + 1; n_page++)
  {
    pos_ram = column_start + ((page_start + n_page) * 128); // Calcula posição da RAM referente a coluna * pagina
    n_data = column_end - column_start + 1; // Calcula a quantidade de colunas atualizado na pagina da RAM
    //memcpy(&buffer_display[pos_ram], (uint8_t*)&bitmap[descriptors[text].offset + (n_data * n_page)], n_data); //Atualiza pagina da RAM hardfalt
    
    for(uint8_t i = 0; i < n_data; i++)
    {
      buffer_display[pos_ram + i]       |= bitmap[descriptors[text].offset + (n_data * n_page) + i] << rigth_column;
      buffer_display[pos_ram + i + 128] |= bitmap[descriptors[text].offset + (n_data * n_page) + i] >> left_column;
    }
  }
 
  column_start = column_end + info->space; //Prepara para proximo caracter
  }
}

void ssd1306_write_string(uint8_t font, uint8_t column_start, uint8_t page_start, uint8_t string)
{
  uint8_t column_end;
  uint8_t page_end;
  uint8_t text;
  
    uint8_t *bitmap;
  font_char_info *descriptors;
  font_info *info;
  
  switch(font)
  {
  case 1:
    bitmap = font_1_bitmap;
    descriptors = font_1_descriptors;
    info = font_1_info;
    break;
  case 2:
    bitmap = font_2_bitmap;
    descriptors = font_2_descriptors;
    info = font_2_info;
    break;
  case 3:
    bitmap = font_3_bitmap;
    descriptors = font_3_descriptors;
    info = font_3_info;            
    break;
  }
  
  text = string - info->start_character;
  column_end = column_start + descriptors[text].width - 1;
  page_end = page_start + info->height - 1;
  
  uint16_t s_data, n_data, n_page;
  for(n_page = 0; n_page < page_end - page_start + 1; n_page++)
  {
    s_data = column_start + ((page_start + n_page) * 128); // Calcula posição da RAM referente a coluna * pagina
    n_data = column_end - column_start + 1; // Calcula a quantidade de colunas atualizado na pagina da RAM
    memcpy(&buffer_display[s_data], (uint8_t*)&bitmap[descriptors[text].offset + (n_data * n_page)], n_data); //Atualiza pagina da RAM
  }
}

void ssd1306_write_image(uint8_t column_start, uint8_t page_start, uint8_t *image)
{
  uint8_t column_end;
  uint8_t page_end;
  uint16_t size = (image[0] * image[1]) / 8;
  
  column_end = column_start + image[0] - 1;
  page_end = (page_start + (image[1] / 8) - 1);
  
  uint16_t s_data, n_data, n_page;
  for(n_page = 0; n_page < page_end - page_start + 1; n_page++)
  {
    s_data = column_start + ((page_start + n_page) * 128); // Calcula posição da RAM referente a coluna * pagina
    n_data = column_end - column_start + 1; // Calcula a quantidade de colunas atualizado na pagina da RAM
    memcpy(&buffer_display[s_data], &image[2 + (n_data * n_page)], n_data); //Atualiza pagina da RAM
  }
}










