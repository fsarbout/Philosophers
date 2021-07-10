# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/10 20:29:56 by fsarbout          #+#    #+#              #
#    Updated: 2021/07/10 20:33:13 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -g -ltermcap

CFLAGS = -Wall -Wextra -Werror -lpthread

SRC =  *.c

all : $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -g
clean:
	@rm -rf *.o
	@rm -rf philo.dSYM

fclean: clean
	@rm -rf $(NAME) 
re:	fclean all