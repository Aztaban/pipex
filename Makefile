# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 00:43:12 by mjusta            #+#    #+#              #
#    Updated: 2025/08/20 14:15:03 by mjusta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_DIR = src
BONUS_DIR = src_bonus
OBJ_DIR = build
INC_DIR = include
LIBFT_DIR = libft

SRC = \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/helpers.c \
		$(SRC_DIR)/process.c \
		$(SRC_DIR)/pathfinder.c \

BONUS_SRC = \
		$(BONUS_DIR)/main_bonus.c \
		$(BONUS_DIR)/helpers_bonus.c \
		$(BONUS_DIR)/process_bonus.c \
		$(BONUS_DIR)/pathfinder_bonus.c \

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)/include

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(BONUS_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)
	@test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d -empty -delete || true
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) infile "grep 42" "cat" outfile

.PHONY: all clean fclean bonus re valgrind norminette
