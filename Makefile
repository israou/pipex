# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 00:51:52 by ichaabi           #+#    #+#              #
#    Updated: 2024/04/03 01:29:16 by ichaabi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_B = pipex_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC =	pipex.c \
		pipex_utils.c \
		split.c \
		split_spaces.c \


SRC_B =	pipex_bonus.c \
		split_spaces_bonus.c \
		split_bonus.c \
		pipex_utils_bonus.c \
		here_doc.c \

OBJ = $(SRC:.c=.o)

OBJB = $(SRC_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

bonus: $(OBJB)
		$(CC) $(OBJB) -o $(NAME_B)

%.o : %.c ../bonus/pipex_bonus.h pipex.h
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(NAME_B)

re: fclean all

.PHONY: all clean fclean re