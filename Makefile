# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 17:00:20 by alejandj          #+#    #+#              #
#    Updated: 2025/05/04 13:15:29 by alejandj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes

# Directorios
LIBDIR = libft/
OBJDIR = obj/

SRC =	src/pipex.c			\
		src/pipex_utils.c	\

OBJECTS = $(SRC:src/%.c=$(OBJDIR)/%.o)

# Libreria
LIBFT = $(LIBDIR)/libft.a

all: $(NAME)

# Compilar el ejecutable
$(NAME) : $(OBJECTS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBDIR) -lft -o $(NAME)

# Compilar la biblioteca
$(LIBFT):
	make -C $(LIBDIR)

# Regla para crear los .o en el directorio obj
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "Object files removed."

fclean: clean
	@rm -rf $(NAME)
	@echo "Executable $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re