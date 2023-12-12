#include <stdio.h>
#include <malloc.h>

int main() {
    unsigned char name1[]  = {'I', 'H', 'D', 'R'};
    unsigned char name2[] = "IHDR";
    if (name1 == name2) {
        printf("true");
    } else {
        printf("false");
    }
}