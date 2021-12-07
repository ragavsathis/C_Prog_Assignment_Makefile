# The compiler
CC = gcc

# The compiler flags
CFLAG = -Wall

SRC_CODE_PATH := lib/*
TEST_CASE_PATH := test
TARGET := buffer_test
BUILD_FOLDER_NAME := build


INC_DIRS := $(addprefix -I./, $(wildcard $(SRC_CODE_PATH)))
SRC_FILES := $(notdir $(wildcard $(SRC_CODE_PATH)/*.c | $(TEST_CASE_PATH)/*.c))
SRC_TO_OBJ_FILES := $(SRC_FILES:.c=.o)
OBJ_FILES := $(addprefix $(BUILD_FOLDER_NAME)/, $(SRC_TO_OBJ_FILES))

# OS detection
OS_NAME = Windows
TARGET_EXTENSION := .exe
ifneq ($(OS), Windows_NT)
	UNAME = $(shell uname -s)
	ifeq ($(UNAME), Linux)
		OS_NAME = Linux
		TARGET_EXTENSION := .out
	else
		OS_NAME = Unknown
	endif
endif


all: clean build_test
	@echo "*** OS: $(OS_NAME)"
	@echo "*** Running the testcases"
	@echo $(INC_DIRS)
	@./$(TARGET)$(TARGET_EXTENSION)

$(BUILD_FOLDER_NAME)/%.o: $(SRC_CODE_PATH)/%.c
	@echo "### Created the .o files from lib/ !!!!"
	@$(CC) -MMD $(CFLAG) -c $< -o $@

$(BUILD_FOLDER_NAME)/%.o: $(TEST_CASE_PATH)/%.c
	@echo "### Created the .o files from test/ !!!!"
	@$(CC) -MMD $(CFLAG) -c $< $(INC_DIRS) -o $@

build_test: mkbuild_folder $(OBJ_FILES)
	@echo "### Building the testcases !!!"
	@$(CC) $(CFLAG) $(OBJ_FILES) -o $(TARGET)$(TARGET_EXTENSION)

execute_test: build_test
	@echo "### Executing the testcases"
	./$(TARGET)$(TARGET_EXTENSION)

mkbuild_folder:
	@echo "### Making the build directory for storing the object files !!!!"
	@mkdir -p $(BUILD_FOLDER_NAME)

clean:
	@echo "### Cleaning the build directory !!!"
	@echo "### Removing the .o and .d files"
	@rm -rf ${BUILD_FOLDER_NAME}

.PHONY: clean mkbuild_folder build_test execute_test all
