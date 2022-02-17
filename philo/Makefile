# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 02:21:09 by gucamuze          #+#    #+#              #
#    Updated: 2022/02/17 02:56:26 by gucamuze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


EXEC_NAME		=	philo
CC				=	clang -Wall -Wextra -Werror
RM				=	rm -f

SRCS_PATH		=	./srcs/
					
SRC_FILES		=	${SRCS_PATH}main.c \
					${SRCS_PATH}my_atoi.c\
					${SRCS_PATH}setup.c \
					${SRCS_PATH}threads.c \
					${SRCS_PATH}monitoring.c
					
SRC_OFILES		= 	$(SRC_FILES:.c=.o)

%.o: %.c
				$(CC) -Iincludes -c $< -o $@

all:			$(EXEC_NAME)

$(EXEC_NAME):	$(SRC_OFILES)
				$(CC) $(SRC_OFILES) -Iincludes -lpthread -o $(EXEC_NAME)
							
clean:
				$(RM) $(SRC_OFILES)

fclean:		clean
				$(RM) ${EXEC_NAME}

re:			fclean all

norminette:
			norminette srcs libft includes

.PHONY:	all clean fclean re norminette

