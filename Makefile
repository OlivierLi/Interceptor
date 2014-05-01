CC=clang++
LIBS = -lsfml-system -lsfml-window -lGLEW
FLAGS=-Wall -Werror -Wextra -Wfatal-errors --std=c++11 -g
INCLUDE_DIRS=

all: src/main.cpp
	$(CC) $(FLAGS) $(INCLUDE_DIRS) -o bin/interceptor src/main.cpp  $(LIBS)

clean:
	rm bin/interceptor
	
