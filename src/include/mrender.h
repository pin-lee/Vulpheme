#include <stdlib.h>
#include <string.h>

#define PD_BOLD 			sizeof ("<b></b>") - 1
#define PD_BREAK			sizeof ("<br>") - 1
#define PD_CODE_BLOCK		sizeof ("<pre><code></code></pre>") - 1
#define PD_CONTENT_EMBED	sizeof ("<embed src=""/>") - 1
#define PD_HEADER			sizeof ("<hn></hn>") - 1
#define PD_HORIZONTAL_LINE	sizeof ("<hr>") - 1
#define PD_FOOTER			sizeof ("<footer></footer>") - 1
#define PD_HYPERLINK		sizeof ("<a href=""></a>") - 1
#define PD_INLINE_CODE		sizeof ("<code></code>") - 1
#define PD_ITALIC			sizeof ("<em></em>") - 1
#define PD_LIST_ELEMENT		sizeof ("<li></li>") - 1
#define PD_ORDERED_LIST		sizeof ("<ol></ol>") - 1
#define PD_PLAIN_TEXT		sizeof ("<p></p>") - 1
#define PD_QUOTATION		sizeof ("<blockquote></blockquote>") - 1
#define PD_SPOILER			sizeof ("<span class=\"spoiler\"></span>") - 1
#define PD_STRIKETHROUGH	sizeof ("<s></s>") - 1
#define PD_TABLE			sizeof ("<table></table>") - 1
#define PD_TABLE_DATA		sizeof ("<td></td>") - 1
#define PD_TABLE_ROW		sizeof ("<tr></tr>") - 1
#define PD_TASK_LIST		sizeof ("<ul class=\"task_list\"></ul>") - 1
#define PD_UNDERLINE		sizeof ("<u></u>") - 1
#define PD_UNORDERED_LIST	sizeof ("<ul></ul>") - 1

enum TokenFlag {
	BOLD,
	BREAK,
	CODE_BLOCK,
	CONTENT_EMBED,
    HEADER,
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
	TASK_LIST,
	UNDERLINE,
	UNORDERED_LIST,
};

typedef struct string {
	size_t size;
    size_t length;
	char* body;
} string;

typedef struct token {
	enum TokenFlag type;
	string content;
} token ;
