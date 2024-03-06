#suppress directory messages
MAKEFLAGS	+=	--no-print-directory

CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall -g -Ilibft -Ift_printf
NAME		=	push_swap
BONUS		=	checker

SRC_PATH	=	src/
OBJ_PATH	=	src/obj/

LIBFT_PATH	=	./libs/libft
LIBFT		=	$(LIBFT_PATH)/libft.a

FTPRINTF_PATH		= ./libs/ft_printf
FTPRINTF	=	$(FTPRINTF_PATH)/libftprintf.a

INC			=	-I ./includes/ -I $(LIBFT_PATH)/ -I $(FTPRINTF_PATH)/


SRC			=	populate_stack_a.c \
				prepare_stack_a.c \
				prepare_stack_b.c \
				push_swap.c \
				push.c \
				reverse_rotate.c \
				rotate.c \
				sort.c \
				sort_utils.c \
				stack_utils.c \
				swap.c
BONUS_SRC	=	checker/checker.c


# Formatting
BOLD		=	\033[1m
NO_FORMAT	=	\033[0m

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BONUS_SRCS	=	$(addprefix $(SRC_PATH), $(BONUS_SRC))
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))
BONUS_OBJ	=	$(BONUS_SRC:.c=.o)
BONUS_OBJS	=	$(addprefix $(OBJ_PATH), $(BONUS_OBJ))

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(BOLD)✔️	Compiling $<...$(NO_FORMAT)"

all:
	@echo ""
	@$(MAKE) $(NAME)

$(NAME):$(OBJS) $(LIBFT) $(FTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(BONUS_OBJS) -o $@ -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
	@echo "\n✅	$(BOLD)Push_swap compiled$(NO_FORMAT)"

# Add compilation for checker object file
$(OBJ_PATH)$(BONUS_OBJ): $(SRC_PATH)$(BONUS_SRC)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(BOLD)✔️ Compiling $<...$(NO_FORMAT)"

# Adjusted bonus target
bonus: $(BONUS_SRCS) $(LIBFT) $(FTPRINTF)
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(BONUS_SRCS) -o $(BONUS) $(INC) -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
	@echo "\n✅ $(BOLD)Checker compiled$(NO_FORMAT)"

$(LIBFT):
	@make -C $(LIBFT_PATH) all
	@echo "\n✔️	$(BOLD)Libft compiled...$(NO_FORMAT)"

$(FTPRINTF):
	@make -C $(FTPRINTF_PATH) all
	@echo	"\n✔️	$(BOLD)ft_printf compiled...$(NO_FORMAT)"

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


# #suppress directory messages
# MAKEFLAGS	+=	--no-print-directory

# CC			=	cc
# CFLAGS		=	-Werror -Wextra -Wall -g -Ilibft -Ift_printf
# NAME		=	push_swap
# BONUS		=	checker

# SRC_PATH	=	src/
# OBJ_PATH	=	src/obj/
# CHECKER_SRC	=	src/checker/checker.c

# LIBFT_PATH	=	./libs/libft
# LIBFT		=	$(LIBFT_PATH)/libft.a

# FTPRINTF_PATH		= ./libs/ft_printf
# FTPRINTF	=	$(FTPRINTF_PATH)/libftprintf.a

# INC			=	-I ./includes/ -I $(LIBFT_PATH)/ -I $(FTPRINTF_PATH)/


# SRC			=	populate_stack_a.c \
# 				prepare_stack_a.c \
# 				prepare_stack_b.c \
# 				push_swap.c \
# 				push.c \
# 				reverse_rotate.c \
# 				rotate.c \
# 				sort.c \
# 				sort_utils.c \
# 				stack_utils.c \
# 				swap.c

# # Formatting
# BOLD		=	\033[1m
# NO_FORMAT	=	\033[0m

# SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
# OBJ			=	$(SRC:.c=.o)
# OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

# $(OBJ_PATH)%.o:$(SRC_PATH)%.c
# 	@mkdir -p $(OBJ_PATH)
# 	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
# 	@echo "$(BOLD)✔️	Compiling $<...$(NO_FORMAT)"

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT) $(FTPRINTF)
# 	@$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
# 	@echo "\n✅	$(BOLD)Push_swap compiled$(NO_FORMAT)"

# $(BONUS):
# 	@$(CC) $(CFLAGS) $(CHECKER_SRC) -o $(BONUS) $(INC) -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
# 	@echo "\n✅	$(BOLD)Checker compiled$(NO_FORMAT)"

# bonus: $(BONUS)

# $(LIBFT):
# 	@make -C $(LIBFT_PATH) all
# 	@echo "\n✔️	$(BOLD)Libft compiled...$(NO_FORMAT)"

# $(FTPRINTF):
# 	@make -C $(FTPRINTF_PATH) all
# 	@echo	"\n✔️	$(BOLD)ft_printf compiled...$(NO_FORMAT)"

# clean:
# 	@echo ""
# 	@make -C $(LIBFT_PATH) clean
# 	@make -C $(FTPRINTF_PATH) clean
# 	@rm -rf $(OBJ_PATH)
# 	@echo		"🗑️	$(BOLD)Object files removed$(NO_FORMAT)"

# fclean: clean
# 	@echo ""
# 	@make -C $(LIBFT_PATH) fclean
# 	@make -C $(FTPRINTF_PATH) fclean
# 	@rm -f $(NAME) $(BONUS)
# 	@echo		"🗑️	$(BOLD)Push_swap and Checker removed$(NO_FORMAT)"

# re: fclean all

# test:
# 	cd tester/ && ./test

# .PHONY: all re clean fclean bonus test
