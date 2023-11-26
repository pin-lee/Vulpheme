//
// Created by goose on 11/25/23.
//

#ifndef ANNA_ANNA_H
#define ANNA_ANNA_H

#include <vector>

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

    anna() {}

    struct string {
        unsigned int length;
        T* body;
    };

    struct token {
        flag type;
        string content;
    };

    struct lexer {
        lexer(unsigned int length, T* body) : length{length}, input{body} {}
        unsigned int length;
        T* input;
        unsigned int cursor;
    };

    void combinator(T* input, void (*parser)(T*)...) {
        parser(input);
    }

    string content;
    std::vector<token> tokens;

};


#endif //ANNA_ANNA_H
