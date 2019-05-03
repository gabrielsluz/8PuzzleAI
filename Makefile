CC=clang++
BUILD_DIR = ./build
SRC_DIR = ./src
INCLUDE_DIR = ./include
BIN_DIR = ./bin

${BIN_DIR}/astar: ${BUILD_DIR}/astar.o ${BUILD_DIR}/puzzle.o
	${CC} -o ${BIN_DIR}/astar ${BUILD_DIR}/astar.o ${BUILD_DIR}/puzzle.o

${BIN_DIR}/bfs: ${BUILD_DIR}/bfs.o ${BUILD_DIR}/puzzle.o
	${CC} -o ${BIN_DIR}/bfs ${BUILD_DIR}/bfs.o ${BUILD_DIR}/puzzle.o

${BIN_DIR}/greedy: ${BUILD_DIR}/greedy.o ${BUILD_DIR}/puzzle.o
	${CC} -o ${BIN_DIR}/greedy ${BUILD_DIR}/greedy.o ${BUILD_DIR}/puzzle.o

${BIN_DIR}/ucs: ${BUILD_DIR}/ucs.o ${BUILD_DIR}/puzzle.o
	${CC} -o ${BIN_DIR}/ucs ${BUILD_DIR}/ucs.o ${BUILD_DIR}/puzzle.o

${BIN_DIR}/ids: ${BUILD_DIR}/ids.o ${BUILD_DIR}/puzzle.o
	${CC} -o ${BIN_DIR}/ids ${BUILD_DIR}/ids.o ${BUILD_DIR}/puzzle.o

${BIN_DIR}/hill: ${BUILD_DIR}/hill.o ${BUILD_DIR}/puzzle.o
	${CC} -o ${BIN_DIR}/hill ${BUILD_DIR}/hill.o ${BUILD_DIR}/puzzle.o
