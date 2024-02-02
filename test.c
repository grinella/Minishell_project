splitter;
input = (ls -la | grep a > file | ciao | come | stai echo "          ciao");

toks.word:
ls
-la
|
grep
a
>
file
|
ciao
|
come
|
stai

--------------------------------------------
tokenizer " "

NODO0-MATRICE0
ls
-la
NULL

NOTO1-MATRICE0
|
NULL

NODO2-MATRICE0
grep
a
>
file
NULL

NODO3-MATRICE0
ciao
NULL

NODO4-MATRICE0
|
NULL

NODO5-MATRICE0
come 
NULL

NODO6-MATRICE0
|
NULL

NODO7-MATRICE0
stai
NULL

NODO8-MATRICE0
NULL

