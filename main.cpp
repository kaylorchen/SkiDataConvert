#include <iostream>
#include "fstream"
#include "stdio.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    if (argc < 2) {
        std::cout << "Pls input: ./convert xxx.sonw" << std::endl;
        return 0;
    }
    printf("Input file: %s\n", argv[1]);
    std::ifstream inFlie(argv[1], std::ios::in | std::ios::binary);
    char offset[8];
    inFlie.read(offset, sizeof(offset));
    for (int i = 0; i < sizeof(offset); ++i) {
        printf("%X ", offset[i]);
    }
    printf("\n");
    unsigned char data[31];
    while (inFlie.read((char *) data, sizeof(data))) {
//        for (int i = 0; i < sizeof(data); ++i) {
//            printf("%02X ", data[i]);
//        }
//        printf("\n");
        uint32_t *pTickCount = (uint32_t *) &data[3];

        uint32_t pressure[4] = {0};
        uint8_t *pPressure = &data[7];
        for (int num = 0; num < 4; ++num) {
            pressure[num]  = ((*pPressure) << 16) | ((*(pPressure + 1)) << 8) | (*(pPressure + 2));
            pPressure = pPressure + 3;
        }
        printf("Tick count = %d, %d %d %d %d\n", *pTickCount, pressure[0], \
        pressure[1], pressure[2], pressure[3]);
        static int32_t count = 0;
        count ++;
        if (count == 1000)
            break;
    }
    inFlie.close();
    return 0;
}
