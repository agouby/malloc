# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agouby <agouby@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/07 09:20:23 by agouby            #+#    #+#              #
#    Updated: 2018/03/09 21:10:22 by agouby           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_$(HOSTTYPE).so
NAME_LINK	= libft_malloc.so

FLAGS	= -Wall -Werror -Wextra
CC		= gcc

OBJ_FOLDER	= ./builds/
SRC_FOLDER	= ./srcs/
SRCS_FILES	= align.c \
			  malloc.c  \
			  page.c \
			  chunk.c \
			  show_alloc_mem.c \
			  free.c \
			  realloc.c

SRCS		= $(addprefix $(SRC_FOLDER), $(SRCS_FILES))
OBJS		= $(addprefix $(OBJ_FOLDER), $(SRCS_FILES:.c=.o))

INC_PATH	= ./includes/
INCLUDES	= -I$(INC_PATH)
INC_FILES	= malloc.h \
			  sizes.h
INCS		= $(addprefix $(INC_PATH), $(INC_FILES))

all: $(NAME) $(NAME_LINK)

.SILENT:

$(NAME): $(OBJ_FOLDER) $(OBJS)
	@gcc -shared -o $(NAME) $(OBJS)
	@printf "\e[96m$(NAME)\e[92m successfully created\n\e[0m"

$(NAME_LINK):
	@rm -f $(NAME_LINK)
	@ln -s $(NAME) $(NAME_LINK)
	@printf "\e[96m$(NAME)\e[92m successfully linked as \e[35m$(NAME_LINK)\n\e[0m"
	@gcc main.c -I./includes libft_malloc.so

$(OBJ_FOLDER):
	@mkdir -p $(OBJ_FOLDER)

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c $(INCS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@ -fPIC

clean:
	@rm -rf $(OBJ_FOLDER)
	@printf "\e[91m$(OBJ_FOLDER) successfully deleted\n\e[0m"

fclean: clean
	@rm -f $(NAME)
	@printf "\e[91m$(NAME) successfully deleted\n\e[0m"
	@rm -f $(NAME_LINK)
	@printf "\e[91m$(NAME_LINK) successfully deleted\n\e[0m"

re: fclean all

.PHONY: all clean fclean re
