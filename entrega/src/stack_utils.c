/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:13:01 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/18 15:52:01 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Calculates the length of a stack.
 *
 * Iterates through the stack, incrementing a counter for each node encountered
 * until it reaches the end of the stack. This function is useful for 
 * determining the size of the stack, which can be essential for operations 
 * that depend on the stack's current state.
 *
 * @param stack Pointer to the top node of the stack.
 * @return The total number of nodes in the stack, or 0 if the stack is empty.
 */
int	stack_len(t_stack_node *first_node)
{
	int	len;

	if (!first_node)
		return (-1);
	len = 0;
	while (first_node)
	{
		first_node = first_node->next;
		len++;
	}
	return (len);
}

/**
 * Finds and returns the last node in a stack.
 *
 * Traverses the stack from the top node to the end, returning the last node
 * in the sequence. If the stack is empty, returns NULL.
 *
 * @param stack Pointer to the top node of the stack to be traversed.
 * @return Pointer to the last node in the stack, or NULL if stack is empty.
 */
t_stack_node	*find_last(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

/**
 * Identifies and returns the node with the minimum value in a stack.
 *
 * Begins with the assumption that the minimum value is the largest possible
 * long value. Iterates through the stack, updating the minimum value and
 * corresponding node as it finds lower values.
 *
 * @param stack Pointer to the first node of the stack to search through.
 * @return Pointer to the node with the minimum value; NULL if the stack is
 *         empty.
 */
t_stack_node	*get_min_value_node(t_stack_node *stack)
{
	long			min;
	t_stack_node	*min_node;

	if (!stack)
		return (NULL);
	min = LONG_MAX;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

/**
 * Finds and returns the node with the maximum value in a stack.
 *
 * Iterates through the stack to identify the node with the highest value.
 * Initializes the maximum value as the smallest possible long to ensure
 * any stack value is larger. Updates the max value and max node pointer
 * as it traverses the stack.
 *
 * @param stack The starting node of the stack to search.
 * @return Pointer to the node with the maximum value, or NULL if the
 * stack is empty.
 */
t_stack_node	*get_max_value_node(t_stack_node *stack)
{
	long			max;
	t_stack_node	*max_node;

	if (!stack)
		return (NULL);
	max = LONG_MIN;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

/**
 * Assigns the current position to each node in the stack and marks if it is
 * above the median position.
 *
 * Iterates through the stack, assigning each node an index starting from 0 and
 * determining if it is positioned above or below the median of the stack's
 * length. This classification aids in optimizing operations that depend on
 * the node's position relative to the stack's median.
 *
 * @param stack Pointer to the top node of the stack to be indexed.
 */
void	set_positions(t_stack_node *first_node)
{
	int	i;
	int	median;

	i = 0;
	if (!first_node)
		return ;
	median = stack_len(first_node) / 2;
	while (first_node)
	{
		first_node->position = i;
		if (i <= median)
			first_node->is_above_median = true;
		else
			first_node->is_above_median = false;
		first_node = first_node->next;
		++i;
	}
}
