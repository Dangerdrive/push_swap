/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_stack_a.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:12:18 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/06 12:57:15 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Assigns optimal target nodes in stack 'b' for each node in stack 'a'.
 *
 * For every node in stack 'a', this function finds the closest higher value
 * node in stack 'b' to set as its target. If no such node exists in 'b', the
 * highest value node in 'b' is assigned as the target. This aims to optimize
 * the push and rotate operations by pre-calculating the most efficient target
 * positions for nodes in 'a' to be moved to 'b'.
 *
 * @param a Pointer to the top node of stack 'a'.
 * @param b Pointer to the top node of stack 'b'.
 */
static void	set_targets_for_a(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_node_b;
	t_stack_node	*optimal_target;
	long			optimal_value;

	while (a)
	{
		optimal_value = LONG_MIN;
		current_node_b = b;
		while (current_node_b)
		{
			if (current_node_b->value < a->value
				&& current_node_b->value > optimal_value)
			{
				optimal_value = current_node_b->value;
				optimal_target = current_node_b;
			}
			current_node_b = current_node_b->next;
		}
		if (optimal_value == LONG_MIN)
			a->target_node = get_max_value_node(b);
		else
			a->target_node = optimal_target;
		a = a->next;
	}
}

/**
 * Calculates move costs for nodes in stack 'a'.
 *
 * For each node in stack 'a', it calculates the total moves needed for
 * optimal positioning. This considers the node's current position, target
 * position in stack 'b', and whether it's above the median. The goal is
 * efficient repositioning to minimize 'total_moves'.
 *
 * @param a Pointer to stack 'a's top node.
 * @param b Pointer to stack 'b's top node for target positions.
 */
static void	calculate_moves_for_a(t_stack_node *a, t_stack_node *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->total_moves = a->position;
		if (!(a->is_above_median))
			a->total_moves = len_a - (a->position);
		if (a->target_node->is_above_median)
			a->total_moves += a->target_node->position;
		else
			a->total_moves += len_b - (a->target_node->position);
		a = a->next;
	}
}

/**
 * Identifies and marks the node with the minimum total moves as optimal move.
 *
 * Iterates through the stack to find the node with the least number of total
 * moves required to reach its designated position, marking it as the optimal
 * move for an operation. This function helps in optimizing stack operations
 * by identifying the most efficient move at the current state of the stack.
 *
 * @param stack Pointer to the top node of the stack to be evaluated.
 */
void	set_optimal_move(t_stack_node *stack)
{
	long			min_moves;
	t_stack_node	*optimal_node;

	if (!stack)
		return ;
	min_moves = LONG_MAX;
	while (stack)
	{
		if (stack->total_moves < min_moves)
		{
			min_moves = stack->total_moves;
			optimal_node = stack;
		}
		stack = stack->next;
	}
	optimal_node->is_optimal_move = true;
}

/**
 * Initializes and prepares nodes in stack 'a' for sorting operations.
 *
 * This function performs a series of initializations and analyses on stack 'a'
 * to facilitate efficient sorting. It assigns positional indexes to nodes in
 * both stacks 'a' and 'b', identifies target nodes in stack 'a' based on their
 * relationship with nodes in stack 'b', performs a cost analysis to determine
 * the optimal moves for sorting, and finally marks the node in stack 'a' that
 * represents the most efficient move as the optimal move.
 *
 * @param a Pointer to the top node of stack 'a'.
 * @param b Pointer to the top node of stack 'b'.
 */
void	prepare_stack_a(t_stack_node *a, t_stack_node *b)
{
	set_positions(a);
	set_positions(b);
	set_targets_for_a(a, b);
	calculate_moves_for_a(a, b);
	set_optimal_move(a);
}
