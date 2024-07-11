# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/24 14:23:38 by tforster          #+#    #+#              #
#    Updated: 2024/07/11 15:06:45 by tforster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GRN		=	\033[0;32m
YLW		=	\033[0;33m
BLU		=	\033[0;34m
MAG		=	\033[0;35m
CYA		=	\033[0;36m
WHT		=	\033[0;37m
RST		=	\033[0m

NAME	=	fdf

FILES	=	fdf.c init_fc.c error_check.c \
			fdf_read.c array.c array_error.c \
			camera_build.c camera_utils.c projection.c \
			fdf_draw.c bresenham.c color.c \
			oprt_vector.c oprt_matrix.c oprt_tf.c oprt_rotate.c math_utils.c

BONUS	=	fdf_bonus.c init_fc_bonus.c error_check_bonus.c \
			keys_bonus.c keys_utils_bonus.c \
			fdf_read_bonus.c array_bonus.c array_error_bonus.c \
			array_colorh_bonus.c \
			camera_build_bonus.c camera_utils_bonus.c projection_bonus.c \
			fdf_draw_bonus.c bresenham_bonus.c color_bonus.c menu_bonus.c \
			oprt_vector_bonus.c oprt_matrix_bonus.c \
			oprt_tf_bonus.c oprt_rotate_bonus.c math_utils_bonus.c

SRCDIR	=	src
BNSDIR	=	src_bonus
SRC		=	$(FILES:%.c=$(SRCDIR)%.o)
SRCBNS =	$(FILES:%.c=$(BNSDIR)%.o)

OBJDIR	=	obj
OBJ		=	${FILES:%.c=$(OBJDIR)/%.o}
OBJ_BNS	=	$(BONUS:%.c=$(OBJDIR)/%.o)

CC		=	cc
CFLGS	=	-Wextra -Wall -Werror
MLXFLGS	=	-ldl -lglfw -pthread -lm

LIBFT	=	./libft
GNL		=	./gnl
LIBMLX	=	./MLX42

INCLUDE	=	-I ./include -I $(LIBFT) -I $(GNL) -I $(LIBMLX)/include
LIBS	=	$(LIBFT)/libft.a $(GNL)/gnl.a $(LIBMLX)/build/libmlx42.a

DEL		=	$(OBJ_BNS)

ifdef WITH_BONUS
	DEL		:=	$(OBJ)
	SRCDIR	:=	$(BNSDIR)
	OBJ		:=	$(OBJ_BNS)
endif

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	rm -rf $(DEL)
	$(CC) $(CFLGS) $(OBJ) $(LIBS) $(INCLUDE) $(MLXFLGS) -ldl -lglfw -pthread -lm -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLGS) $(INCLUDE) -c $< -o $@
	@echo "${GRN}Compile $@ DONE${RST}"

$(LIBS):
	@make -C $(LIBFT)
	@make -C $(GNL)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

bonus:
	@make WITH_BONUS=TRUE --no-print-directory

clean:
	@rm -rf $(OBJDIR)
	@echo "${RED}CLEAN:	Objects $(OBJ) DELETED${RST}"

fclean: clean
	@make fclean -sC $(LIBFT)
	@echo "${RED}CLEAN:	Lib $(LIBFT) DELETED${RST}"
	@make fclean -sC $(GNL)
	@echo "${RED}CLEAN:	Lib $(GNL) DELETED${RST}"
	@rm -rf $(LIBMLX)/build
	@echo "${RED}CLEAN:	Lib $(LIBMLX) DELETED${RST}"
	@rm -rf $(NAME)
	@echo "${RED}FCLEAN $(NAME) DELETED${RST}"

re: clean all

.PHONY: all, clean, fclean, re, libmlx
