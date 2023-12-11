#include <cstdio>
#include <ftw.h>
#include <cstdlib>
#include "markdown_renderer.hpp"

const char* USAGE = "USAGE: mrender <source> <dest>";

int main(int argc, char* argv[]) {

    if (!argv[1]) {
        puts(USAGE);
        return 0;
    }

    markdown_renderer system{argv[1]};

    return 0;
}

