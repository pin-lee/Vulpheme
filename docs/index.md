# Vulpheme Technical Specification

## Vulpes Lemma - NLP

### Sources
- https://wordnet.princeton.edu/
- https://github.com/colingoldberg/morphemes

## Markdown Renderer

### Operation

1. System will be supplied a path
2. Supplied path will be file tree walked
3. Data will be loaded incrementally.
4. The lexer will look for control characters and assemble tokens with the following Al Gore rhythm (Al Gore invented the internet):
```python
token = [] # type-flagged vector buffer of characters
tokens = [] # vector of tokens
for character in chunk:
    if character == escape_character:
        tokens.append(token)
        token.clear() # wipe the buffer clean
        token.set_type(character) # set new type
    else:
        token.append(character)
# Note, type denotes text modifier, e.g., 
```
In addition to trigger characters (the reserved markdown ones), leading EOF (implicitly) and newline will denote new tokens.
Certain trigger characters which might signal a new token (such as *) will be invalidated if they are adjacent to some kind of whitespace.
1. The parser will iterate over the tokens, building a stack-based HTML structure so things will be enclosed properly. 
2. Export to a file

### Supported Markdown Features and Syntax
(Dated, see grammar.txt and mrender.h)
| Feature         | Syntax              |
|-----------------|---------------------|
| Header          | `#` `##` `###`      |
| Horizontal line | `---`               |
| Ordered list    | `1. ` `n. `         |
| Unordered list  | `- `                |
| Task list       | `- [ ]` `- [x]`     |
| Table           | *see below          |
| Code block      | ` ```content``` `   |
| Inline code     | ` `` `              |
| Quotation       | `> content`         |
| Content embed   | `![Title](path)`    |
| Hyperlink       | `[content](target)` |
| Plain text      | `content`           |
| Bold            | `**content**`       |
| Italic          | `*content*`         |
| Underline       | `__content__`       |
| Strikethrough   | `~~content~~`       |
| Spoiler         | `\|\|content\|\|`   |
| Footnote        | 


#### Tables
Tables will not be supported in the alpha version. Priority will be placed on other Vulpheme features.

### Persistence and Data Oriented Design

Use of a database system is necessary. SQLite3 has been selected. A table for source and destination files will be constructed.
