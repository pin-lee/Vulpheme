# Markdown Renderer (yes)

## How to factory assembly line ceramic

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

## Supported Markdown Features and Syntax
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
| Footnote


### Table

If you have
```markdown
| th1 | th2 | thn |
|-----|-----|-----|
| item | item | item |
```
the whitespace around token identifiers gets removed by the lexer, so it doesn't actually matter if you have it or not.
Additionally, I hate having to write out the `|----|----|`, but I am keeping support for it for markdown reasons.
Depending on how well I am able to get work done, I might support a superior version, `|-`.

## Persistence and Data Oriented Design

Use of a database system is necessary. SQLite3 has been selected. A table for source and destination files will be constructed.

The justification for loading the whole file into memory with chunks into an arena is that memory is a lot faster to access than disk, so even though going character by character with an fread size of 1 would be *algorithmically* more efficient, the fact of the matter is that the disk is 10,000 times slower than memory, so several passes over the data are faster. Additionally, using an arena allocator will allow us to use the least amount of practical allocations, such that the memory used is within the *about* the same order of magnitude (hopefully) as the size of the largest file being processed.

[Justification](https://stackoverflow.com/questions/1100311/what-is-the-ideal-growth-rate-for-a-dynamically-allocated-array) for 1.5 as the arena scaling factor.