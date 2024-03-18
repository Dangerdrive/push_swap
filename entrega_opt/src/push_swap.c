/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:12:33 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/07 13:58:08 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

/**
 * The main entry point for the push_swap program.
 *
 * Initializes two stacks, 'a' and 'b', and populates stack 'a' with integers
 * from the command line arguments. If stack 'a' is not already sorted, it
 * applies sorting algorithms based on the number of integers. For 2 or 3
 * integers, specific small sort functions are called. For more integers, a
 * general sorting algorithm is applied. Finally, the program frees allocated
 * memory before exiting.
 *
 * @param argc The number of command line arguments.
 * @param argv The array of command line arguments.
 * @return 0 on successful execution, 1 if input is invalid or missing.
 */
int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = ft_split(argv[1], ' ');
	populate_stack_a(&a, argv + 1);
	if (!is_stack_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a);
		else if (stack_len(a) == 3)
			sort_three_nodes(&a);
		else
			sort_stack_a(&a, &b);
	}
	free_stack(&a);
	if (argc == 2)
		ft_free_split(argv, 1);
	return (EXIT_SUCCESS);
}
