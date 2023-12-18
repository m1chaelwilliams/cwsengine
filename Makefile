PROJECTNAME = project

OUTPUT_DIR = build

INCLUDE_DIRS = -Iinclude -Iheaders

LIB_DIRS = -Llib

LIBS = -lglfw3 -lopengl32 -lgdi32 -lassimp.dll

SRC = $(wildcard src/*.cpp) src/glad.c

CFLAGS = -DDEBUG

CC = g++

test:
	$(CC) $(CFLAGS) $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)

run: test
	cd $(OUTPUT_DIR) && $(PROJECTNAME)

.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)