# PEG - Parsing Expression Grammar
# Parsing Combinators

## Parsing Expressions

| Expression                    | namespace                 | Precedence    |
|-------------------------------|---------------------------|---------------|
| Nonterminal                   | Nonterminal               | 6             |
| (\<e\>)                       | Parentheses               | 6             |

## Lexical (matching characters)

| Expression                    | Name                      | Precedence    |
|-------------------------------|---------------------------|---------------|
| "string"                      | Literal String            | 6             |
| [ab]                          | Character Class           | 6             |
| ^[ab]                         | Negated Character Class   | 6             |
| [a-c]                         | Character Range           | 6             |
| ^[a-c]                        | Negated Character Range   | 6             |
| -                             | Wildcard                  | 6             |


## Syntactic

| Expression                    | Name                      | Precedence    |
|-------------------------------|---------------------------|---------------|
| \<e\>?                        | Optional                  | 5             |
| \<e\>*                        | Zero or More              | 5             |
| \<e\>+                        | One or More               | 5             |
| &\<e\> (Lookahead, for later) | Lookahead (don't consume) | 4             |
| !\<e\> (Lookahead, for later) | Forbid (don't consume)    | 4             |
| \<e0\> \.\.\. \<eN\>          | Sequence                  | 2             |
| \<e0\> \| ... \| \<eN\>       | Ordered Choice            | 1             |


## Grammar
```
program: (expressions)? END

expressions: expression ((';' | NEWLINE)+ (expression)?)*

expression: 
	definition |
	declaration_assignment |


definition: NAME ':' expression

declaration_assignment: NAME ':' (expression)? '=' expression
deep_assignment: NAME (('[' expression ']') | (('.' | '::') NAME))+ augmented_assignment expression

augmented_assignment:
	':=' |
	'+=' |
    '-=' |
    '*=' |
    '/=' |
    '%=' |
    '&=' |
    '|=' |
    '^=' |
    '<<=' |
    '>>=' |
    '**='

```
