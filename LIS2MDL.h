#ifndef LIS2MDL_H
#define LIS2MDL_H

#include <stdint.h>

// º¯ÊýÉùÃ÷
void LIS2MDL_WriteReg(uint8_t RegAddress, uint8_t Data);
uint8_t LIS2MDL_ReadReg(uint8_t RegAddress);
void LIS2MDL_Init(void);
void LIS2MDL_GetData(int16_t *ANGLE_X, int16_t *ANGLE_Y, int16_t *ANGLE_Z);

#endif // LIS2MDL_H
