all: ttt2.o ttt1.o alphatoe count_nodes show_node



alphatoe: alphatoe.o ttt2.o ttt1.o
	gcc -std=c99 -Wall -pedantic -o alphatoe alphatoe.o  ttt2.o  ttt1.o
alphatoe.o: alphatoe.c
	gcc -std=c99 -Wall -pedantic -c alphatoe.c

count_nodes: count_nodes.o ttt2.o ttt1.o
	gcc -std=c99 -Wall -pedantic -o count_nodes count_nodes.o  ttt2.o  ttt1.o
count_nodes.o: count_nodes.c
	gcc -std=c99 -Wall -pedantic -c count_nodes.c

show_node: show_node.o ttt2.o ttt1.o
	gcc -std=c99 -Wall -pedantic -o show_node show_node.o  ttt2.o  ttt1.o
show_node.o: show_node.c
	gcc -std=c99 -Wall -pedantic -c show_node.c



ttt1.o: ttt1.c
	gcc -std=c99 -Wall -pedantic -c ttt1.c

ttt2.o: ttt2.c
	gcc -std=c99 -Wall -pedantic -c ttt2.c




clean:
	rm ttt1.o ttt2.o alphatoe alphatoe.o count_nodes.o count_nodes show_node.o show_node
