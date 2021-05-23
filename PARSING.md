# PEG - Parsing Expression Grammar

## Parsing Expressions

| Expression | Name | Precedence |
|---|---|---|
| Nonterminal | Nonterminal | 6 |
| (<e>) | Parentheses | 6 |

## Lexical

| Expression | Name | Precedence |
|---|---|---|
| "string" | Literal String | 6 |
| [ab] | Character Class | 6 |
| ^[ab] | Negated Character Class | 6 |
| [a-c] | Character Range | 6 |
| ^[a-c] | Negated Character Range | 6 |
| - | Wildcard | 6 |


## Syntactic

| Expression | Name | Precedence |
|---|---|---|
| <e>? | Optional | 5 |
| <e>* | Zero or More | 5 |
| <e>+ | One or More | 5 |
| &<e> (Lookahead, for later) | Lookahead | 4 |
| !<e> (Lookahead, for later) | Forbid | 4 |
| <e1> ... <eN> | Sequence | 2 |
| <e1> \| ... \| <eN> | Ordered Choice | 1 |
