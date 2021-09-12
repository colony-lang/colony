#include <stdio.h>
#include "core/ctx.h"
#include "object/object.h"

int main(int argc, char **argv) {
    co_ctx_t *ctx = co_ctx_new(NULL);
    co_ctx_rel(ctx);
    return 0;
}
