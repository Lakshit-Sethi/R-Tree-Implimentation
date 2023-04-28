runRtree: driver.o search.o insertion.o utils.o traversal.o rTrees.o
	gcc -o runRtree driver.o search.o insertion.o utils.o traversal.o rTrees.o
	./runRtree
driver.o: driver.c rTrees.h
	gcc -c driver.c
search.o: search.c utils.h rTrees.h
	gcc -c search.c
insertion.o: insertion.c utils.h rTrees.h
	gcc -c insertion.c
traversal.o: traversal.c utils.h rTrees.h
	gcc -c traversal.c
utils.o: utils.c utils.h rTrees.h
	gcc -c utils.c
rTrees.o: rTrees.c rTrees.h utils.h
	gcc -c rTrees.c
clear:
	rm *.o
