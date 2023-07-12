# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmiranda <jmiranda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 16:42:57 by jmiranda          #+#    #+#              #
#    Updated: 2023/07/12 13:41:45 by jmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH   = src/

NAME    = philo

SRCS    = error_and_clear.c initialization.c main.c one_philo.c \
		  reaper_check.c routine.c time_and_print.c \

OBJS    = ${SRCS:.c=.o}

CC      = gcc

CFLAGS  = -Wall -Wextra -Werror -Iinc -pthread

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
				rm -f ${NAME}

re      : fclean all

.PHONY  : all bonus clean fclean re
