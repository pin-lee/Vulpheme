#pragma once

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <wn.h>
#include <string.h>
#include <booleans.h>

enum FileType {
	MARKDOWN,
	IMAGE,
	HTML,
};

const char* ADD_WORD = "INSERT INTO words (?, ?, ?);";


const char* ADD_FILE_WORD_ASSOCIATION = "INSERT INTO file";

const char* GET_WORD_FREQUENCY = "SELECT occurence_frequency \
FROM file_word_associations WHERE id_f='?' AND id_w='?';";


int prepare_queries(sqlite3* database);

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