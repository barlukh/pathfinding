# ************************************************************************************** #
#                                                                                        #
#   File:       Makefile                                                                 #
#   Purpose:    Main compilation file of the application                                 #
#   Author:     barlukh (Boris Gazur)                                                    #
#   Updated:    2026/01/26                                                               #
#                                                                                        #
# ************************************************************************************** #

NAME	=	pathfinding

CC		=	g++
CFLAGS	=	-Wall -Werror -Wextra -O0 -std=c++17 -g
LFLAGS	=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
VGFLAGS	=	--show-leak-kinds=all \
			--show-reachable=yes \
			--leak-check=full \
			--track-origins=yes \
			--undef-value-errors=yes \
			--track-fds=yes \
			--suppressions=vg.supp
RM		=	rm -rf

DIR_LIB	=	lib
DIR_HDR	=	include
DIR_OBJ	=	obj
DIR_SRC	=	src

HDR		=	$(wildcard $(DIR_HDR)/*.hpp)
OBJ		=	$(patsubst $(DIR_SRC)/%.cpp,$(DIR_OBJ)/%.o,$(SRC))
SRC		=	$(shell find $(DIR_SRC) -name "*.cpp")

all: $(NAME)

$(NAME): $(DIR_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L$(DIR_LIB) $(LFLAGS)
	@echo "✅ Compilation successful"

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	@echo "📁 Created directory for object files"

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp $(HDR) | prepare_dirs
	$(CC) $(CFLAGS) -I$(DIR_HDR) -c $< -o $@

clean:
	$(RM) $(DIR_OBJ)
	@echo "🧹 Object files removed"

fclean:
	$(RM) $(DIR_OBJ)
	@echo "🧹 Object files removed"
	$(RM) $(NAME)
	@echo "🧹 Executable removed"

prepare_dirs:
	mkdir -p $(sort $(dir $(OBJ)))

re: fclean all

run: $(NAME)
	./$(NAME)

valgrind: $(NAME)
	valgrind $(VGFLAGS) ./$(NAME)

.PHONY: all clean fclean prepare_dirs re run valgrind
