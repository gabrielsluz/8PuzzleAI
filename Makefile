SRC_DIR= ./src-tsts

bfs:
	clang++ ${SRC_DIR}/bfs.cpp ${SRC_DIR}/puzzle.cpp

ids:
	clang++ ${SRC_DIR}/ids.cpp ${SRC_DIR}/puzzle.cpp

astar:
	clang++ ${SRC_DIR}/astar.cpp ${SRC_DIR}/heap.cpp ${SRC_DIR}/puzzle.cpp

greedy:
	clang++ ${SRC_DIR}/greedy.cpp ${SRC_DIR}/heap.cpp ${SRC_DIR}/puzzle.cpp

ucs:
	clang++ ${SRC_DIR}/ucs.cpp ${SRC_DIR}/heap.cpp ${SRC_DIR}/puzzle.cpp

hill:
	clang++ ${SRC_DIR}/hill.cpp ${SRC_DIR}/puzzle.cpp
