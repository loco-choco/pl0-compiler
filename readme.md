#define MAX 100

| Symbol    | Token     |
|-----------|-----------|
| PROCEDURE | procedure |
| CONST     | const     |
| VAR       | var       |
| CALL      | call      |
| BEGIN     | begin     |
| END       | end       |
| IF        | if        |
| THEN      | then      |
| WHILE     | while     |
| DO        | do        |
| ODD       | odd       |
| +         | plus      |
| -         | minus     |
| *         | mult      |
| /         | div       |
| <>        | diff      |
| <         | less      |
| >         | bigger    |
| <=        | less_eq   |
| >=        | bigg_eq   |
| =         | equal     |
| :=        | assign    |
| .         | end_prog  |
| ;         | end_exp   |
| ,         | separator |
| (         | open_exp  |
| )         | close_exp |


| String  | Rule                          |
|---------|-------------------------------|
| ident   | (a-z + A-z)(a-z + A-Z + 0-9)* |
| number  | (0-9)(0-9)*                   |
| reserved| see reserved table            |


comments : {_anything_}
invisible_chars: \n , \r , \t , Space


Error messages: 
- Invalid char, when you read anything that isn't an ident, number or reserved (outside a comment)
- Malformed assign operator, when an equal sign "=" is not found after ":"
- Unexpected end of file, when you don't close the comment
- Number too long, when the number has more than MAX char
- Identifier too long, when the ident has more than MAX char

First draft:

![alt text](/assets/image.png)

automaton for reading identifiers and checking if they are reserved words. If they are, return the apropriate token found  in the reserved table

Second draft:

![alt text](/assets/image1.png)

then we add the invisible_chars that are consumed before reading the word

Third draft:

![alt text](/assets/image2.png)

now we add the comments processing step

Fourth draft: 

![alt text](/assets/image4.png)

here we add the number processing step

Fifth draft:

![alt text](/assets/image5.png)

in this stage we identify and check all the reserved symbols that weren't treated in the first draft

Final draft:

![alt text](/assets/image6.png)

Finally we handle the error messages

Access link to edit the report:

[Work Report 01](https://www.overleaf.com/4926265154ccxfgqcxdbbj#861c78)
