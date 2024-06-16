<programa> ::= <bloco> .
<bloco> ::= <declaracao> <comando>
<declaracao> ::= <constante> <variavel> <procedimento>
<constante> ::= CONST ident = numero <mais_const> ; | λ
<mais_const> ::= , ident = numero <mais_const> | λ
<variavel> ::= VAR ident <mais_var> ; | λ
<mais_var> ::= , ident <mais_var> | λ
<procedimento> ::= PROCEDURE ident ; <bloco> ; <procedimento> | λ
<comando> ::= ident := <expressao>
    | CALL ident
    | BEGIN <comando> <mais_cmd> END
    | IF <condicao> THEN <comando>
    | WHILE <condicao> DO <comando>
    | λ
<mais_cmd> ::= ; <comando> <mais_cmd> | λ
<expressao> ::= <operador_unario> <termo> <mais_termos>
<operador_unario> ::= - | + | λ
<termo> ::= <fator> <mais_fatores>
<mais_termos> ::= - <termo> <mais_termos> | + <termo> <mais_termos> | λ
<fator> ::= ident | numero | ( <expressão> )
<mais_fatores> ::= * <fator> <mais_fatores> | / <fator> <mais_fatores> | λ
<condicao> ::= ODD <expressao>
    | <expressao> <relacional> <expressao>
<relacional> ::= = | <> | < | <= | > | >=

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
