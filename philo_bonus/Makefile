# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 17:42:05 by aouichou          #+#    #+#              #
#    Updated: 2022/12/02 18:44:01 by aouichou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo_bonus

SRC_D		= srcs/
OBJ_D		= objs/
INC_D		= include/

SRC			= main.c	\
			init.c		\
			libft.c		\
			philo.c		\
			tools.c		\
			free.c

OBJ			= $(addprefix $(OBJ_D), $(SRC:.c=.o))
FLAGS		= -g -Wall -Werror -Wextra -pthread #-fsanitize=address
INCS		= -I $(INC_D)

all: $(OBJ_D) $(NAME)

$(OBJ_D):
	@mkdir -p $@

$(NAME): $(OBJ)
	gcc $(FLAGS) $^ -o $@ $(INCLUDE)

$(OBJ_D)%.o: $(SRC_D)%.c
	gcc $(FLAGS) -o $@ -c $< $(INCS)

clean:
	rm -rf $(OBJ_D)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all bonus
