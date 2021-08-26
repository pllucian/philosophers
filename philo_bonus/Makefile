# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/11 10:21:28 by pllucian          #+#    #+#              #
#    Updated: 2021/08/25 23:35:47 by pllucian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	philo_bonus.c simulation_bonus.c \
		utils_philos_bonus.c utils_sem_kill.c utils_bonus.c

OBJS = $(SRCS:.c=.o)

INCL = philo_bonus.h

NAME = philo_bonus

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
