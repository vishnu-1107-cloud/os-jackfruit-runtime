
#include <stdio.h>

int main() {
    while (1) {
        for (volatile long i = 0; i < 100000000; i++);
        printf("cpu_hog running\n");
    }
}
