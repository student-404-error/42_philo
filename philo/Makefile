# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/23 20:42:23 by seong-ki          #+#    #+#              #
#    Updated: 2024/07/23 20:43:42 by seong-ki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		philo

SRC			=		philo.c

OBJ			=		$(SRC:.c=.o)

CC			=		cc
CFLAGS		=		-Wall -Werror -Wextra

RM			=		rm -f
# =============================================================================#

all			:	$(NAME)

$(NAME)		:	$(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

clean		:
				$(RM) $(OBJ)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean	\
				all

.PHONY :	all	\
			clean	\
			fclean	\
			re
