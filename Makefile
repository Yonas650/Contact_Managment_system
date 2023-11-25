cms: main.o contact.o contactbst.o myvector.o
	g++  main.o contact.o contactbst.o myvector.o -o cms
main.o: main.cpp
	g++ -c main.cpp
contact.o: contact.cpp contact.h
	g++ -c contact.cpp
contactbst.o: contactbst.cpp contactbst.h
	g++ -c contactbst.cpp
myvector.o: myvector.cpp myvector.h
	g++ -c myvector.cpp
clean:
	rm *.o cms