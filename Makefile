# Variables
CC = c++
CFLAGS = -std=c++17 #-Wall -Werror -Wextra
AR = ar rcs
RM = rm -rf

# Directories
VPATH =	./include \
		./components

COMP_DIR = ./components
INC_DIR = ./include
OBJ_DIR = ./obj

# Include Directories
INCLUDE_DIRS = 	$(INC_DIR) \
				$(COMP_DIR)

INCLUDE = $(addprefix -I, $(INCLUDE_DIRS))

# Target
NAME = libftpp.a
MAIN_FILE = main.cpp
MAIN_OBJ = $(OBJ_DIR)/$(notdir $(MAIN_FILE:.cpp=.o))
LDL_FLAGS = -L. -lftpp

# Find source files and define object files
SRCS = $(shell find $(COMP_DIR) -name "*.cpp")
OBJS = $(OBJ_DIR)/$(notdir $(SRCS:.cpp=.o))

all: $(NAME) $(MAIN_OBJ) test

$(NAME): $(OBJ_DIR) $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo $(NAME) built

$(OBJ_DIR)/%.o: $(COMP_DIR)/%/*.cpp
	@echo Compiling file: $(notdir $<).
	@$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

# Rule for compiling main.cpp to obj file
$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling main file: $(notdir $<).
	@$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@

$(OBJ_DIR):
	@echo Directory $(OBJ_DIR) not found. Creating.
	@mkdir -p $(OBJ_DIR)

test: $(NAME) $(MAIN_OBJ)
	$(CC) $(MAIN_FILE) $(CFLAGS) $(INCLUDE) $(LDL_FLAGS)

clean:
	@$(RM) $(OBJ_DIR)
	@echo $(NAME) cleaned.

fclean: clean
	@$(RM) $(NAME)
	@echo $(NAME) fully cleaned.

re: fclean all

debug_makefile:
	@echo OBJS: $(OBJS)
	@echo SRCS: $(SRCS)
	@echo INCLUDE: $(INCLUDE)
	@echo MAIN_OBJ: $(MAIN_OBJ)

.PHONY: all clean fclean re debug_makefile
