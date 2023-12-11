#include <vector>
#include <ftw.h>
#include <sys/stat.h>

struct enum class flag {
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

struct string {
	unsigned int length;
	char* body;
};

struct token {
	flag type;
	string content;
};

struct markdown_renderer {

	static const size_t C_SIZE = sizeof (char);

	explicit markdown_renderer(const char* start_path) {
		// walk down files, calling load_file on each one
		// if this works out, the lexer will have been called on each one
		// next we throw the newly minted (lexed) tokens at the parser(s)
		// then export to files
		if (nftw(start_path, load_file, NUM_OPEN_FILE_DESC, BITFLAGS)) {

		}
	}

	static inline bool is_parent_path_of(string* a, string* b) {
		if (a->length <= b->length) { return false; }
		for (unsigned int i{}; i < a->length; i++) {
			if (a->body[i] != b->body[i]) { return false; }
		}
		return true;
	}

	static inline int load_file(const char* file_path, const stat* file_staus,
	int type_flag, FTW* ftw_buffer) {



		switch (type_flag) {
			case FTW_F: {} break;
			case FTW_SL: {
				// if the symlink links to higher up, skip
				//if (){} TODO
			} break;
			default: { return 1; } // TODO err
		}

		// proceed if the file is markdown
		unsigned int length = sizeof (*file_path) / C_SIZE;
		T buff[2];
		memcpy(&buff, &(file_path[length - 2]), 2);
		if (*buff == *"md") {
			FILE* file = fopen(file_path, "r");

	}

	static inline int lex_file(FILE file) {
		// must load file as chunks because fopen is a stream
		// this is better for memory consumption, anyway
		//fread(void ptr[restrict .size * .nmemb], )
		return 0;
	};


	void combinator(T* input, void (*parser)(T*)...) {
		parser(input);
	}

	int BITFLAGS = FTW_PHYS;
		string content;
		std::vector<token> tokens;

};
