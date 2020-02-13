#include <stdio.h>
//Arthur Chu
int prefix(unsigned int x, unsigned int n) {
    int nRightShifted = x >> (32 - n);
    printf("The number in decimal form is %d\n", nRightShifted);
    int temp;
    for (int i = 32; i > 0; i--) {
        temp = x >> i;

        if (temp & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    return nRightShifted;
}

int suffix(unsigned int x, unsigned int n) {
    int nLeftShifted = x << (32 - n);
    printf("The number in decimal form is %d\n", nLeftShifted);
    int temp;
    for (int i = 32; i > 0; i--) {
        temp = x << i;

        if (temp & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    return nLeftShifted;
}

int toggle(unsigned int x, unsigned int n) {
    return (x | (1 << (n -1));
}

void main() {

return;
}
