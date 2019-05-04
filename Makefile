SRC_DIR= ./src

bfs:
	g++ ${SRC_DIR}/bfs.cpp ${SRC_DIR}/puzzle.cpp

ids:
	g++ ${SRC_DIR}/ids.cpp ${SRC_DIR}/puzzle.cpp

astar:
	g++ ${SRC_DIR}/astar.cpp ${SRC_DIR}/heap.cpp ${SRC_DIR}/puzzle.cpp

greedy:
	g++ ${SRC_DIR}/greedy.cpp ${SRC_DIR}/heap.cpp ${SRC_DIR}/puzzle.cpp

ucs:
	g++ ${SRC_DIR}/ucs.cpp ${SRC_DIR}/heap.cpp ${SRC_DIR}/puzzle.cpp

hill:
	g++ ${SRC_DIR}/hill.cpp ${SRC_DIR}/puzzle.cpp
