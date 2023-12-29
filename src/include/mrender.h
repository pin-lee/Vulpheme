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
	DEFINITION_DATA,// Note, the lexer cannot distinguish between text and 
	HEADER_,		// <dt>, so it is the job of the parser to do that part.	
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

enum InlineToken {
	IT_BOLD,
	IT_HIGHLIGHT,
	IT_ITALIC,
	IT_SPOILER,
	IT_STRIKETHROUGH,
	IT_UNDERLINE,
	_IT_END
};

#define INLINE_ENDABLE_AMOUNT _IT_END

typedef struct token {
	enum TokenFlag type;
	size_t length;
	char* body;
} token;

token token_create() {
    return (token) { .type = _UNTYPED, .length = 0, .body = NULL };
}

int tokenize(char* text, size_t text_length, vector* tokens) {
    
    if (text_length == 0) return 0; // Skip empty file

	token* cur_token_ptr = NULL;
    token cur_token_buff;
	bool modifier_stack[INLINE_ENDABLE_AMOUNT] = { false };
    size_t cursor       = 0;

    #define CREATE  cur_token_buff = token_create(); cur_token_ptr = vector_add(tokens, &cur_token_buff);
    #define TYPE    cur_token_ptr->type
    #define BODY    cur_token_ptr->body
    #define LENGTH  cur_token_ptr->length
	#define NEXT	text[++cursor]
    
    CREATE;
    goto start;
    while (cursor < text_length) {
		switch (text[cursor]) {
			// todo, do lookaheads at the top of each case
			/* Block Token Processing
			 * 
			*/
			case '\n': {
				CREATE;
				switch (NEXT) {
				start:
					case '-': {
						if (NEXT == ' ') {
							if (NEXT == '[' &&
							text[cursor + 2] == ']' &&
							text[cursor + 3] == ' ') {
								switch (NEXT) {
									default:
									case (' '): TYPE = TASK_UNFINSHED; break;
									case ('x'):
									case ('X'): TYPE = TASK_FINISHED; break;
								} 
								BODY = &text[cursor + 3]; cursor += 2;
								goto lex_end;
							}
							// normal list
							TYPE = LIST_ELEMENT;
						}
					} break;
					case '#': {} break;
					case '>': {} break;
					case '`': {} break;
					case ':': {} break;
					default: {
						// check numbers
					} break;
			}} break;

			/* Escaped Character Processing: Skip */
			case '\\': {
				cursor++;
			} break;

			case '|': {} break;
			case '`': {
				// Note: Code blocks are handled above. This path is strictly for inline code.
			} break;

			/* (Hyper)Links and Embeds
			 *
			*/
			case '[': {
				switch (NEXT) {
					case 'h': {
						/* Link processing
						* Do a lookahead for the `p` in http(s)
						* Do a lookahead for the `:`
						* Check for the remaining `t`s and `/`s.
						* If all checks, succeed, create URL token.
						*/
						
					} break;
				}
			} break;
			case '*': {} break;
			case '_': {} break;
			case '~': {} break;
			case '=': {} break;
			default: {
				LENGTH++;
			}
		}
	lex_end:
		cursor++;
		continue;
	plain_text:
		TYPE = PLAIN_TEXT;
		goto lex_end;
	}

	for (size_t i = 0; i < tokens->length; i++) {
		printf("There are %ld tokens.", tokens->length);
		token t = *(token*)vector_get(tokens, i);
		printf("The current token is %ld characters long.", t.length);
		for (size_t j = 0; j < t.length; j++) {
			printf("%c", t.body[j]);
		}
		printf("\n");
	}

}