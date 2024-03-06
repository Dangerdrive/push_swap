/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:12:46 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/06 20:08:16 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Rotates the elements of a given stack upwards.
 *
 * The first element becomes the last one, 
 * and all other elements move up by one position.
 * This operation is skipped if stack is empty or contains only one element.
 *
 * @param stack Pointer to the stack to be rotated.
 */
void	rotate(t_stack_node **stack)
{
	t_stack_node	*last_node;

	if (!*stack || !(*stack)->next)
		return ;
	last_node = find_last(*stack);
	last_node->next = *stack;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	last_node->next->prev = last_node;
	last_node->next->next = NULL;
}

/**
 * Rotates the elements of stack 'a' upwards 
 * and prints the operation.
 *
 * Rotates stack 'a' by moving the top element to the bottom, effectively
 * cycling the stack's elements. This prepares 'a' for subsequent manipulations
 *
 * @param a Pointer to the top of stack 'a' for rotation.
 */
void	ra(t_stack_node **a)
{
	rotate(a);
	ft_printf("ra\n");
}

/**
 * Rotates stack 'b' upwards, printing "rb".
 *
 * Elements in stack 'b' are rotated upwards, moving the top element to the
 * bottom. This action rearranges the stack for further operations.
 *
 * @param b Pointer to stack 'b''s top node for rotation.
 */

void	rb(t_stack_node **b)
{
	rotate(b);
	ft_printf("rb\n");
}

/**
 * Rotates stacks 'a' and 'b' upwards, printing "rr".
 *
 * Elements in stacks 'a' and 'b' are rotated upwards, with the first element
 * moving to the last position. This uniform action aligns both stacks for
 * subsequent operations.
 *
 * @param a Pointer to stack 'a''s top node for rotation.
 * @param b Pointer to stack 'b''s top node for rotation.
 */
void	rr(t_stack_node **a, t_stack_node **b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}
