#ifndef __FONT_H
#define __FONT_H

#include "main.h"
#include "stm32f1xx_hal.h"


typedef struct{
  uint8_t width;
  uint16_t offset;
}font_char_info;

typedef struct{
  uint8_t height;
  uint8_t start_character;
  uint8_t end_character;
  uint8_t space;
  //FONT_CHAR_INFO descriptor_array[];
  //uint8_t bitmap_array[];
}font_info;

//Font data for GiantRobotArmy Med 24pt
extern const uint8_t giantRobotArmyMed_8ptBitmaps[];
extern const font_info giantRobotArmyMed_8ptFontInfo;
extern const font_char_info giantRobotArmyMed_8ptDescriptors[];

extern const uint8_t giantRobotArmyMed_16ptBitmaps[];
extern const font_info giantRobotArmyMed_16ptFontInfo;
extern const font_char_info giantRobotArmyMed_16ptDescriptors[];

extern const uint8_t giantRobotArmyMed_24ptBitmaps[];
extern const font_info giantRobotArmyMed_24ptFontInfo;
extern const font_char_info giantRobotArmyMed_24ptDescriptors[];

extern uint8_t *font_1_bitmap;
extern font_char_info *font_1_descriptors;
extern font_info *font_1_info;

extern uint8_t *font_2_bitmap;
extern font_char_info *font_2_descriptors;
extern font_info *font_2_info;

extern uint8_t *font_3_bitmap;
extern font_char_info *font_3_descriptors;
extern font_info *font_3_info;
extern const uint8_t opala[];




#endif
