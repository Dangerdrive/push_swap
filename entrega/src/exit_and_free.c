/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:12:33 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/27 14:59:55 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * Frees all nodes in a stack and sets the stack pointer to NULL.
 *
 * Iterates through the stack starting from the top node, freeing each node
 * sequentially. Before freeing, it zeroes out the value of the node as a
 * precautionary measure. After all nodes are freed, the stack pointer is
 * set to NULL to indicate that the stack is empty and prevent dangling pointer
 * access.
 *
 * @param stack Double pointer to the top node of the stack to be freed. This
 *              allows directly modifying the original stack pointer to NULL.
 */
void	free_stack(t_stack_node **stack)
{
	t_stack_node	*next_node;
	t_stack_node	*current_node;

	if (!stack)
		return ;
	current_node = *stack;
	while (current_node)
	{
		next_node = current_node->next;
		current_node->value = 0;
		free(current_node);
		current_node = next_node;
	}
	*stack = NULL;
}

/**
 * Frees the stack and exits the program with an error message.
 *
 * This function is called upon encountering an error condition. It first frees
 * the memory allocated for the stack to prevent memory leaks. Then, it prints
 * an "Error" message to standard output to inform the user of the issue. 
 * Finally, it exits the program with a status code of 1, 
 * indicating an error has occurred.
 *
 * @param a Double pointer to the top node of the stack that needs to be freed
 *          due to an error condition.
 */
void	exit_with_error(t_stack_node **a, bool	print, int ac, char **tab)
{
	free_stack(a);
	if (ac == 2)
		ft_free_split(tab, ft_strarray_len(tab));
	if (print == true)
		ft_printf("Error\n");
	exit(EXIT_FAILURE);
}
