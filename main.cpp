#include <cstdio>
#include <cstdlib>
#include "anna.h"

const char* USAGE = "USAGE: anna filename [encoding]\nEncoding can be utf-8 (default) or utf-16.";

int main(int argc, char* argv[]) {

    if (!argv[1]) {
        puts(USAGE);
        return 0;
    }

    auto source = fopen(argv[1], "r");
    if (!source) {
        printf("Failed to open file %s.\n", argv[1]);
        return -1;
    }

    switch (*argv[2]) {
        case *"utf-16": {
            anna<wchar_t> system;
        } break;
        default: {
            anna<char> system;
        }
    }

    return 0;
}

