#include <assert.h>
#include <iostream>
#include <stdio.h>

uint8_t bin2bcd(uint8_t bin) {
    union {
        uint16_t m_val;
        uint8_t m_buf[2];
    } buf;
    
    buf.m_buf[1] = 0;
    buf.m_buf[0] = bin;
    printf("val: %.4X, 0: %d, 1: %d\n", buf.m_val, buf.m_buf[0], buf.m_buf[1]);
    for (int i = 0; i < 7; i++) {
        
        buf.m_val <<= 1;
        if (((buf.m_buf[1] + 0x03) & 0x08) == 0x08) {
          buf.m_buf[1] += 0x03;
        }
        if (((buf.m_buf[1] + 0x30) & 0x80) == 0x80) {
          buf.m_buf[1] += 0x30;
        }
        printf("val: %.4X, 0: %.2X, 1: %.2X\n", buf.m_val, buf.m_buf[0], buf.m_buf[1]);
        
    }
    buf.m_val <<= 1;
    return buf.m_buf[1];
}

#define DAYS2TICK(day, periodUs) (((day) * 24 * 3600 * 1000000UL) / (periodUs))


int main(int argc, char *argv[]) {

  std::cout << "template makefile project \r\n";

  uint32_t days     = 9;
  uint32_t periodUs = 500;
  uint64_t result = DAYS2TICK(days, periodUs);
  printf("days: %u, periodUs: %u, result: %lu, 0x%.8lX ", days, periodUs, result, result);
  return 0;
}


