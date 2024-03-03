#include "../unity/src/unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to run push_swap and return its output
char* run_push_swap(char* input) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "echo \"%s\" | ../../push_swap", input);
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return NULL;

    char* result = malloc(1024);
    fgets(result, 1024, pipe);
    pclose(pipe);

    return result;
}

// Test to check push_swap with non-numeric input
void test_push_swap_non_numeric_input(void) {
    char* input = "a b c";
    char* output = run_push_swap(input);
    TEST_ASSERT_NOT_NULL(output);
    TEST_ASSERT_EQUAL_STRING("Error\n", output);
    free(output);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_push_swap_non_numeric_input);
    return UNITY_END();
}