# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 00:43:12 by mjusta            #+#    #+#              #
#    Updated: 2025/08/04 17:25:12 by mjusta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_DIR = src
INC_DIR = include
LIBFT_DIR = libft

SRC = $(SRC_DIR)/main.c \
			$(SRC_DIR)/helpers.c \
			$(SRC_DIR)/process.c \

BONUS_SRC = $(SRC_DIR)/main_bonus.c \
			$(SRC_DIR)/helpers_bonus.c \
			$(SRC_DIR)/process_bonus.c \

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/include

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) infile "grep 42" "wc -l" outfile

norminette:
	@norminette ./*.c ./*.h

.PHONY: all clean fclean bonus re norminette
