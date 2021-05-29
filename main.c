#include <stdio.h>
#include "ctx.h"

int main(int argc, char **argv) {
    co_ctx_t *root = co_ctx_new(NULL);
    co_ctx_t *ctx = co_ctx_new(root);
    co_ctx_free(ctx);
    return 0;
}
