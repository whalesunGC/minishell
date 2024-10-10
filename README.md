# minishell
@wichee and @apoh minihell project

## Project Outline

Only one global variable to indicate received signal.
Not interpretation of unclosed quotes or special characters such as \ (backslash) or ; (semicolon)

(1) Expansion - ENV Variables, **envp

(2) Lexing - Input validation, tokenization 

(3) Parsing - Syntax, data structure design

(4) Redirection - heredocs and normal

(5) Execution - pipex, PATH variable, working history

(6) Built-Ins - echo, cd, pwd, export, unset, env, exit

(7) Signal Handling - ctrl-C, ctrl-D ctrl-\
