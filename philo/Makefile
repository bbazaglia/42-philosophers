# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 11:39:42 by bbazagli          #+#    #+#              #
#    Updated: 2024/06/03 11:52:13 by bbazagli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
VPATH = philo
SOURCE = main.c args_validation.c init.c utils.c time.c
OBJDIR = obj
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCE))

all: $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling: $<"

clean:
	@rm -rf $(OBJDIR)
	@echo "objects removed"

fclean: clean
	@rm -f $(NAME)
	@echo "executable removed"

re: fclean all

.PHONY: all clean fclean re