#pragma once

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <wn.h>
#include <string.h>
#include <stdbool.h>

enum FileType {
	MARKDOWN,
	IMAGE,
	HTML,
};

const char* ADD_WORD = "IF NOT EXISTS\
(SELECT * FROM words WHERE word=?) BEGIN\
INSERT INTO words (?, ?, ?) END;";

const char* ADD_FILE_WORD_ASSOCIATION = "IF EXISTS\
(SELECT FROM file_word_associations WHERE id_f='?') BEGIN \
UPDATE file_word_associations \
SET occurence_frequency = occurence_frequency + 1 \
WHERE id_f='? AND id_w='?' END ELSE BEGIN \
INSER INTO file_word_associations VALUES (?, ?, ?) END;";

const char* GET_WORD_FREQUENCY = "SELECT occurence_frequency \
FROM file_word_associations WHERE id_f='?' AND id_w='?';";


#define STMT_ALLOC (sqlite3_stmt*) malloc(1024)
sqlite3_stmt* add_word_stmnt;
sqlite3_stmt* add_file_word_stmnt;
sqlite3_stmt* get_word_freq_stmnt;
sqlite3_stmt* add_word_word_stmnt;

void prepare_statements(sqlite3* database) {
	add_word_stmnt		= STMT_ALLOC;
	add_file_word_stmnt	= STMT_ALLOC;
	get_word_freq_stmnt	= STMT_ALLOC;
	add_word_word_stmnt	= STMT_ALLOC;
	#define PREP_STMNT(CCXPR, OPTR) sqlite3_prepare_v2(database, CCXPR, sizeof (CCXPR), &OPTR, NULL)
	PREP_STMNT(ADD_WORD, add_word_stmnt);
	PREP_STMNT(ADD_FILE_WORD_ASSOCIATION, add_file_word_stmnt);
	PREP_STMNT(GET_WORD_FREQUENCY, get_word_freq_stmnt);
}

void free_statements() {
	free(add_word_stmnt);
	free(add_file_word_stmnt);
	free(get_word_freq_stmnt);
	free(add_word_word_stmnt);
}

void parse_words(char* text, size_t text_length, const char* file_path, sqlite3* database) {

	if (!wninit()) { return; }

	size_t cursor = 0;
	char word_buffer[101] = { '\0' };
	
	#define HERE text[cursor]

	for (size_t i = 0; i < text_length; i++) {
		size_t start = cursor;
		while ('a' <= HERE && HERE <= 'z' ||  'A' <= HERE && HERE <= 'Z') {
			cursor++;
		}
		size_t length = cursor - start; 
		if (length == 0 || length > 100) { continue; }
		memcpy(word_buffer, &text[start], length);
		word_buffer[length] = '\0';

		bool noun = findtheinfo_ds(word_buffer, NOUN, HYPERPTR, ALLSENSES);
		bool verb = findtheinfo_ds(word_buffer, VERB, HYPERPTR, ALLSENSES);
		
		

	}

	
}