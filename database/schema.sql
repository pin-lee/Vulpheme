CREATE TABLE files (
    file_path VARCHAR(255),
    file_type INTEGER();
    file_length INTEGER();
    time_created DATETIME(),
    time_changed DATETIME(),
    time_registered DATETIME(DEFAULT CURRENT_TIMESTAMP),
    time_entry_updated DATETIME(ON UPDATE DEFAULT CURRENT_TIMESTAMP),
);

CREATE TABLE words {
    word VARCHAR(45),
    classification INTEGER(),
};

CREATE TABLE morphemes {
    
};

CREATE TABLE file_file_associations {};

CREATE TABLE file_word_associations {};

CREATE TABLE word_word_associations {};

CREATE TABLE word_morpheme_associations {};