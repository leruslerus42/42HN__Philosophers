# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrajaobe < rrajaobe@student.42heilbronn    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/27 05:39:02 by rrajaobe          #+#    #+#              #
#    Updated: 2022/04/18 05:25:00 by rrajaobe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

NAME = philosophers

SRC = 	./main.c	\
		./src/ft_parsing.c	\
		./src/ft_mutex.c	\
		./src/ft_utils.c	\
		./src/ft_thread.c	\
		./src/ft_thread_operations.c	\
	
OBJ = $(SRC: .c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -lpthread -o $(NAME)
#$(CFLAGS)
#$(NAME): *.c
#		$(CC) $(FLAGS) -c $(SRC)
#		ar rc $(NAME) *.o
#		$(CC) $(FLAGS) -L. -lft_philosophers -lpthread -o philo

clean:
		rm -f *.o
		rm -f ./src/*.o

fclean: clean
		rm -f $(NAME)

re: fclean all