# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/29 23:07:53 by lfarias-          #+#    #+#              #
#    Updated: 2022/07/30 07:48:12 by lfarias-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = error_handler.c \
		file_handler.c \
		ft_split_quotes.c \
		ft_strtrim_quotes.c\
		path_builder.c \
		pipex.c \
		resource_cleaner.c
SRC_BONUS = error_handler_bonus.c \
			file_handler_bonus.c \
			ft_split_quotes_bonus.c \
			ft_strtrim_quotes_bonus.c \
			path_builder_bonus.c \
			pipex_bonus.c \
			resource_cleaner_bonus.c
LIBFT_DIR = ./libft/
GNL_DIR = ./get_next_line/

$(NAME):
	make -C $(LIBFT_DIR) libft.a
	$(CC) $(CFLAGS) -I. $(SRC) $(LIBFT_DIR)libft.a -o $(NAME)

all: $(NAME)

clean:
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT_DIR)libft.a

re: fclean all

bonus:
	make -C $(LIBFT_DIR) libft.a
	$(CC) -g $(CFLAGS) -I. $(SRC_BONUS) $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c $(LIBFT_DIR)libft.a -o $(NAME)

.PHONY:
	all clean fclean re bonus
