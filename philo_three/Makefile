# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmoumani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/05 12:03:01 by hmoumani          #+#    #+#              #
#    Updated: 2021/02/05 12:03:02 by hmoumani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=philo_three.c utils.c life_functions.c doctor.c

FLAGS=-Wextra -Wall -Werror

NAME=philo_three

$(NAME):
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

re: fclean $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
