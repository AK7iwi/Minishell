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

III) Redirections:

- Before: \, OPERATOR, O_PAREN, C_PAREN, WORD

- After: WORD

c) ast_creator



III) Exec

Functions : 

1) Prototype

2) Functionality

3) Parameters

4) Return Value / Errors

a) cd

- getenv:

1) char *getenv(const char *name);

2) 

- Retrieves the value of an environment variable.
- Searches for name in the environment and returns its value as a string.

3) 

 - name: The name of the environment variable (case-sensitive)

4) 

- Returns a pointer to the value of the environment variable if found.
- Returns NULL if the variable does not exist.
- Does not modify errno on failure


- getcwd:

1) char *getcwd(char *buf, size_t size);

2) 

getcwd retrieves the current working directory of the calling process and stores it in the buffer provided by buf.

- If buf is NULL, getcwd dynamically allocates memory using malloc, which must be freed by the caller.

- If buf is not NULL, it must have enough space (size bytes) to store the full pathname.

3) 

- buf: A pointer to a buffer where the current working directory will be stored. If NULL, malloc is used.

- size: The size of the buffer. If buf is NULL, this parameter is ignored.

4) 

- On success, getcwd returns a pointer to the buffer containing the current working directory.

- On failure, it returns NULL and sets errno to indicate the error:

    ERANGE: The buffer size is too small.
    EACCES: Insufficient permissions to access a directory in the path.
    ENOMEM: Insufficient memory if malloc is used.

- chdir:

1) int chdir(const char *path);


2) 

- Changes the current working directory of the calling process to path.

- Affects subsequent file and directory operations.

3) 

path: The path to the new working directory. It can be:

- An absolute path (/home/user).
- A relative path (../folder).

4) 

- Returns 0 on success.

- Returns -1 on failure and sets errno accordingly:

    EACCES: Permission denied.
    ENOENT: The specified path does not exist.
    ENOTDIR: A component of the path is not a directory.


