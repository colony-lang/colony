# PEG Grammar of Colony

file: [exprs] ENDMARKER
repl: exprs NEWLINE* ENDMARKER

exprs:
    | expr (',' expr)+ [',']
    | expr ','
    | expr

expr:
    