#include <assert.h>
#include <iostream>

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

int main(int argc, char *argv[]) {

  std::cout << "template makefile project \r\n";
  return 0;
}


