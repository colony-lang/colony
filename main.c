#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utf8.h"
#include "colony.h"

int main(int argc, char **argv) {
    co_obj_t s0 = {.k = CO_KIND_STR };
    size_t l0 = sizeof(s0);
    printf("l0 = %lu\n", l0);
    
    co_obj_t s1 = {.k = CO_KIND_STR };
    
    co_small_str_obj_t s1s;
    memmove(&s1s, &s1, sizeof(s1));

    printf("s1.k = %d\n", s1.k);
    printf("s1s.k = %d\n", s1s.k);
    printf("s1s.v = '%s'\n", s1s.v);
    
    char8_t t1[15] = u8"getattr";
    utf8ncpy((void*)&s1s.v, (void*)&t1, utf8size((void*)&t1));
    
    printf("s1.k = %d\n", s1.k);
    printf("s1s.k = %d\n", s1s.k);
    printf("s1s.v = '%s'\n", s1s.v);

    size_t l1 = sizeof(s1);
    printf("l1 = %lu\n", l1);
    
    // size_t s2 = sizeof(co_packed_obj_t);
    // printf("s2 = %lu\n", s2);

    return 0; 
}

