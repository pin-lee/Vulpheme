#define _XOPEN_SOURCE 500 // Feature Test Macro Requirements for glibc `man nftw`

#include <stdio.h>
#include <ftw.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "include/vector.h"
#include "include/mrender.h"
#include <sqlite3.h>

#define BUFF_S 1000

char* buffer_arena = NULL;
size_t buffer_size = BUFF_S;
vector tokens;

int get_str_len(const char* body) {
    int length = 0;
    while (body[length] != '\0') { length++; }
    return length;
}

int load_file(FILE* file, const struct stat* sb) {
    size_t text_length = sb->st_size;
    if (text_length > buffer_size) {
        buffer_arena = realloc(buffer_arena, text_length);
        if (buffer_arena) {
            printf("Reallocated buffer to %ld bytes.\n", text_length);
            buffer_size = text_length;
        } else {
            puts("Failed to reallocate buffer.");
            return 1;
        }
    }
    fread(buffer_arena, sizeof (char), text_length, file);
    return 0;
}

int handle_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    switch (typeflag) {
        case FTW_F: {
            FILE* file = fopen(fpath, "r");
            if (load_file(file, sb) == 1) {
                printf("Failed to load file %s.", fpath);
                return 1;
            }
            tokenize(buffer_arena, sb->st_size, &tokens);
        } break;
        case FTW_D: return 0;
        default: {
            return 1;
        }
        // todo check if markdown
        // todo check if symlink and check if it's an uplink to parent
        // todo register file in database
        // todo copy over non-md files to dest
    }

    
    return 0;
}

int main(int argc, char* argv[]) {
    
    buffer_arena = malloc(BUFF_S);
    tokens = vector_create(token);

    if (!argv[1] || !argv[2]) {
        printf("USAGE: %s <src> <dest>\n", argv[0]);
        return 0;
    }
    int ret = nftw(argv[1], handle_file, NOPENFD, 0);
    vector_free(&tokens);
    return ret;
}
