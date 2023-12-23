#include <stdio.h>
#include <ftw.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "include/mrender.h"
#include <sqlite3.h>

#define NOPENFD 100
#define BUFF_S 1000
#define SCALE_F 1.5

char* buffer_arena = NULL;
size_t buffer_size = BUFF_S;

size_t load_file(FILE* file) {
    size_t text_length = 0;
    size_t cursor = 0;
    size_t bytes_written = 0;
    do {
        bytes_written = fread(&buffer_arena[cursor], sizeof (char), BUFF_S, file);
        cursor += bytes_written;
        text_length += bytes_written;
        if (text_length == buffer_size) {
            size_t new_size = (size_t)((float)buffer_size * SCALE_F);
            printf("Realocating from %ld bytes to %ld bytes. ", buffer_size, new_size);
            buffer_arena = realloc(buffer_arena, new_size);
            if (buffer_arena) {
                printf("Reallocated, growing by %fx.", SCALE_F);
                buffer_size *= SCALE_F;
            } else {
                puts("Failed to reallocate. Exiting.");
                return 1;
            }
        }
    } while (bytes_written == BUFF_S);
    buffer_arena[text_length] = '\0';
    return text_length;
}

int tokenize(size_t text_length) { // lex the file
    
    printf("%s\n", buffer_arena);
    return 0;
}

int handle_file(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
    switch (typeflag) {
        case FTW_F: {
            int len = get_str_len(fpath);
            printf("%s has %d characters.\n", fpath, len);
            
        } break;
        case FTW_D: return 0;
        default: {
            puts("You broke something.");
            return 1;
        }
        // todo check if markdown
        // todo check if symlink and check if it's an uplink to parent
        // todo register file in database
        // todo copy over non-md files to dest
    }

    FILE* file = fopen(fpath, "r");
    tokenize(load_file(file));
    
}

inline int get_str_len(const char* body) {
    int length = 0;
    while (body[length] != '\0') { length++; }
    return length;
}

inline bool is_parent_path_of(string* a, string* b) {
	if (a->length <= b->length) { return false; }
	for (unsigned int i = 0; i < a->length; i++) {
		if (a->body[i] != b->body[i]) { return false; }
	}
	return true;
}


int main(int argc, char* argv[]) {

    buffer_arena = malloc(BUFF_S);

    if (!argv[1] || !argv[2]) {
        printf("USAGE: %s <src> <dest>\n", argv[0]);
        return 1;
    }
    nftw(argv[1], handle_file, NOPENFD, 0);
    
    return 0;
}
