# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 15:56:16 by houbeid           #+#    #+#              #
#    Updated: 2021/11/02 11:21:47 by houbeid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FILE = main.c philo_utils.c error.c

FLAG = -Wall -Wextra -Werror


all: $(NAME)

$(NAME):
	@gcc $(FLAG) $(FILE) -o $(NAME)
 
clean:
	@rm -f *.o 

fclean: clean
	@echo "Clean..."
	@rm -f $(NAME)

re: fclean all