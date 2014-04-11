mrc:
	clang -o mrc -Wall -L/opt/local/lib -I/opt/local/include -Iinc -llua mrc.c list.c utils.c scripting.c map.c error.c