#pragma once

#include <stdio.h>
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
	LINK_TARGET,
	LINK_TEXT,
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
	token* modifier_stack[INLINE_ENDABLE_AMOUNT] = { NULL };
    size_t cursor       = 0;

	/* CREATE Macro Explanation
	 * Limiting the scope of _cur_token_buff prevents it from being accessed
	 * in other areas of the routine. It exists purely as a transient location
	 * for the token to live as it is moving through the initialization stage
	 * of the token lifecycle.
	 */
    #define CREATE	{ token _cur_token_buff = token_create();\
	cur_token_ptr = vector_add(tokens, &_cur_token_buff); }

    #define TYPE    cur_token_ptr->type
    #define BODY    cur_token_ptr->body
    #define LENGTH  cur_token_ptr->length
	#define NEXT	text[++cursor]
	#define KILL(i)	text[i] = 27;

	#define EFFECT_WRAP(character, IT, Flag, EndFlag) if (NEXT == character) {\
					if (modifier_stack[IT]) {\
						CREATE; TYPE = EndFlag;\
						modifier_stack[IT] = NULL;\
						KILL(cursor); KILL(cursor - 1);\
					} else if (NEXT != ' ') {\
						CREATE; modifier_stack[IT] = cur_token_ptr;\
						TYPE = Flag;\
						BODY = &text[cursor];\
						KILL(cursor - 1); KILL(cursor - 2);\
					}\
				}

    CREATE;
	size_t line_start = 0;
    goto start;
    while (cursor < text_length) {
		switch (text[cursor]) {
			// todo, do lookaheads at the top of each case
			/* Block Token Processing
			 * 
			*/
			case '\n': {
				CREATE; TYPE = BREAK; CREATE;
				*modifier_stack = NULL;
				line_start = cursor;
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
								BODY = &text[cursor + 3]; cursor += 3;
								break;
							}
							// normal list
							TYPE = LIST_ELEMENT;
							BODY = &text[cursor];
							break;
						}
					} break;
					case '#': {
						unsigned int level = 1;
						while (NEXT == '#') { level++; };
						if (text[cursor] == ' ') {
							BODY = &NEXT;
							if (level > 6) { level = 6; };
							printf("Creating level %d header.\n", level);
							TYPE = HEADER_ + level;
							break;
						} else {
							TYPE = PLAIN_TEXT;;
							BODY = &text[cursor - level];
						}
					} break;
					case '>': {
						if (NEXT == ' ') {
							TYPE = QUOTATION;
							BODY = &NEXT;
							break;
						} else { TYPE = PLAIN_TEXT; BODY = &text[cursor - 2]; }
					} break;
					case ':': {
						if (NEXT == ' ') {
							TYPE = DEFINITION_DATA;
							BODY = &NEXT;
						} else { TYPE = PLAIN_TEXT; BODY = &text[cursor - 2]; }
					} break;
					default: {
						// check numbers
						if (NEXT >= '1' && text[cursor] <= '9') {
							size_t start = cursor;
							while (NEXT >= '0' && text[cursor] <= '9');
							if (text[cursor] == '.' && NEXT == ' ') {
								TYPE = ORDERED_LIST;
								BODY = &NEXT;
								break;
							} else {
								TYPE = PLAIN_TEXT;
								BODY = &text[start];
							}
						} else {
							TYPE = PLAIN_TEXT;
							BODY = &text[line_start];
							cursor = line_start + 1;
						}
					} break;
			}} break;

			/* Escaped Character Processing: Skip */
			case '\\': {
				KILL(cursor);
				cursor++;
			} break;

			case '`': { // code blocks can happen at end of line. inline can happen anywhere
			
			} break;

			/* (Hyper)Links and Embeds
			 *
			*/
			case '!': {
				/*
				if (NEXT == '[') {
					int i = 0;
					NEXT;
					while (text[cursor + i] != ']' && i < 2048) { i++; }
					CREATE;
					if (text[cursor + i] == ']') {
						TYPE = CONTENT_EMBED;
						BODY = &text[cursor];
						LENGTH = i;
					} else {
						TYPE = PLAIN_TEXT;
						BODY = &text[cursor - 1];
					}
				} */
			} break;
			case '[': {
				switch (NEXT) {
					// ]
					// words
				}
			} break;
			case '*': {

			} break;
			case '|': { EFFECT_WRAP('|', IT_SPOILER, SPOILER, END_SPOILER); } break;
			case '_': { EFFECT_WRAP('_', IT_UNDERLINE, UNDERLINE, END_UNDERLINE); } break;
			case '~': { EFFECT_WRAP('~', IT_STRIKETHROUGH, STRIKETHROUGH, END_STRIKETHROUGH); } break;
			case '=': { EFFECT_WRAP('=', IT_HIGHLIGHT, HIGHLIGHT, END_HIGHLIGHT); } break;
			default: {
				
			}
		}
		for (int i = 0; i < 6; i++) {
			if (modifier_stack[i] && modifier_stack[i] != cur_token_ptr) {
				modifier_stack[i]->length++;
			}
		}
		LENGTH++;
		cursor++;
	}

	for (size_t i = 0; i < tokens->length; i++) {
		token* t = (token*)vector_get(tokens, i);
		if (t->body == NULL) continue;
		for (size_t j = 0; j < t->length; j++) {
			printf("%c", t->body[j]);
		}
		printf("\n");
	}

	return 0;
}
