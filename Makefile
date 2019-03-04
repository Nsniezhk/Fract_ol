# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsniezhk <nsniezhk@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/08 17:11:21 by nsniezhk          #+#    #+#              #
#    Updated: 2018/10/08 17:11:24 by nsniezhk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = "fract'ol"

SRC	=	main.c fractal_init.c fractal_sets.c control.c visual.c\

CC = gcc
CFLAGS	=	-Wall	-Wextra	-Werror

OBJ 	= $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
.SILENT:

SRC_DIR	=	./src/
INC_DIR	=	./include/
OBJ_DIR	=	./obj/

MLX = ./MiniLibx/
MLX_LIB	= $(addprefix $(MLX), mlx.a)
MLX_INC	=	-I ./MiniLibx
MLX_LNK	=	-L ./MiniLibx -l mlx -framework OpenGL -framework AppKit

FT	=	./libft
LIB_FT	= $(addprefix $(FT), libft.a)
LIB_INC	=	-I ./libft/
PRINTF	= -I ./libft/ft_printf/header
LIB_LNK	=	-L ./libft -l ft

all: obj $(LIB_FT) $(MLX_LIB) $(NAME)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(MLX_INC) $(PRINTF) $(LIB_INC) -I $(INC_DIR) -o $@ -c $<

$(LIB_FT):
	make -C $(FT)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "LibFT created"

$(MLX_LIB):
	make -C $(MLX)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "MiniLibx created"

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) $(LIB_LNK) -lm -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Fract'ol compilation completed"

clean:
	rm -rf $(OBJ_DIR)
	make -C $(FT) clean
	make -C $(MLX) clean
	printf '\0\x1b[36m[ ✔ ] %s\n\033[0m' "Cleaned"

fclean: clean
	rm -rf $(NAME)
	make -C $(FT) fclean
	printf '\0\x1b[36m[ ✔ ] %s\n\033[0m' "All binary files is deleted!"

re: fclean all