# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/03 17:00:20 by alejandj          #+#    #+#              #
#    Updated: 2025/05/29 16:22:47 by alejandj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes

# Directorios
LIBDIR = libft/
OBJDIR = obj/

SRC =	src/pipex.c				\
		src/pipex_utils_1.c		\
		src/pipex_utils_2.c		\
		src/execution.c			\

OBJECTS = $(SRC:src/%.c=$(OBJDIR)/%.o)

# Libreria
LIBFT = $(LIBDIR)/libft.a

all: $(NAME)

# Compilar el ejecutable
$(NAME) : $(OBJECTS) $(LIBFT)
	@echo ""
	@echo "\033[0;31m⚙️ COMPILANDO... 🚀\033[0m"
	@echo ""
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBDIR) -lft -o $(NAME)

	@echo "\033[0;32m  ____    _                       \033[0m"
	@echo "\033[0;32m |  _ \  (_)  _ __     ___  __  __\033[0m"
	@echo "\033[0;32m | |_) | | | | '_ \   / _ \ \ \/ /\033[0m"
	@echo "\033[0;32m |  __/  | | | |_) | |  __/  >  < \033[0m"
	@echo "\033[0;32m |_|     |_| | .__/   \___| /_/\_\\ \033[0m"
	@echo "\033[0;32m             |_|                   \033[0m"

	@echo ""
	@echo "✅ \033[0;32mPIPEX COMPILADO EXITOSAMENTE!!!\033[0m 🎉🎉"
	@echo ""
	@echo "🔧 Listo para ejecutar. ¡Vamos a hacer magia! ✨"
	@echo ""

# Compilar la biblioteca
$(LIBFT):
	make -C $(LIBDIR)

# Regla para crear los .o en el directorio obj
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@echo "🧹 \033[0;32mObject files removed successfully! 🗑️\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "🚀 \033[0;32mExecutable $(NAME) has been removed! Bye bye! 👋\033[0m"

re: fclean all

.PHONY: all clean fclean re