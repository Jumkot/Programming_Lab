APP_NAME = coder

CFLAGS = -Wall -Werror -Wextra
DEPSFLAGS = -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

APP_PATH = $(BIN_DIR)/$(APP_NAME)

APP_SOURCES = $(wildcard $(SRC_DIR)/*.c)
APP_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(APP_SOURCES))

DEPS = $(APP_OBJECTS:.o=.d)

all: $(APP_PATH)

$(APP_PATH): $(APP_OBJECTS)
	gcc $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c $(CFLAGS) $(DEPSFLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm $(APP_PATH) $(OBJ_DIR)/*.[aod]

-include $(DEPS)

.PHONY: all clean