# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/23 20:42:23 by seong-ki          #+#    #+#              #
#    Updated: 2024/07/24 22:19:51 by seong-ki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo

SRCS		=		philo.c	\
					ft_atoi.c	\
					ft_init.c	\
					ft_thread_mutex_utils.c	\

OBJS		=		$(SRCS:.c=.o)

CC			=		cc
CFLAGS		=		-Wall -Werror -Wextra

RM			=		rm -f
# =============================================================================#

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean	\
				all

.PHONY :	all	\
			clean	\
			fclean	\
			re
