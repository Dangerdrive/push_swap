NAME        :=  pipex
CC          :=  cc
CFLAGS      :=  -Wextra -Wall -Werror -Wunreachable-code -Iinclude

LEAKS       :=  valgrind --leak-check=full --show-leak-kinds=all
SRCS        :=  $(wildcard ./*.c)
TEST_SRCS   :=  $(wildcard ./test/*.cpp) # assuming your test files are in ./test/
OBJDIR      :=  obj
OBJS        :=  $(SRCS:%.c=$(OBJDIR)/%.o)
TEST_OBJS   :=  $(TEST_SRCS:%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean fclean re valgrind test

LIBFT_PATH  :=  ./libft
LIBFT       :=  $(LIBFT_PATH)/libft.a

GTEST_DIR   :=  /path/to/gtest
GTEST_FLAGS :=  -I$(GTEST_DIR)/include -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
    @$(CC) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT):
    @$(MAKE) -C $(LIBFT_PATH) all

$(OBJDIR)/%.o: %.c | $(OBJDIR)
    @$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
    @mkdir -p $(OBJDIR)

clean:
    @$(MAKE) -C $(LIBFT_PATH) clean
    @rm -rf $(OBJDIR)

fclean: clean
    @$(MAKE) -C $(LIBFT_PATH) fclean
    @rm -rf $(NAME)

re: fclean all

# Test rule
test: $(TEST_OBJS) $(OBJS)
    @$(CC) $(TEST_OBJS) $(OBJS) $(GTEST_FLAGS) -o runTests
    @./runTests

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
    @$(CC) $(CFLAGS) $(GTEST_FLAGS) -c $< -o $@

valgrind: $(NAME)
    @$(LEAKS) ./$(NAME)