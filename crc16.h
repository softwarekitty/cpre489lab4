#ifndef CRC16_H
#define CRC16_H

#include <cstdint>
#include <cstddef>

#ifndef CRC16_GENERATOR
#define CRC16_GENERATOR 0x1021
#endif

uint16_t crc16_compute(const uint8_t *data, size_t length);

#endif // CRC16_H
