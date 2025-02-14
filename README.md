I) Init

- getenv: 

II) Parser

a) lexer

b) syn_analyzer

Synthax rules: 

OPERATOR (&&, ||, |)
REDIR (<,<<,>,>>)
O_PAREN 
C_PAREN
WORD(+ENV_VAR)

I) Operator 

- Before: WORD, C_PAREN

- After: WORD, O_PAREN, REDIR

II) Parse for paren

a) O_paren:

- Before: \, OPERATOR, O_PAREN

- After: WORD, REDIR, O_PAREN

b) C_paren:

- Before: WORD, C_PAREN

- After: \ , OPERATOR, REDIR, C_PAREN

III) Parse for redirection:

- Before: \, OPERATOR, O_PAREN, C_PAREN, WORD

- After: WORD

c) ast_creator

III) Exec

fct: 

a) cd

- getcwd:

1) char *getcwd(char *buf, size_t size);

2) 


- chdir:


- getenv:



