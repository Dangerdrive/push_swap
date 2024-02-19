#NAME		:=  pipex
#CC		  :=  cc
#CFLAGS	  :=  -Wextra -Wall -Werror -Wunreachable-code -Iinclude
#
#LEAKS	   :=  valgrind --leak-check=full --show-leak-kinds=all
#SRCS		:=  $(wildcard ./*.c)
#TEST_SRCS   :=  $(wildcard ./test/*.cpp) # assuming your test files are in ./test/
#OBJDIR	  :=  obj
#OBJS		:=  $(SRCS:%.c=$(OBJDIR)/%.o)
#TEST_OBJS   :=  $(TEST_SRCS:%.cpp=$(OBJDIR)/%.o)
#
#.PHONY: all clean fclean re valgrind test
#
#LIBFT_PATH  :=  ./libft
#LIBFT	   :=  $(LIBFT_PATH)/libft.a
#
#GTEST_DIR   :=  /path/to/gtest
#GTEST_FLAGS :=  -I$(GTEST_DIR)/include -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread
#
#all: $(NAME)
#
#$(NAME): $(LIBFT) $(OBJS)
#	@$(CC) $(OBJS) -o $(NAME) $(LIBFT)
#
#$(LIBFT):
#	@$(MAKE) -C $(LIBFT_PATH) all
#
#$(OBJDIR)/%.o: %.c | $(OBJDIR)
#	@$(CC) $(CFLAGS) -c $< -o $@
#
#$(OBJDIR):
#	@mkdir -p $(OBJDIR)
#
#clean:
#	@$(MAKE) -C $(LIBFT_PATH) clean
#	@rm -rf $(OBJDIR)
#
#fclean: clean
#	@$(MAKE) -C $(LIBFT_PATH) fclean
#	@rm -rf $(NAME)
#
#re: fclean all
#
## Test rule
#test: $(TEST_OBJS) $(OBJS)
#	@$(CC) $(TEST_OBJS) $(OBJS) $(GTEST_FLAGS) -o runTests
#	@./runTests
#
#$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
#	@$(CC) $(CFLAGS) $(GTEST_FLAGS) -c $< -o $@
#
#valgrind: $(NAME)
#	@$(LEAKS) ./$(NAME)

NAME        := pipex
CC          := cc
CFLAGS      := -Wextra -Wall -Werror -Iincludes

LEAKS       := valgrind --leak-check=full --show-leak-kinds=all
SRCS        := $(wildcard src/*.c)
TEST_SRCS   := $(wildcard test/*.cpp) # assuming your test files are in ./test/
OBJDIR      := obj
OBJS        := $(SRCS:src/%.c=$(OBJDIR)/%.o)
TEST_OBJS   := $(TEST_SRCS:test/%.cpp=$(OBJDIR)/%.o)

.PHONY: all clean fclean re valgrind test

GTEST_DIR   := /path/to/gtest # Make sure this is the correct path to your Google Test installation
GTEST_FLAGS := -I$(GTEST_DIR)/include -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

# Test rule
test: CFLAGS += $(GTEST_FLAGS)
test: $(TEST_OBJS) $(OBJS)
	@$(CC) $(TEST_OBJS) $(OBJS) -o runTests
	@./runTests

$(OBJDIR)/%.o: test/%.cpp | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

valgrind: $(NAME)
	@$(LEAKS) ./$(NAME)
