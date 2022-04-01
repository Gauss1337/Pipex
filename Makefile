# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 18:02:04 by ahakam            #+#    #+#              #
#    Updated: 2022/03/24 03:49:41 by ahakam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES =   ft_split.c ft_strdup.c ft_strjoin.c ft_strnstr.c pipex.c ft_strlen.c pipex_utils.c 

BFILES = pipex_bonus.c get_next_line.c get_next_line_utils.c ft_split_bonus.c ft_strnstr_bonus.c ft_strlen_bonus.c ft_strjoin_bonus.c ft_strdup_bonus.c pipex_utils_bonus.c ft_strcmp_bonus.c here_doc.c

NAME = pipex

BONUS = pipex_bonus

CC = gcc 

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra -g

all : $(NAME) 

$(NAME):
	$(CC) $(CFILES) -o $(NAME)
	
bonus : $(BONUS)

$(BONUS):
	$(CC) $(BFILES) -o $(BONUS) 
	
clean : 
			${RM} ${NAME} ${BONUS}
fclean : clean
re : fclean all bonus
