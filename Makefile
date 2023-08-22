CXX = g++
SRCS = main.cpp game.cpp
HEADERS = game.h

tictactoe: ${SRCS} ${HEADERS}
	${CXX} ${SRCS} -o tictactoe

clean:
	rm -f *.o program1

backup: ${SRCS} ${HEADERS}
	cp -f main.cpp backup/main.cpp
	cp -f game.cpp backup/game.cpp
	cp -f game.h backup/game.h
