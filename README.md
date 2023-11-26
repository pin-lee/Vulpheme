# anna
Pronounced Anya, Anna is a small markdown renderer supporting a minimal subset of markdown.

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

