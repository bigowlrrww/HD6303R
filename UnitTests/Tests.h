#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define CheckSame(a, b, c) _Generic((a), \
    uint8_t:  CheckSame8, \
    uint16_t: CheckSame16 \
)(a, b, c)

void EnVerbose();
bool PASS();
bool WARN();
bool FAIL();

bool CheckSame8(uint8_t a, uint8_t b, const char *str);
bool CheckSame16(uint16_t a, uint16_t b, const char *str);

bool checkPC(uint16_t a, uint16_t b, uint8_t expectedStep);

bool checkImplemented(uint8_t flags);
bool checkVerified(uint8_t flags);
bool verifyUnknownMnemonic(uint16_t ExecResult);
