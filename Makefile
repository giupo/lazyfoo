#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = main

#DIST specifies where to put the compiled code
DIST = dist

#This is the target that compiles our executable
all : $(OBJS) init
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(DIST)/$(OBJ_NAME)

init:
	mkdir -p $(DIST)

clean:
	rm -rf *~
	rm -rf dist/*
