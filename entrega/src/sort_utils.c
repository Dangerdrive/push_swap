/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:39:15 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/29 12:49:31 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Checks if the stack is sorted in ascending order.
 *
 * Iterates through the stack, comparing each node's value to the value
 * of the next node. The stack is considered sorted if no node's value
 * is greater than the value of the node following it.
 *
 * @param stack Pointer to the top node of the stack to be checked.
 * @return True if the stack is sorted in ascending order, or if the stack
 *         is empty. Returns False if any node's value is greater than the
 *         value of the node following it.
 */
bool	is_stack_sorted(t_stack_node *stack)
{
	if (!stack)
		return (false);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

/**
 * Moves the top node from stack 'a' to 'b', optimizing for the next push.
 *
 * Transfers the top node from 'a' to 'b', updating nodes in both stacks for
 * the upcoming push operation. Manages stack rotation to optimize push
 * positioning.
 *
 * @param a Pointer to stack 'a''s top node, the push source.
 * @param b Pointer to stack 'b''s top node, the push destination.
 */
void	rotate_both(t_stack_node **a,
						t_stack_node **b,
						t_stack_node *cheapest_node)
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node)
		rr(a, b);
	set_positions(*a);
	set_positions(*b);
}

/**
 * Moves the top node from stack 'a' to 'b', updating for optimal push.
 *
 * Transfers the top node from 'a' to 'b', updating both stacks for the next
 * push. Manages reverse rotation of stacks to optimize push position.
 *
 * @param a Pointer to top node of stack 'a', source for the push.
 * @param b Pointer to top node of stack 'b', destination for the push.
 * @param cheapest_node Pointer to cheapest node in 'a' for the push.
 */
void	rev_rotate_both(t_stack_node **a,
								t_stack_node **b,
								t_stack_node *optimal_node)
{
	while (*b != optimal_node->target_node
		&& *a != optimal_node)
		rrr(a, b);
	set_positions(*a);
	set_positions(*b);
}

/**
 * Finds and returns the first node marked as optimal for a move.
 *
 * Iterates through the given stack to find the first node flagged as
 * an optimal move based on certain criteria. This function is useful
 * for identifying the most efficient action to take with the current
 * stack configuration.
 *
 * @param stack Pointer to the top of the stack to search through.
 * @return Pointer to the first node marked as an optimal move, or
 * NULL if no such node exists or the stack is empty.
 */
t_stack_node	*get_optimal_node(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack)
	{
		if (stack->is_optimal_move)
			return (stack);
		stack = stack->next;
	}
	return (NULL);
}

/**
 * Moves the smallest number in stack 'a' to the top and updates nodes for
 * optimal pushing.
 *
 * This function identifies and moves the smallest number in stack 'a' to the
 * top. It prepares nodes in stack 'a' for the next push operation by handling
 * rotation and reverse rotation to find the optimal position for pushing.
 *
 * @param a Pointer to the top node of stack 'a', the source stack for the
 * push operation.
 */
void	rotate_min_to_top(t_stack_node **a)
{
	while ((*a)->value != get_min_value_node(*a)->value)
	{
		if (get_min_value_node(*a)->is_above_median)
			ra(a);
		else
			rra(a);
	}
}
