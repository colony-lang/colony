#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "colony.h"


int main(int argc, char** argv, char** env_var_ptr) {
    int exit_code = EXIT_SUCCESS;

    /*
    // TODO: create `map` object from parsed env vars
    char* env_var;
    
    while (*env_var_ptr != NULL) {
        env_var = *(env_var_ptr++);
        printf("%s\n", env_var);
    }
    */

    /* parse argv */
    int opt;
    bool arg_compile = false;
    char* main_module_path = NULL; 

    while ((opt = getopt(argc, argv, "ch")) != -1) {
        switch (opt) {
            case 'c':
                arg_compile = true;
                break;
            case '?':
                fprintf(stderr, "Unrecognized option: '-%c'\n", optopt);
                exit_code = EXIT_FAILURE;
                goto exit;
            case 'h':
                fprintf(
                    stdout,
                    "Usage: colony [-c] [file]\n"
                    "Available options are:\n"
                    "  -c      compile bytecode only\n"
                    "  file    main module path\n"
                );
                goto exit;
            default:
                exit_code = EXIT_FAILURE;
                goto exit;
        }
    }

    if (optind < argc) {
        main_module_path = argv[optind];
    }

    if (arg_compile && main_module_path == NULL) {
        fprintf(
            stderr,
            "Option '-c' requires path to file\n"
            "Example: colony -c example.co\n"
        );

        exit_code = EXIT_FAILURE;
        goto exit;
    }

    /* create vm */
    co_vm_t* vm = co_vm_new();

    if (arg_compile) {
        fprintf(stderr, "Compile-to-file currently unsupported\n");
        exit_code = EXIT_FAILURE;
        goto cleanup_0;
    }

    if (main_module_path == NULL) {
        fprintf(stderr, "Interactive REPL currently unsupported\n");
        exit_code = EXIT_FAILURE;
        goto cleanup_0;
    }

    /* create compiler */
    co_compiler_t* compiler = co_compiler_new();

    if (compiler == NULL) {
        fprintf(stderr, "Could not create 'compiler' object\n");
        exit_code = EXIT_FAILURE;
        goto cleanup_0;
    }

    /* path to main module */
    co_object_t* path = co_str_new(vm, CO_OWN_NONE, strlen(main_module_path), main_module_path);

    if (path == NULL) {
        fprintf(stderr, "Could not create 'path' object\n");
        exit_code = EXIT_FAILURE;
        goto cleanup_1;
    }

    /* compile */
    co_object_t* code = co_compiler_compile_path(compiler, path);

    if (code == NULL) {
        fprintf(stderr, "Could not compile main module from path\n");
        exit_code = EXIT_FAILURE;
        goto cleanup_2;
    }

cleanup_2:
    co_object_free(vm, path);
cleanup_1:
    co_compiler_free(compiler);
cleanup_0:
    co_vm_free(vm);
exit:
    return exit_code;
}
