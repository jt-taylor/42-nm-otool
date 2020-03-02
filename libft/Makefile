# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/21 17:04:25 by jtaylor           #+#    #+#              #
#    Updated: 2020/02/03 19:26:01 by jtaylor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -I includes -c

SRC = ./ft_atoi.c \
		ft_bzero.c \
		ft_freestrarr.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_putstrarr.c \
		ft_str_chr_rplc.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_uitoa_base.c \
		get_all_lines.c \
		get_next_line.c \
		ft_strsep.c \
		ft_strtok.c \
		ft_strcspn.c \
		ft_stronly_space.c \
		ft_strstart_w_str.c \

OBJ = $(SRC:%.c=%.o)

OBJD = $(SRC:%.c=%.o)

LIBHEADER = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@ar -rcs $(NAME) $(OBJ)
	@echo "\tBuilding libft.a"

$(OBJ): $(SRC)
	@gcc $(FLAGS) $(SRC)
	@echo "\tBuilding libft .o files"
	@make -C ./ft_printf

debug : $(SRC)
	@gcc -g3 $(FLAGS) $(SRC)
	@make -C ./ft_printf
	@ar -rcs $(NAME) $(OBJD)

fsan: $(SRC)
	@gcc -g3 -fsanitize=address $(FLAGS) $(SRC)
	@make -C ./ft_printf
	@ar -rcs $(NAME) $(OBJD)
	@echo "Building fsan libft"

clean:
	@rm -f $(OBJ)
	@make clean -C ./ft_printf
	@echo "\tRemoving Libft .o files"

fclean: clean
	@rm -f $(NAME)
	@echo "\tRemoving libft.a\n"
	@make fclean -C ./ft_printf

re: fclean all
