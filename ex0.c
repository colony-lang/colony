#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

int main(int argc, char **argv) {
    ssize_t index = -3;
    size_t len = 8;
    size_t u_index = index % len;
    printf("u_index: %u\n", u_index);
    return 0;
}