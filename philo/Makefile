# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 11:39:42 by bbazagli          #+#    #+#              #
#    Updated: 2024/06/17 14:57:04 by bbazagli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 
VPATH = philo
SOURCE = eat_sleep_think.c args_validation.c getter_setter.c init.c main.c monitor.c \
		safe_functions.c start_simulation.c take_fork.c time.c utils.c write.c
OBJDIR = obj
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SOURCE))

all: $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) -pthread

val: all
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--trace-children=yes \
		./$(NAME) 5 10000 200 200 5
#       --log-file=valgrind-out.txt \

hel: all
	valgrind \
		--tool=helgrind \
		--history-level=none \
		-s \
		./$(NAME) 5 1800 200 200 5
#       --log-file=helgrind-out.txt \

drd: all
	valgrind \
		--tool=drd \
		-s \
		./$(NAME) 5 1800 200 200 5
#       --log-file=drd-out.txt \

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
