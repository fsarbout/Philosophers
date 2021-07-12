# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsarbout <fsarbout@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/10 20:29:56 by fsarbout          #+#    #+#              #
#    Updated: 2021/07/12 12:41:51 by fsarbout         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -g

CFLAGS = -Wall -Wextra -Werror -lpthread -fsanitize=address

SRC =  *.c

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