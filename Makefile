# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 17:00:20 by alejandj          #+#    #+#              #
#    Updated: 2025/05/03 19:51:22 by alejandj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes

# Libft
LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a

SRC =	src/pipex.c		\

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

# Compilar el ejecutable
$(NAME) : $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBDIR) -lft -o $(NAME)

# Compilar la biblioteca
$(LIBFT):
	make -C $(LIBDIR)

%.o: %.c pipex.h $(LIBDIR)/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "Object files removed."

fclean: clean
	@rm -rf $(NAME)
	@echo "Executable $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re