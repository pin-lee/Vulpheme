CREATE TABLE IF NOT EXISTS files (
    file_path TEXT,
    file_type INTEGER,
    file_length INTEGER,
    time_created INTEGER,
    time_changed INTEGER,
    time_registered INTEGER,
    time_entry_updated INTEGER
);

CREATE TABLE IF NOT EXISTS words (
    word TEXT,
    is_noun INTEGER,
    is_verb INTEGER
);

CREATE TABLE IF NOT EXISTS file_file_associations (
    id_1 INTEGER,
    id_2 INTEGER,
    strength INTEGER
);

CREATE TABLE IF NOT EXISTS file_word_associations (
    id_f INTEGER,
    id_w INTEGER,
    occurence_frequency INTEGER
);

CREATE TABLE IF NOT EXISTS word_word_associations (
    id_1 INTEGER,
    id_2 INTEGER,
    strength INTEGER
);
