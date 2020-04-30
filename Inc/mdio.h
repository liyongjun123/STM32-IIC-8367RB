#ifndef __MDIO_H_
#define __MDIO_H_

#include <stdint.h>

uint16_t read_data(uint8_t phyad, uint8_t regad);
void write_data(uint8_t phyad, uint8_t regad, uint16_t out_data);

uint16_t read_data_8367(uint8_t phyad, uint16_t regad);
void write_data_8367(uint8_t phyad, uint16_t regad, uint16_t out_data);

void help(void);

#endif
