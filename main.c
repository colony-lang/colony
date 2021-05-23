#include <stdio.h>
#include "ctx.h"

int main(int argc, char **argv) {
    co_ctx_t *ctx = co_ctx_new();
    co_ctx_free(ctx);
    return 0;
}
