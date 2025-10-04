#include <stdio.h>
#include <string.h>

union Data {
    int i;
    float f;
    unsigned char bytes[4];
};

int main() {
    union Data d;

    // Simulating: we receive the bytes from the hardware {0x00, 0x00, 0x20, 0x41}
    unsigned char rawData[4] = {0x00, 0x00, 0x20, 0x41};
    memcpy(d.bytes, rawData, 4);

    printf("Interpreting the same 4 bytes:\n");
    printf("Integer: %d\n", d.i);
    printf("Floating: %.2f\n", d.f);
    printf("Individual bytes: %02X %02X %02X %02X\n", d.bytes[0], d.bytes[1], d.bytes[2], d.bytes[3]);

    return 0;
}
