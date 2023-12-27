# vulpes-db
A data oriented NoSQL graph database on top of SQLite for Vulpheme.

# Normalization of Form

## Initial form

### Nodes/Vertices
- Files
- Words
- Morphemes
- Possibly graphemes
### Relationships/Edges
- Directory (file↔file)
- Hyperlinks (file↔file)
- Frequency of occurence (file↔word)
- Synonym (word↔word)
- Antonym (word↔word)
- Occurence in (word↔morpheme↔grapheme↔word) (morphemes and graphemes can be words)