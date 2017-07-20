all: p4

p4: mphoto.o Image.o Position.o Point.o Photo.o House.o
	g++ -o p4 mphoto.o Image.o Position.o Point.o Photo.o House.o -lm
	
mphoto.o: mphoto.cpp
	g++ -c mphoto.cpp
	
Photo.o: Photo.cpp Photo.h
	g++ -c -std=c++11 Photo.cpp Photo.h

Image.o: Image.cpp Image.h
	g++ -c Image.cpp Image.h

House.o: House.cpp House.h
	g++ -c -std=c++14 House.cpp House.h

Position.o: Position.cpp Position.h
	g++ -c Position.cpp Position.h
	
Point.o: Point.h Point.cpp
	g++ -c Point.cpp Point.h

clear:
	rm *.o *.gch
