# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/10 20:29:56 by fsarbout          #+#    #+#              #
#    Updated: 2022/02/07 15:38:13 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -lpthread -fsanitize=address 

SRC =  main.c\
	helpers.c\
	routine.c\
	collect_data.c

all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
clean:
	@rm -rf *.o
	@rm -rf philo.dSYM

fclean: clean
	@rm -rf $(NAME)
	@rm -rf philo.dSYM
re:	fclean all