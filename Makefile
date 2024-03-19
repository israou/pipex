# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ichaabi <ichaabi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 00:51:52 by ichaabi           #+#    #+#              #
#    Updated: 2024/03/18 02:29:34 by ichaabi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_B = pipex_bonus

CC = CC

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

SRC =	pipex.c \
		pipex_utils.c \
		ft_strjoin.c \


SRC_B =

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