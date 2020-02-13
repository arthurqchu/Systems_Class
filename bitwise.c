#include <stdio.h>
//Arthur Chu
int prefix(unsigned int x, unsigned int n) {
    int nRightShifted = x >> (16 - n);
    return nRightShifted;
}

int suffix(unsigned int x, unsigned int n) {
    int nLeftShifted = x << (16 - n);
    return nLeftShifted;
}

int toggle(unsigned int x, unsigned int n) {
    return (x | (1 << (n -1)));
}

void main() {
    unsigned int a = 10000, b = 10;
    printf("a = %d\nb = %d\n", a, b);

    int p = prefix(a, 4);
    int s = suffix(b, 4);
    int temp;
    printf("a (after prefix) = %d. In binary it's ", p);
    for (int i = 16; i > 0; i--) {
        temp = p >> i;

        if (temp & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
    printf("b (after suffix)= %d. In binary it's ", s);
    for (int i = 16; i > 0; i--) {
        temp = s >> i;

        if (temp & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
return;
}
