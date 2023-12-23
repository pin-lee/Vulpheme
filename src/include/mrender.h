#include <stdlib.h>
#include <string.h>

enum TokenFlag {
    HEADER,
	HORIZONTAL_LINE,
	ORDERED_LIST,
	UNORDERED_LIST,
	TASK_LIST,
	TABLE,
	CODE_BLOCK,
	INLINE_CODE,
	QUOTATION,
	CONTENT_EMBED,
	HYPERLINK,
	PLAIN_TEXT,
	BOLD,
	ITALIC,
	UNDERLINE,
	STRIKETHROUGH,
	SPOILER,
	FOOTER
};

typedef struct string {
	size_t size;
    size_t length;
	char* body;
} string;

void s_concat(string* a, string* b) {
	a = realloc(a->body, a->length + b->length);
	a->size = a->length + b->length;
	memmove(&a->body[a->length], b->body, b->length);
	free(b);
}

typedef struct token {
	enum TokenFlag type;
	string content;
} token ;
