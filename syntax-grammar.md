\<programa> ::= \<bloco> .

\<bloco> ::= \<declaracao> \<comando>

\<declaracao> ::= \<constante> \<variavel> \<procedimento>

\<constante> ::= CONST ident = numero \<mais\_const> ; | λ

\<mais\_const> ::= , ident = numero \<mais\_const> | λ

\<variavel> ::= VAR ident \<mais\_var> ; | λ

\<mais\_var> ::= , ident \<mais\_var> | λ

\<procedimento> ::= PROCEDURE ident ; \<bloco> ; \<procedimento> | λ

\<comando> ::= ident := \<expressao>
    | CALL ident
    | BEGIN \<comando> \<mais\_cmd> END
    | IF \<condicao> THEN \<comando>
    | WHILE \<condicao> DO \<comando>
    | λ

\<mais\_cmd> ::= ; \<comando> \<mais\_cmd> | λ

\<expressao> ::= \<operador\_unario> \<termo> \<mais\_termos>

\<operador\_unario> ::= - | + | λ

\<termo> ::= \<fator> \<mais\_fatores>

\<mais\_termos> ::= - \<termo> \<mais\_termos> | + \<termo> \<mais\_termos> | λ

\<fator> ::= ident | numero | ( \<expressão> )

\<mais\_fatores> ::= * \<fator> \<mais\_fatores> | / \<fator> \<mais\_fatores> | λ

\<condicao> ::= ODD \<expressao>
    | \<expressao> \<relacional> \<expressao>

\<relacional> ::= = | <> | < | <= | > | >=


| Rule | First | Follower |
| :--- | :---: | :------: |
| \<programa> | {CONST, VAR, PROCEDURE, ident, CALL, BEGIN, IF, WHILE, .} | {Lambda} |
| \<bloco> | {CONST, VAR, PROCEDURE, ident, CALL, BEGIN, IF, WHILE, Lambda} | {., ;} |
| \<declaracao> | {CONST, VAR, PROCEDURE, Lambda} | {ident, CALL, BEGIN, IF, WHILE, ., ;} |
| \<constante> | {CONST, Lambda} | {VAR, PROCEDURE, ident, CALL, BEGIN, IF, WHILE, ., ;} |
| \<mais\_const> | {',', Lambda} | {;} |
| \<variavel> | {VAR, Lambda} | {PROCEDURE, ident, CALL, BEGIN, IF, WHILE, ., ;} |
| \<mais\_var> | {',', Lambda} | {;} |
| \<procedimento> | {PROCEDURE, Lambda} | {ident, CALL, BEGIN, IF, WHILE, ., ;} |
| \<comando> | {ident, CALL, BEGIN, IF, WHILE, Lambda} | {;, END, .} |
| \<mais\_cmd> | {;, Lambda} | {END} |
| \<expressao> | {-, +, ident, numero, (} | {), THEN, DO, =, <>, <, <=, >, >=, ;, END, .} |
| \<operador\_unario> | {-, +, Lambda} | {ident, numero, (} |
| \<termo> | {ident, numero, (} | {-, +, ), THEN, DO, =, <>, <, <=, >, >=, ;, END, .} |
| \<mais\_termos> | {-, +, Lambda} | {), THEN, DO, =, <>, <, <=, >, >=, ;, END, .} |
| \<fator> | {ident, numero, (} | {\*, /, -, +, ), THEN, DO, =, <>, <, <=, >, >=, ;, END, .} |
| \<mais\_fatores> | {\*, /, Lambda} | {-, +, ), THEN, DO, =, <>, <, <=, >, >=, ;, END, .} |
| \<condicao> | {ODD, -, +, ident, numero, (} | {THEN, DO} |
| \<relacional> | {=, <>, <, <=, >, >=} | {-, +, ident, numero, (} | 
