//
// Created by goose on 11/25/23.
//

#ifndef ANNA_ANNA_H
#define ANNA_ANNA_H

#include <vector>
#include <ftw.h>
#include <sys/stat.h>

enum class flag {
    header,
    horizontal_line,
    ordered_list,
    unordered_list,
    task_list,
    table,
    code_block,
    inline_code,
    quotation,
    content_embed,
    hyperlink,
    plain_text,
    bold,
    italic,
    underline,
    strikethrough,
    spoiler
};

template<typename T>
struct anna {

    explicit anna(char* source) {
        if (ftw(source, load_file, 1024)) {

        }
    }

    static int load_file(const char *fpath, const struct stat *sb, int typeflag) {

    }

    int lex_file(unsigned int length, T* body) {
        unsigned int cursor = 0;

        return 0;
    };


    void combinator(T* input, void (*parser)(T*)...) {
        parser(input);
    }

    struct string {
        unsigned int length;
        T* body;
    };

    struct token {
        flag type;
        string content;
    };

    string content;
    std::vector<token> tokens;

};


#endif //ANNA_ANNA_H
