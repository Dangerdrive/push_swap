/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_stack_a.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:03:47 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/06 17:04:02 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Initializes a new stack node with default values.
 * 
 * This function sets the value of a new stack node to 0,
 * and the position and total_moves * to -1. 
 * It also sets the is_above_median and is_optimal_move flags to false,
 * and the target_node * to NULL.
 * The next and prev pointers are set to NULL as well.
 *
 * @param stack Pointer to the stack node to be initialized.
 */
void	init_node(t_stack_node *stack)
{
	stack->value = 0;
	stack->position = -1;
	stack->total_moves = 0;
	stack->is_above_median = false;
	stack->is_optimal_move = false;
	stack->target_node = NULL;
	stack->next = NULL;
	stack->prev = NULL;
}

/**
 * Checks if a string represents a valid number.
 *
 * Validates that a given string is a properly formatted number, potentially
 * starting with a '+' or '-' sign, followed by digits. It ensures the string
 * does not contain any characters outside of these valid options.
 *
 * @param parameter The string to check for numeric validity.
 * @return true if the string is a valid number, false otherwise.
 */
bool	is_valid_number(char *parameter)
{
	if (!(*parameter == '+'
			|| *parameter == '-'
			|| (*parameter >= '0' && *parameter <= '9')))
		return (false);
	if ((*parameter == '+'
			|| *parameter == '-')
		&& !(parameter[1] >= '0' && parameter[1] <= '9'))
		return (false);
	while (*++parameter)
	{
		if (!(*parameter >= '0' && *parameter <= '9'))
			return (false);
	}
	return (true);
}

/**
 * Checks if a given value exists in a stack.
 *
 * Iterates through the stack to determine if any node contains a value
 * equal to 'n'. The function stops searching through the stack either
 * when it finds a duplicate (returning true) or reaches the end
 * of the stack without finding a duplicate (returning false).
 *
 * @param a The head node of the stack to search for duplicates.
 * @param n The value to search for within the stack.
 * @return Returns true if a duplicate value is found; otherwise returns false.
 */
bool	has_duplicate(t_stack_node *a, int n)
{
	if (!a)
		return (false);
	while (a)
	{
		if (a->value == n)
			return (true);
		a = a->next;
	}
	return (false);
}

/**
 * Adds a new node with a specified value to the end of a stack.
 *
 * Allocates memory for a new node, initializes it, and sets its value to the
 * specified integer. If the stack is empty, the new node becomes the first
 * node. Otherwise, the new node is appended to the end, maintaining the
 * doubly linked list structure by updating the 'next' and 'prev' pointers.
 *
 * @param stack Double pointer to the top node of the stack.
 * @param n The integer value to assign to the new node.
 */
void	add_node_back(t_stack_node **stack, int n)
{
	t_stack_node	*node;
	t_stack_node	*last_node;

	node = NULL;
	last_node = NULL;
	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node));
	if (!node)
		return ;
	init_node(node);
	node->value = n;
	if (!(*stack))
		*stack = node;
	else
	{
		last_node = find_last(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

/**
 * Populates stack 'a' with integers parsed from argv strings.
 *
 * Iterates over argv, converting each string to a long. Validates the
 * converted value for number format, range within INT_MIN and INT_MAX, and
 * uniqueness within the stack. On validation failure, frees resources and
 * exits. Successfully parsed integers are appended to stack 'a'.
 *
 * @param a Double pointer to the top of stack 'a'.
 * @param argv Null-terminated array of strings representing integers.
 */
void	populate_stack_a(t_stack_node **a, char **argv)
{
	long	value;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!(is_valid_number(argv[i])))
			exit_with_error(a, true);
		value = ft_atol(argv[i]);
		if (value > INT_MAX || value < INT_MIN)
			exit_with_error(a, true);
		if (has_duplicate(*a, (int)value))
			exit_with_error(a, true);
		add_node_back(a, (int)value);
		i++;
	}
}
