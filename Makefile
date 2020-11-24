# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 16:18:57 by hhuhtane          #+#    #+#              #
#    Updated: 2020/11/24 17:56:41 by hhuhtane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell

_SRC = minishell.c test.c
_OBJ = $(_SRC:.c=.o)
_INC = minishell.h

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes

SRC = $(patsubst %,$(SRC_DIR)/%,$(_SRC))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
INC = $(patsubst %,$(INC_DIR)/%,$(_INC))

FLAGS = -Wall -Wextra -Werror

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I $(INC_DIR) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	$(CC) $(FLAGS) -I $(INC_DIR) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJS)
	find . -type f -name '.DS_Store' -delete
	find . -type f -name '*~' -print -delete -o -name "#*#" -print -delete

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
