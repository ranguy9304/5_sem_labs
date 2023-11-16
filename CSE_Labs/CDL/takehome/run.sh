bison -d tk.y
flex tk.l
gcc -o out lex.yy.c tk.tab.c
./out
