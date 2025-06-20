# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 22:51:34 by lsilva-x          #+#    #+#              #
#    Updated: 2025/06/20 16:42:08 by lsilva-x         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gc
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR     = src
DEBUG_DIR   = debug
OBJECT_DIR  = obj
BIN_DIR     = bin

NAME        = gc

SRC_FILES   = $(SRC_DIR)/gc_utils.c \
              $(SRC_DIR)/gc.c

DEBUG_FILE  = $(DEBUG_DIR)/gc_debug.c

SRCS        = $(SRC_FILES) $(DEBUG_FILE)
OBJS        = $(patsubst %.c,$(OBJECT_DIR)/%.o,$(SRCS))

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
AR          = ar rcs

all: $(BIN_DIR)/lib$(NAME).a

$(BIN_DIR)/lib$(NAME).a: $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(AR) $@ $^

$(OBJECT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECT_DIR)

fclean: clean
	rm -rf $(BIN_DIR)   # Alterado para BIN_DIR

re: fclean all

.PHONY: all clean fclean re
