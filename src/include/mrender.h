#pragma once

#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "html.h"

#define NOPENFD 100

/* TokenFlag documentation
 * A noteworthy specific of operation which is not immediately apparent is 
 * that TERM_ is used to delineate the position in the enum of tagged 
 * variants. Being that the overal enum is subject to change, an abstract
 * base variant being used to "bookmark" locations in the sequence seems
 * the best way to go about using said enum, as otherwise certain tokens 
 * would be subject to carrying around a extra piece of information, which
 * would be very bad. Notice that the above preprocessor definitions lack 
 * analogues the abstract untagged variants; this is because said definitions
 * function as implementations of the ensuing enumerations.
*/
enum TokenFlag {
    _UNTYPED,
	BOLD,
	BREAK,
	CODE_BLOCK,
	CONTENT_EMBED,
	HEADER_,
    HEADER_1,
	HEADER_2,
	HEADER_3,
	HEADER_4,
	HEADER_5,
	HEADER_6,
	HIGHLIGHT,
	HORIZONTAL_LINE,
	FOOTER,
	HYPERLINK,
	INLINE_CODE,
	ITALIC,
	LIST_ELEMENT,
	ORDERED_LIST,
	PLAIN_TEXT,
	QUOTATION,
	SPOILER,
	STRIKETHROUGH,
	TABLE,
	TABLE_DATA,
	TABLE_ROW,
	TASK_,
	TASK_FINISHED,
	TASK_UNFINSHED,
	UNDERLINE,
	UNORDERED_LIST,

	END_BOLD,
	END_HIGHLIGHT,
	END_ITALIC,
	END_SPOILER,
	END_STRIKETHROUGH,
	END_UNDERLINE,

};

typedef struct token {
	enum TokenFlag type;
	size_t length;
	char* body;
} token;

token* token_create() {
    return &(token) { .type = _UNTYPED, .length = 0, .body = NULL };
}

int tokenize(char* text, size_t text_length, vector* tokens) {

	printf("%ld\n", tokens->size);
    
    if (text_length == 0) return 0; // Skip empty file

    token* cur_token    = NULL;
    size_t token_length = 0;
    size_t cursor       = 0;

    #define CREATE  cur_token = vector_add(tokens, token_create());
    #define TYPE    cur_token->type;
    #define BODY    cur_token->body;
    #define LENGTH  cur_token->length;
    #define END     BODY = &text[cursor]; LENGTH = token_length; CREATE;
    
    CREATE;
    //goto start;
    while (cursor < text_length) {
		switch (text[cursor]) {
			/* Block Token Processing
			 * 
			*/
			case '\n': {
				switch (++cursor) {
					case '': {

					} break;
					default: {
						// check numbers
					} break;
			}} break;

			/* Escaped Character Processing: Skip */
			case '\\': {} break;


			case '|': {} break;
			case '`': {} break;
			case 'h': {
				/* Link processing
				 *
				*/
				
			} break;
			case '[': {} break;
			case '*': {} break;
			case '_': {} break;
			case '~': {} break;
			case '=': {} break;
		}
		cursor++;
	}
}