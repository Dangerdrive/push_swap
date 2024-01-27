//
// Created by fde-alen on 1/25/24.
//
#include <gtest/gtest.h>

void SetUp() override {
// Initialize the stack with some nodes
// Assuming 'push' adds a new node to the stack
t_stack_node node1 = {1, 0, 0, 0, false, false, nullptr, nullptr, nullptr};
t_stack_node node2 = {2, 0, 0, 0, false, false, nullptr, nullptr, nullptr};
a.push(node1);
a.push(node2);
}

void TearDown() override {
// Clean up the stack after each test
// Assuming 'clear' removes all nodes from the stack
a.clear();
}
};