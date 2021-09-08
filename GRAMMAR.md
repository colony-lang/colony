# Colony Grammar

```
eval: expr_list ENDMARKER
expr_delim: ';' | NEWLINE
aug_assign_op: '+=' | '-=' | '*=' | '/=' | '%=' | '&=' | '|=' | '^=' | '<<=' | '>>=' | '**='
comp_op: '<' | '>' | '==' | '>=' | '<=' | '!='

expr_list: expr (expr_delim expr)* [expr_delim]

expr = test_list (
    | aug_assign_op test_list
    | (':' [test] '=' test_list)*
)

test_list: test (',' test)* [',']
test: or_test '?' or_test ':' test
or_test: and_test ('||' and_test)*
and_test: not_test ('&&' not_test)*
not_test: '!' not_test | comparison
comparison: comp_expr (comp_op comp_expr)*
comp_expr: xor_expr ('|' xor_expr)*
xor_expr: and_expr ('^' and_expr)*
and_expr: shift_expr ('&' shift_expr)*
shift_expr: arith_expr (('<<'|'>>') arith_expr)*
arith_expr: term (('+'|'-') term)*
term: factor (('*'|'@'|'/'|'%') factor)*
factor: ('+'|'-'|'~') factor | power
power: atom_expr ['**' factor]
atom_expr: atom trailer*

atom:
    # NOTE: in case of function definition `->` and after parts are always present
    | '(' [typed_arg_list] ')' ['->' test '{' [stmt_list] '}']
    | '[' [test_list] ']'
    | '{' [dict_maker] '}'
    | NAME
    | NUMBER
    | STRING
    | 'true'
    | 'false'

arg: NAME ['=' test]
arg_list: arg (',' arg)* [',']

# NOTE: in case of function definition
#       first `test` is always `NAME` and
#       `[':' test] ['=' test]` is not present
typed_arg: test [':' test] ['=' test]

# NOTE: in case of function definition
#       `'[' NAME ']'` and `'{' NAME '}'` could be present present
typed_arg_list:
    | typed_arg (',' typed_arg)* [',' '[' NAME ']' [',' '{' NAME '}']]
    | typed_arg (',' typed_arg)* [',' [
        | '[' NAME ']' [',' '{' NAME '}']
        | '{' NAME '}'
      ]]
    | '[' NAME ']' [',' '{' NAME '}']
    | '{' NAME '}'

dict_maker: test ':' test (',' test ':' test)* [',']

trailer:
    | '(' [arg_list] ')'
    | '[' [test_list] ']'
    | '.' NAME
```
