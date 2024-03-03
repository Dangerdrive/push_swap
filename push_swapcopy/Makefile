# # Standard
# NAME				= push_swap

# # Directories
# LIBFT				= ./libft/libft.a
# INC					= inc/
# SRC_DIR				= srcs/
# OBJ_DIR				= obj/

# # Compiler and CFlags
# CC					= gcc
# CFLAGS				= -Wall -Werror -Wextra -g -I
# RM					= rm -f

# # Source Files
# COMMANDS_DIR		=	$(SRC_DIR)/push_swap.c

# # Concatenate all source files
# SRCS 				= $(COMMANDS_DIR)

# # Apply the pattern substitution to each source file in SRC and produce a corresponding list of object files in the OBJ_DIR
# OBJ 				= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

# # Build rules
# start:
# 					@make all

# $(LIBFT):
# 					@make -C ./libft

# all: 				$(NAME)

# $(NAME): 			$(OBJ) $(LIBFT)
# 					@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME)

# # Compile object files from source files
# $(OBJ_DIR)%.o:		$(SRC_DIR)%.c
# 					@mkdir -p $(@D)
# 					@$(CC) $(CFLAGS) $(INC) -c $< -o $@

# clean:
# 					@$(RM) -r $(OBJ_DIR)
# 					@make clean -C ./libft

# fclean: 			clean
# 					@$(RM) $(NAME)
# 					@$(RM) $(LIBFT)

# re: 				fclean all

# test:
# 					cd tester && ./test

# # Phony targets represent actions not files
# .PHONY: 			start all clean fclean re test


#suppress directory messages
MAKEFLAGS	+=	--no-print-directory

CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall -g -Ilibft -Ift_printf
NAME		=	push_swap

SRC_PATH	=	src/
OBJ_PATH	=	src/obj/

LIBFT_PATH	=	./libs/libft
LIBFT		=	$(LIBFT_PATH)/libft.a

FTPRINTF_PATH		= ./libs/ft_printf
FTPRINTF	=	$(FTPRINTF_PATH)/libftprintf.a

INC			=	-I ./includes/ -I $(LIBFT_PATH)/ -I $(FTPRINTF_PATH)/


SRC			=	push_swap.c
#				file_handler.c \
				parse_envp.c \
				Push_swap_utils.c \
				Push_swap.c

# Formatting
BOLD		=	\033[1m
NO_FORMAT	=	\033[0m

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(BOLD)✔️	Compiling $<...$(NO_FORMAT)"

all:
	@echo ""
	@$(MAKE) $(NAME)

$(NAME):$(OBJS) $(LIBFT) $(FTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
	@echo "\n✅	$(BOLD)Push_swap compiled$(NO_FORMAT)"

$(LIBFT):
	@make -C $(LIBFT_PATH) all
	@echo "\n✔️	$(BOLD)Libft compiled...$(NO_FORMAT)"

$(FTPRINTF):
	@make -C $(FTPRINTF_PATH) all
	@echo	"\n✔️	$(BOLD)ft_printf compiled...$(NO_FORMAT)"

bonus: all

clean:
	@echo ""
	@make -C $(LIBFT_PATH) clean
	@make -C $(FTPRINTF_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo		"🗑️	$(BOLD)Object files removed$(NO_FORMAT)"

fclean: clean
	@echo ""
	@make -C $(LIBFT_PATH) fclean
	@make -C $(FTPRINTF_PATH) fclean
	@rm -f $(NAME)
	@echo		"🗑️	$(BOLD)Push_swap removed$(NO_FORMAT)"

re: fclean all

test:
	cd tester/ && ./test

.PHONY: all re clean fclean bonus test




#
