/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:12:50 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/06 15:54:47 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Moves the top node from stack 'a' to 'b', optimizing nodes for pushing.
 *
 * This function transfers the top node from stack 'a' to 'b', updating nodes
 * in both stacks for the next push. It manages rotation and reverse rotation
 * in both stacks to optimize push positioning.
 *
 * @param a Pointer to the top node of stack 'a', source for the push.
 * @param b Pointer to the top node of stack 'b', destination for the push.
 */
static void	targets_to_top_and_push_to_b(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*optitmal_push_node;

	optitmal_push_node = get_optimal_node(*a);
	if (optitmal_push_node->is_above_median
		&& optitmal_push_node->target_node->is_above_median)
		rotate_both(a, b, optitmal_push_node);
	else if (!(optitmal_push_node->is_above_median)
		&& !(optitmal_push_node->target_node->is_above_median))
		rev_rotate_both(a, b, optitmal_push_node);
	rotate_until_target_top(a, optitmal_push_node, 'a');
	rotate_until_target_top(b, optitmal_push_node->target_node, 'b');
	pb(b, a);
}

/**
 * Rotates a stack until a specified target node is at the top.
 *
 * For stack 'a' or 'b', rotates or reverse rotates based on the target node's
 * position relative to the median. This optimizes the movement to place the
 * target node at the top of the stack with minimal operations.
 *
 * @param stack Pointer to the stack's top node.
 * @param target_node The node that needs to be moved to the top.
 * @param stack_name Identifier for the stack ('a' or 'b') being manipulated.
 */
void	rotate_until_target_top(t_stack_node **stack,
						t_stack_node *target_node, char stack_name)
{
	while (*stack != target_node)
	{
		if (stack_name == 'a')
		{
			if (target_node->is_above_median)
				ra(stack);
			else
				rra(stack);
		}
		else if (stack_name == 'b')
		{
			if (target_node->is_above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}

/**
 * Sorts a three elements stack using a specific sequence of operations.
 *
 * This function sorts a stack with three elements 
 * using a specific sequence of operations:
 * - If the first element is the largest, rotate the stack upwards. 
 * Ex.: 1 2 3 -> 2 3 1
 * - If the second element is the largest, reverse rotate the stack. 
 * Ex.: 1 3 2 -> 2 1 3
 * - If the first element is the smallest, swap the first two elements. 
 * Ex.: 3 2 1 -> 2 3 1
 * - If the second element is the smallest, rotate the stack. 
 * Ex.: 2 1 3 -> 1 3 2
 *
 * @param a Pointer to the top node of the stack to be sorted.
 */
void	sort_three_nodes(t_stack_node **a)
{
	t_stack_node	*biggest_node;

	biggest_node = get_max_value_node(*a);
	if (biggest_node == *a)
		ra(a);
	else if ((*a)->next == biggest_node)
		rra(a);
	if ((*a)->value > (*a)->next->value)
		sa(a);
}

/**
 * Sorts stacks 'a' using push, swap and rotate operations.
 *
 * Begins by pushing 2 elements from stack 'a' to 'b' if 'a' has more than
 * three unsorted elements. 
 * It then prepares a(set targets, calculate moves and set the optimal move).
 * When we have 3 elements in 'a' we sort them with sort_three_nodes.
 * 
 * After sorting three elements in 'a', it moves elements
 * from 'b' back to 'a', ensuring 'a' is sorted. Finally, it adjusts 'a'
 * to have the smallest element on top.
 *
 * @param a Pointer to the top node of stack 'a'.
 * @param b Pointer to the top node of stack 'b'.
 */
void	sort_stack_a(t_stack_node **a, t_stack_node **b)
{
	int	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !is_stack_sorted(*a))
		pb(b, a);
	if (len_a-- > 3 && !is_stack_sorted(*a))
		pb(b, a);
	while (len_a-- > 3 && !is_stack_sorted(*a))
	{
		prepare_stack_a(*a, *b);
		targets_to_top_and_push_to_b(a, b);
	}
	sort_three_nodes(a);
	while (*b)
	{
		prepare_stack_b(*a, *b);
		rotate_until_target_top(a, (*b)->target_node, 'a');
		pa(a, b);
	}
	set_positions(*a);
	rotate_min_to_top(a);
}
