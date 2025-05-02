# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/01 22:51:34 by lsilva-x          #+#    #+#              #
#    Updated: 2025/05/01 23:14:31 by lsilva-x         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gc
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = ./src
DEBUG_DIR = ./debug
OBJECT_DIR = ./object

SRC_FILES	= $(SRC_DIR)/gc_utils.c \
			$(SRC_DIR)/gc.c
			
DEBUG_FILE	= $(DEBUG_DIR)/gc_debug.c

SRCS	= $(SRC_FILES) \
		$(DEBUG_FILE)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	mkdir -p lib
	$(AR) ./lib/lib$(NAME).a $(addprefix $(OBJECT_DIR)/, $(notdir $(OBJS)))

%.o: %.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	mv $@ $(OBJECT_DIR)

clean:
	rm -rf $(OBJECT_DIR)/*.o

fclean: clean
	rm -rf lib
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re