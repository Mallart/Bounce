SHELL=/bin/sh
SOURCES=$(wildcard *.cpp */*.cpp */*/*.cpp)
HEADERS=$(wildcard *.hpp */*.hpp */*/*.hpp)
CC=g++
FLAGS= -w -fcompare-debug-second

.objects:
	$(CC) $(FLAGS) -c $(HEADERS) $(SOURCES)

.build:
	$(CC) $(FLAGS) bounce.exe -o $(wildcard *.o) -lsfml-graphics -lsfml-window -lsfml-system

.make: .objects .build