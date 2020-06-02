# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bleplat <bleplat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/01 42:00:00 by bleplat           #+#    #+#              #
#    Updated: 2020/06/01 42:00:00 by bleplat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###########################
###   B I N A R I E S   ###
###########################

NAME_ASM        = asm
NAME_CW         = corewar


###########################
###  L I B R A R I E S  ###
###########################

LIBFT_DIR   = ./libft
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFTMO     = $(LIBFT_DIR)/libftmo.a


###########################
###    S O U R C E S    ###
###########################

SRC_FILES_COMMON	=	common/cw_champion.c \

SRC_FILES_ASM		=	asm/cw_asm_main.c \

SRC_FILES_CW		=	corewar/cw_main.c \

SRC_FILES = $(SRC_FILES_COMMON) $(SRC_FILES_ASM) $(SRC_FILES_CW)


###########################
###    F O L D E R S    ###
###########################

INCLUDES = includes
SRC_DIR  = srcs
OBJ_DIR  = .obj
DEP_DIR  = $(OBJ_DIR)

SRC_COMMON	= $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES_COMMON))
SRC_ASM		= $(SRC_COMMON) $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES_ASM))
SRC_CW		= $(SRC_COMMON) $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES_CW))
SRC = $(SRC_COMMON) $(SRC_ASM) $(SRC_CW)

OBJ_ASM = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC_FILES_ASM))
OBJ_CW = $(patsubst %, $(OBJ_DIR)/%.o, $(SRC_FILES_CW))
OBJ = $(OBJ_ASM) $(OBJ_CW)

DEP = $(patsubst %, $(DEP_DIR)/%.d, $(SRC_FILES))


###########################
###   C O M P I L E R   ###
###########################

CC = clang

DEFINES = _DARWIN_USE_64_BIT_INODE
CDEFINES = $(patsubst %, -D%, $(DEFINES))

CFLAGS = -Wall -Wextra -Werror
CFLAGS += $(CDEFINES)
CFLAGS += -I $(INCLUDES)
CFLAGS += -I $(LIBFT_DIR)/includes

LDFLAGS += -L $(LIBFT_DIR) -lft


###########################
### M A I N   R U L E S ###
###########################

.PHONY: all
all: $(NAME_ASM) $(NAME_CW)

$(NAME_ASM): $(LIBFT) $(OBJ_ASM)
	@printf "\e[92m" || true
	$(CC) $(CFLAGS) -o $@ $(OBJ_ASM) $(LDFLAGS)
	@printf "\e[0m" || true

$(NAME_CW): $(LIBFT) $(OBJ_CW)
	@printf "\e[92m" || true
	$(CC) $(CFLAGS) -o $@ $(OBJ_CW) $(LDFLAGS)
	@printf "\e[0m" || true

$(OBJ_DIR):
	@printf "\e[94m" || true
	mkdir -p $@
	mkdir -p $@/common
	mkdir -p $@/asm
	mkdir -p $@/corewar
	@printf "\e[0m" || true

$(OBJ_DIR)/%.o: $(SRC_DIR)/% | $(OBJ_DIR)
	@printf "\e[96m" || true
	$(CC) $(CFLAGS) -o $@ -c $<
	@printf "\e[0m" || true

$(LIBFT):
	@printf "\e[35m" || true
	make -C $(LIBFT_DIR) libft.a
	@printf "\e[0m" || true

.PHONY: clean
clean:
	@printf "\e[93m" || true
	rm -f $(OBJ)
	rm -f $(OBJ_DIR)/*.o
	rmdir $(OBJ_DIR) || true
	make -C $(LIBFT_DIR) $@
	@printf "\e[0m" || true

.PHONY: fclean
fclean: clean
	@printf "\e[91m" || true
	rm -f $(NAME)
	rm -f $(LIBFTMO)
	make -C $(LIBFT_DIR) $@
	@printf "\e[0m" || true

.PHONY: re
re: fclean all
	@printf "\e[0m" || true


###########################
### M O R E   R U L E S ###
###########################

.PHONY: update
update:
	@printf "\e[95m" || true
	git remote update
	git status -uno
	@printf "\e[0m" || true

.PHONY: upgrade
upgrade:
	@printf "\e[95m" || true
	git pull
	@printf "\e[0m" || true

.PHONY: debug
debug: LDFLAGS += -L. -lftmo -rdynamic -ldl
debug: $(LIBFTMO) all

.PHONY: optimized
optimized: CFLAGS += -o3
optimized: all

$(LIBFTMO):
	@printf "\e[35m" || true
	make -C $(LIBFT_DIR) libftmo.a
	@printf "\e[35m" || true
	#cp $(LIBFT_DIR)/libftmo.so $@
	@printf "\e[0m" || true


###########################
###  D O C   R U L E S  ###
###########################

.PHONY: geterror
geterror:
	@echo $?
	grep _ERROR_ includes/cw_errors.h

.PHONY: help
help:
	@printf "\e[0m" || true
	@printf "USAGE:\n" || true
	@printf "\t./asm CHAMPION.s\n" || true
	@printf "\t./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n" || true
	@printf "\e[91m" || true

