CC = g++
CFLAGS = -Wall
SRC = src
OUT_DIR = bin
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJS = bin/main
MKDIR_P = mkdir -p

all: directories
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJS)

directories: $(OUT_DIR)

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}
