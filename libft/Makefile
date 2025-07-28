# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 11:21:19 by mjusta            #+#    #+#              #
#    Updated: 2025/07/28 19:56:01 by mjusta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
AR = ar rcs
# r = Replace or insert .o files into archive (if it doesn't exist, create it)
# c = Don't warn if the archive had to be created
# s = Create an archive index (time saving)

INC_DIR = include
SRC_DIR = src
OBJ_DIR = build

SRC = \
		src/char/ft_isalnum.c \
		src/char/ft_isalpha.c \
		src/char/ft_isascii.c \
		src/char/ft_isdigit.c \
		src/char/ft_isprint.c \
		src/conversion/ft_atoi.c \
		src/conversion/ft_itoa.c \
		src/conversion/ft_tolower.c \
		src/conversion/ft_toupper.c \
		src/memory/ft_bzero.c \
		src/memory/ft_calloc.c \
		src/memory/ft_memchr.c \
		src/memory/ft_memcmp.c \
		src/memory/ft_memcpy.c \
		src/memory/ft_memmove.c \
		src/memory/ft_memset.c \
		src/string/ft_strchr.c \
		src/string/ft_strdup.c \
		src/string/ft_strlcpy.c \
		src/string/ft_strlcat.c \
		src/string/ft_strlen.c \
		src/string/ft_strncmp.c \
		src/string/ft_strnstr.c \
		src/string/ft_strrchr.c \
		src/string/ft_split.c \
		src/string/ft_striteri.c \
		src/string/ft_strjoin.c \
		src/string/ft_strmapi.c \
		src/string/ft_strtrim.c \
		src/string/ft_substr.c \
		src/output/ft_putchar_fd.c \
		src/output/ft_putstr_fd.c \
		src/output/ft_putendl_fd.c \
		src/output/ft_putnbr_fd.c \
		src/list/ft_lstnew.c \
		src/list/ft_lstadd_front.c \
		src/list/ft_lstsize.c \
		src/list/ft_lstlast.c \
		src/list/ft_lstadd_back.c \
		src/list/ft_lstdelone.c \
		src/list/ft_lstclear.c \
		src/list/ft_lstiter.c \
		src/list/ft_lstmap.c \
		src/printf/ft_printf.c \
		src/printf/ft_printf_utils.c \
		src/gnl/get_next_line.c \
		src/gnl/get_next_line_utils.c \
		src/cleanup/cleanup.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@test -d $(OBJ_DIR) && find $(OBJ_DIR) -type d -empty -delete || true

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

