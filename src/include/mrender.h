#include <stdlib.h>
#include <string.h>

#define NOPENFD 100

/* PADDING documentation
 * The ensuing preprocessor directives are used to tell the parser how much
 * memory to allocate for formatted output.
*/
#define PD_BOLD 			sizeof ("<b></b>")							- 1
#define PD_BREAK			sizeof ("<br>")								- 1
#define PD_CODE_BLOCK		sizeof ("<pre><code></code></pre>")			- 1
#define PD_CONTENT_EMBED	sizeof ("<embed src=""/>")					- 1
#define PD_HEADER_1			sizeof ("<h1></h1>")						- 1
#define PD_HEADER_2			sizeof ("<h2></h2>")						- 1
#define PD_HEADER_3			sizeof ("<h3></h3>")						- 1
#define PD_HEADER_4			sizeof ("<h4></h4>")						- 1
#define PD_HEADER_5			sizeof ("<h5></h5>")						- 1
#define PD_HEADER_6			sizeof ("<h6></h6>")						- 1
#define PD_HORIZONTAL_LINE	sizeof ("<hr>")								- 1
#define PD_FOOTER			sizeof ("<footer></footer>")				- 1
#define PD_HYPERLINK		sizeof ("<a href=""></a>")					- 1
#define PD_INLINE_CODE		sizeof ("<code></code>")					- 1
#define PD_ITALIC			sizeof ("<em></em>")						- 1
#define PD_LIST_ELEMENT		sizeof ("<li></li>")						- 1
#define PD_ORDERED_LIST		sizeof ("<ol></ol>")						- 1
#define PD_PLAIN_TEXT		sizeof ("<p></p>")							- 1
#define PD_QUOTATION		sizeof ("<blockquote></blockquote>")		- 1
#define PD_SPOILER			sizeof ("<span class=\"spoiler\"></span>")	- 1
#define PD_STRIKETHROUGH	sizeof ("<s></s>")							- 1
#define PD_TABLE			sizeof ("<table></table>")					- 1
#define PD_TABLE_DATA		sizeof ("<td></td>")						- 1
#define PD_TABLE_ROW		sizeof ("<tr></tr>")						- 1
#define PD_TASK_FINISHED	sizeof ("<ul class=\"task_list\"></ul>")	- 1
#define PD_TASK_UNFINISHED	sizeof ("<ul class=\"task_list\"></ul>")	- 1
#define PD_UNDERLINE		sizeof ("<u></u>")							- 1
#define PD_UNORDERED_LIST	sizeof ("<ul></ul>")						- 1

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
};

typedef struct token {
	enum TokenFlag type;
	size_t length;
	char* body;
} token ;



int tokenize(char* text, size_t text_length) {
    if (!text_length) return 0;
    // lex the file into tokens
    // build the word database
    // if number, do
    size_t token_length, i = 0;
    goto first_in_line;
    while (i < text_length) {
        switch (text[i]) {
            case ('\n'): {
                // TODO, end single line tokens here
                first_in_line:
                if ('1' <= text[i] && text[i] <= '9') { // ORDERED LIST
                    while ('0' <= text[++i] && text[i] <= '9');
                    if (text[i] == '.' && text[++i] == ' ') {
                        // TODO
                    } 
                }
                switch (text[++i]) {
                    case ('#'): { // HEADER
                        int level = 1;
                        while (text[++i] == '#') { level++; }
                        if (text[i] == ' ') {

                        }
                    } break;
                    case ('-'): { // UNORDERED LIST & TASK LIST
                        if (text[++i] == ' ') {
                            
                        }
                    } break;
                    case ('>'): { // BLOCK QUOTE

                    } break;

                }
            } break;
            case ('|'): {} break;   // spoiler
            case ('\\'): {} break;  // escape, skip
            case ('`'): {} break;
            case ('!'): {} break;
            case ('['): {} break;
            case ('*'): {} break;
            case ('_'): {} break;
            case ('~'): {} break;
            default: { 
                // todo add to present token
            }
        }
        i++;
    } 

    printf("%s\n", text);
    return 0;
}