runRtree: driver.o search.o insertion.o utils.o traversal.o rTrees.o
	gcc -o runRtree driver.o search.o insertion.o utils.o traversal.o rTrees.o
	rm *.o
	./runRtree
driver.o: src/driver.c src/rTrees.h
	gcc -c src/driver.c
search.o: src/search.c src/utils.h src/rTrees.h
	gcc -c src/search.c
insertion.o: src/insertion.c src/utils.h src/rTrees.h
	gcc -c src/insertion.c
traversal.o: src/traversal.c src/utils.h src/rTrees.h
	gcc -c src/traversal.c
utils.o: src/utils.c src/utils.h src/rTrees.h
	gcc -c src/utils.c
rTrees.o: src/rTrees.c src/rTrees.h src/utils.h
	gcc -c src/rTrees.c
clear_:
	rm *.o
