# Tester Configuration
TESTER_NAME         = push_swap_tester
UNITY_SRC_DIR       = tester/unity/src
TESTS_DIR           = tester/tests
TESTS_OBJ_DIR       = tester/obj

# Compiler and Flags
CC                  = gcc
CFLAGS              = -Wall -Werror -Wextra -I$(UNITY_SRC_DIR) -Iinc

# Find all test .c files and corresponding .o files
TEST_SRC            = $(wildcard $(TESTS_DIR)/*.c)
TEST_OBJ            = $(patsubst $(TESTS_DIR)/%.c,$(TESTS_OBJ_DIR)/%.o,$(TEST_SRC))

# Unity Source Files
UNITY_SRC           = $(UNITY_SRC_DIR)/unity.c
UNITY_OBJ           = $(UNITY_SRC:.c=.o)

# Build Rules
all:                $(TESTER_NAME)

$(TESTER_NAME):     $(TEST_OBJ) $(UNITY_OBJ)
                    @$(CC) $(CFLAGS) $^ -o $@
                    @echo "Tester compiled successfully."

# Compile test object files
$(TESTS_OBJ_DIR)/%.o: $(TESTS_DIR)/%.c
                    @mkdir -p $(TESTS_OBJ_DIR)
                    @$(CC) $(CFLAGS) -c $< -o $@

# Compile Unity object file
$(UNITY_SRC_DIR)/%.o: $(UNITY_SRC_DIR)/%.c
                    @$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
                    @rm -rf $(TESTS_OBJ_DIR)
                    @rm -f $(UNITY_SRC_DIR)/*.o

fclean:             clean
                    @rm -f $(TESTER_NAME)

re:                 fclean all

# Run the tester after rebuilding
run:                re
                    @./$(TESTER_NAME)

# Phony Targets
.PHONY:             all clean fclean re run
