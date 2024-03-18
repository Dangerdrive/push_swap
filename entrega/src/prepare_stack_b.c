/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_stack_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:12:25 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/06 12:33:08 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Assigns optimal target nodes in stack 'a' for nodes in stack 'b'.
 *
 * For each node in stack 'b', this function finds the nearest greater value
 * in stack 'a' and designates it as the target. If a 'b' node's value exceeds
 * all in 'a', it targets 'a's minimum value node, facilitating effective
 * stack movements.
 *
 * @param a Source stack for target node identification.
 * @param b Stack undergoing target node assignment.
 */
static void	set_targets_for_b(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_node_a;
	t_stack_node	*optimal_target;
	long			optimal_value;

	while (b)
	{
		optimal_value = LONG_MAX;
		current_node_a = a;
		while (current_node_a)
		{
			if (current_node_a->value > b->value
				&& current_node_a->value < optimal_value)
			{
				optimal_value = current_node_a->value;
				optimal_target = current_node_a;
			}
			current_node_a = current_node_a->next;
		}
		if (optimal_value == LONG_MAX)
			b->target_node = get_min_value_node(a);
		else
			b->target_node = optimal_target;
		b = b->next;
	}
}

/**
 * Initializes nodes in stack 'b' based on stack 'a'.
 *
 * Assigns positional indexes to nodes in both stacks 'a' and 'b' and
 * then sets the target node for elements in stack 'b' based on their
 * positional relationship to nodes in stack 'a'. This prepares stack 'b'
 * for operations by identifying the optimal targets for moves considering
 * the current state of stack 'a'.
 *
 * @param a Pointer to the top node of stack 'a'.
 * @param b Pointer to the top node of stack 'b'.
 */
void	prepare_stack_b(t_stack_node *a, t_stack_node *b)
{
	set_positions(a);
	set_positions(b);
	set_targets_for_b(a, b);
}
