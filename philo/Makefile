# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 10:21:28 by pllucian          #+#    #+#              #
#    Updated: 2021/08/25 14:43:34 by pllucian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c simulation.c utils_philos.c utils.c

OBJS = $(SRCS:.c=.o)

INCL = philo.h

NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -f

%.o:		%.c $(INCL)
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $@ $^

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
