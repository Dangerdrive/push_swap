//
// Created by fde-alen on 1/25/24.
//
//#include <gtest/gtest.h>
//
//void SetUp() override {
//// Initialize the stack with some nodes
//// Assuming 'push' adds a new node to the stack
//t_stack_node node1 = {1, 0, 0, 0, false, false, nullptr, nullptr, nullptr};
//t_stack_node node2 = {2, 0, 0, 0, false, false, nullptr, nullptr, nullptr};
//a.push(node1);
//a.push(node2);
//}
//
//void TearDown() override {
//// Clean up the stack after each test
//// Assuming 'clear' removes all nodes from the stack
//a.clear();
//}
//};

#include <gtest/gtest.h>
#include "../includes/push_swap.h" // Assume this header defines t_stack_node and createNode

// Describes the feature being tested
class NodeCreationTest : public ::testing::Test {
protected:
// Set up any required variables or state here
void SetUp() override {
}

// Clean up after tests run
void TearDown() override {
}
};

// Describes the scenario and expected behavior
TEST_F(NodeCreationTest, CreateNode_WithGivenValue_ShouldAllocateAndInitializeNode) {
// Given: A value for the node
int nodeValue = 42;

// When: A node is created with the given value
t_stack_node* node = create_node(nodeValue);

// Then: The node should be correctly allocated and initialized
ASSERT_NE(nullptr, node) << "Node should not be null";
EXPECT_EQ(nodeValue, node->value) << "Node value should be initialized to given value";
EXPECT_EQ(nullptr, node->next) << "Next pointer should be initialized to nullptr";
EXPECT_EQ(nullptr, node->prev) << "Prev pointer should be initialized to nullptr";

// Cleanup
free(node);
}