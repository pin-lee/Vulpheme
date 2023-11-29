#include <cstdio>
#include <ftw.h>
#include <cstdlib>
#include "anna.h"

const char* USAGE = "USAGE: anna <source> <dest> [encoding]\nEncoding can be utf-8 (default) or utf-16.";

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

    if (*argv[2] == *"utf-16") {
        anna<wchar_t> system{argv[1]};
    } else {
        anna<char> system{argv[1]};
    }


    return 0;

    fail:
        return 0;

}

