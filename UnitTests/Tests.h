#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define CheckSame(a, b, c) _Generic((a), \
    uint8_t:  CheckSame8, \
    uint16_t: CheckSame16 \
)(a, b, c)

bool CheckSame8(uint8_t a, uint8_t b, const char *str);
bool CheckSame16(uint16_t a, uint16_t b, const char *str);

void PASS();
void FAIL();

