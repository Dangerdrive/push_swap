#suppress directory messages
MAKEFLAGS	+=	--no-print-directory

CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall -Ilibft -Ift_printf
NAME		=	push_swap
BONUS		=	checker

SRC_PATH	=	src/
OBJ_PATH	=	src/obj/

LIBFT_PATH	=	./libs/libft
LIBFT		=	$(LIBFT_PATH)/libft.a

FTPRINTF_PATH	= ./libs/ft_printf
FTPRINTF		=	$(FTPRINTF_PATH)/libftprintf.a

INC			=	-I ./includes/ -I $(LIBFT_PATH)/ -I $(FTPRINTF_PATH)/

# Split SRC into SRC_COMMON and SRC_MAIN
SRC_COMMON	=	exit_and_free.c \
				populate_stack_a.c \
				prepare_stack_a.c \
				prepare_stack_b.c \
				push.c \
				reverse_rotate.c \
				rotate.c \
				sort.c \
				sort_utils.c \
				stack_utils.c \
				swap.c
SRC_MAIN	=	push_swap.c
BONUS_SRC	=	checker/checker.c

# Formatting
BOLD		=	\033[1m
NO_FORMAT	=	\033[0m

SRCS_COMMON	=	$(addprefix $(SRC_PATH), $(SRC_COMMON))
SRCS_MAIN	=	$(addprefix $(SRC_PATH), $(SRC_MAIN))
BONUS_SRCS	=	$(addprefix $(SRC_PATH), $(BONUS_SRC))

OBJS_COMMON	=	$(SRC_COMMON:.c=.o)
OBJS_MAIN	=	$(SRC_MAIN:.c=.o)
BONUS_OBJS	=	$(BONUS_SRC:.c=.o)

OBJS_COMMON_PATH	=	$(addprefix $(OBJ_PATH), $(OBJS_COMMON))
OBJS_MAIN_PATH	=	$(addprefix $(OBJ_PATH), $(OBJS_MAIN))
BONUS_OBJS_PATH	=	$(addprefix $(OBJ_PATH), $(BONUS_OBJS))

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)checker
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@echo "$(BOLD)✔️	Compiling $<...$(NO_FORMAT)"

all: $(NAME)

$(NAME): $(OBJS_COMMON_PATH) $(OBJS_MAIN_PATH) $(LIBFT) $(FTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS_COMMON_PATH) $(OBJS_MAIN_PATH) -o $@ -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
	@echo "\n✅	$(BOLD)Push_swap compiled$(NO_FORMAT)"

bonus: $(OBJS_COMMON_PATH) $(BONUS_OBJS_PATH) $(LIBFT) $(FTPRINTF)
	@$(CC) $(CFLAGS) $(OBJS_COMMON_PATH) $(BONUS_OBJS_PATH) -o $(BONUS) $(INC) -L$(FTPRINTF_PATH) -lftprintf -L$(LIBFT_PATH) -lft
	@echo "\n✅	$(BOLD)Checker compiled$(NO_FORMAT)"

$(LIBFT):
	@make -C $(LIBFT_PATH) all
	@echo "\n✔️	$(BOLD)Libft compiled...$(NO_FORMAT)"

$(FTPRINTF):
	@make -C $(FTPRINTF_PATH) all
	@echo "\n✔️	$(BOLD)ft_printf compiled...$(NO_FORMAT)"

clean:
	@echo ""
	@make -C $(LIBFT_PATH) clean
	@make -C $(FTPRINTF_PATH) clean
	@rm -rf $(OBJ_PATH)
	@echo "🗑️	$(BOLD)Object files removed$(NO_FORMAT)"

fclean: clean
	@echo ""
	@make -C $(LIBFT_PATH) fclean
	@make -C $(FTPRINTF_PATH) fclean
	@rm -f $(NAME) $(BONUS)
	@echo "🗑️	$(BOLD)Push_swap and Checker removed$(NO_FORMAT)"

re: fclean all

test:
	cd tester/ && ./test

.PHONY: all re clean fclean bonus # test
