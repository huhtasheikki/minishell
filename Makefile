# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 16:18:57 by hhuhtane          #+#    #+#              #
#    Updated: 2020/12/16 22:15:40 by hhuhtane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell

_SRC = minishell.c test.c env.c scanner.c expansions.c
_OBJ = $(_SRC:.c=.o)
_INC = minishell.h
_LIBFT = libft.a

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes
LIBFT_DIR = libft

SRC = $(patsubst %,$(SRC_DIR)/%,$(_SRC))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
INC = $(patsubst %,$(INC_DIR)/%,$(_INC))
LIBFT = $(patsubst %,$(LIBFT_DIR)/%,$(_LIBFT))

INC_LIBFT = -I libft/includes

FLAGS = -Wall -Wextra -Werror -I $(INC_DIR) $(INC_LIBFT)

COLOR_RESET = \033[0m
COLOR_WAIT = \033[0;31m
COLOR_OK = \033[0;32m
COLOR_TITLE = \033[1;37m

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "MINISHELL:\t[$(COLOR_TITLE)Make started$(COLOR_RESET)]"
	@make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@echo "MINISHELL:\t[$(COLOR_TITLE)$@ $(COLOR_OK) made$(COLOR_RESET)]"
	@$(CC) $(FLAGS) -c -o $@ $<

$(OBJ_DIR):
	@echo "MINISHELL \t[$(COLOR_TITLE)objs folder $(COLOR_OK)created$(COLOR_RESET)]"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "MINISHELL \t[$(COLOR_TITLE)Objects & garbage $(COLOR_OK)cleaned$(COLOR_RESET)]"
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@find . -type f -name '.DS_Store' -delete
	@find . -type f -name '*~' -print -delete -o -name "#*#" -print -delete

fclean: clean
	@echo "MINISHELL \t[$(COLOR_TITLE)$(NAME) removed$(COLOR_RESET)]"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJ_DIR)

re: fclean all
