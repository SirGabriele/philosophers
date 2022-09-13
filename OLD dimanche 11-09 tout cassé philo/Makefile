# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbrousse <kbrousse@student.42angoulem      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/20 10:12:21 by kbrousse          #+#    #+#              #
#    Updated: 2022/09/10 22:22:09 by kbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c			\
	check_args.c		\
	launch_program.c	\
	god_routine.c		\
	routine.c			\
	print_messages.c	\
	clear_program.c

UTILS = utils.c

INIT = init_structures.c

SRCS = $(addprefix src/, $(SRC))		\
	$(addprefix src/utils/, $(UTILS))	\
	$(addprefix src/init/, $(INIT))

CC = gcc

FLAGS =	-Wall -Wextra -Werror -g -pthread

OBJS = $(SRCS:.c=.o)

all: $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~     Clean terminated!     ~"
	@echo "*           philo           *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.c.o:
	@$(CC) $(FLAGS) -c -o $@ $< 
 
$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32m~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"
	@echo "*                           *"
	@echo "~  Compilation terminated!  ~"
	@echo "*           philo           *"
	@echo "~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\033[0m"

.PHONY: all clean fclean re
