# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/06 16:03:51 by tforster          #+#    #+#              #
#    Updated: 2024/03/01 19:00:05 by tforster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[0;31m
GRN = \033[0;32m
YLW = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYA = \033[0;36m
WHT = \033[0;37m
RST = \033[0m

NAME	=	gnl.a

SRC		=	get_next_line.c get_next_line_utils.c \

BONUS	=	get_next_line_bonus.c get_next_line_utils_bonus.c \

OBJDIR	=	obj
OBJ		=	${SRC:%.c=$(OBJDIR)/%.o}
OBJ_BNS	=	$(SRC_BONUS:%.c=$(OBJDIR)/%.o)

CC = cc
CFLGS = -Wall -Wextra -Werror

ifdef WITH_BONUS
	OBJ += $(OBJ_BNS)
endif

all: $(NAME)

$(NAME): $(OBJ)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLGS) $(INCLS) -c $< -o $@
	@echo "${GRN}GNL => Object $@ DONE${RST}"
	ar rc $(NAME) $@
	@echo "${YLW}GNL => Object $@ ADDED to $(NAME) ${RST}"

bonus:
	@$(MAKE) WITH_BONUS=TRUE --no-print-directory

clean:
	rm -rf $(OBJDIR)
	@echo "${RED}CLEAN Objects $(OBJ) DELETED${RST}"

fclean: clean
	rm -rf $(NAME)
	@echo "${RED}FCLEAN Objects $(NAME) DELETED${RST}"

re: fclean all

.PHONY: all bonus clean fclean re
