# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiranda <marvin@42quebec.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 16:42:57 by jmiranda          #+#    #+#              #
#    Updated: 2023/05/17 21:37:27 by jmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH   = src/

NAME    = philo

SRCS    = main.c \

OBJS    = ${SRCS:.c=.o}

CC      = gcc

CFLAGS  = -Wall -Wextra -Werror -pthread

all     : ${NAME}

${NAME} : ${OBJS}
				@$(CC) $(CFLAGS) ${OBJS} -o ${NAME}
				@echo Philo Is Complete!

%.o     : %.c
				@echo -n .
				@$(CC) $(CFLAGS) -c $< -o $@

clean   :
				rm -f ${OBJS}

fclean  : clean
				rm -f ${OBJS} ${NAME}

re      : fclean all

.PHONY  : all bonus clean fclean re
