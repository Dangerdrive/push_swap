/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:42:41 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/31 10:42:49 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

/**
 * Validates command execution results on stacks and prints the outcome.
 * 
 * Reads and processes each command from input, adjusting stacks 'a' and 'b'
 * accordingly. After processing, checks if stack 'b' is empty and stack 'a' is
 * sorted to determine the validity of the sort operation. Outputs "OK" if the
 * sort is successful and "KO" otherwise.
 *
 * @param a Pointer to the top of stack 'a'.
 * @param b Pointer to the top of stack 'b'.
 * @param line The current command line being processed.
 */
static void	check_rotates(t_stack_node **a, t_stack_node **b, char *line)
{
	if (line[2] == 'a')
		reverse_rotate(a);
	else if (line[2] == 'b')
		reverse_rotate(b);
	else if (line[2] == 'r')
	{
		reverse_rotate(a);
		reverse_rotate(b);
	}
	else if (line[0] == 'r' && line[1] == 'a' && line[2] == '\n')
		rotate(a);
	else if (line[0] == 'r' && line[1] == 'b' && line[2] == '\n')
		rotate(b);
	else if (line[1] == 'r' && line[2] == '\n')
	{
		rotate(a);
		rotate(b);
	}
	else
	{
		write(STDERR_FILENO, "Error\n", 7);
		free(line);
		free_stack(a);
		exit(EXIT_FAILURE);
	}
}

/**
 * Processes a command line and applies the corresponding stack operation.
 *
 * Interprets commands for swapping ('sa', 'sb', 'ss'), pushing ('pa', 'pb'),
 * and rotating ('ra', 'rb', 'rr', 'rra', 'rrb', 'rrr') elements between
 * stack 'a' and 'b'. Calls `check_rotates` for rotation operations. On
 * encountering an invalid command, it prints "Error" and exits.
 *
 * @param a Pointer to the top of stack 'a' for applying commands.
 * @param b Pointer to the top of stack 'b' for applying commands.
 * @param line The command line to be processed.
 * @return Returns the next command line from input for further processing.
 */
static char	*check_commands(t_stack_node **a, t_stack_node **b, char *line)
{
	if (line[0] == 's' && line[1] == 'a' && line[2] == '\n')
		swap(a);
	else if (line[0] == 's' && line[1] == 'b' && line[2] == '\n')
		swap(b);
	else if (line[1] == 's' && line[2] == '\n')
	{
		swap(a);
		swap(b);
	}
	else if (line[0] == 'p' && line[1] == 'a' && line[2] == '\n')
		push(a, b);
	else if (line[0] == 'p' && line[1] == 'b' && line[2] == '\n')
		push(b, a);
	else if (line[0] == 'r' || line[0] == 's')
		check_rotates(a, b, line);
	else
	{
		write(STDERR_FILENO, "Error\n", 7);
		free(line);
		free_stack(a);
		exit(EXIT_FAILURE);
	}
	return (get_next_line(0));
}

/**
 * Validates command execution results on stacks and prints the outcome.
 * 
 * Reads and processes each command from input, adjusting stacks 'a' and 'b'
 * accordingly. After processing, checks if stack 'b' is empty and stack 'a' is
 * sorted to determine the validity of the sort operation. Outputs "OK" if the
 * sort is successful and "KO" otherwise.
 *
 * @param a Pointer to the top of stack 'a'.
 * @param b Pointer to the top of stack 'b'.
 * @param line The current command line being processed.
 */
void	validate_and_print_result(t_stack_node **a,
			char *line)
{
	char			*tmp;
	t_stack_node	**b;

	b = NULL;
	while (line && *line != '\n')
	{
		tmp = line;
		line = check_commands(a, b, line);
		free(tmp);
	}
	if (*b)
		ft_printf("KO\n");
	else if (!is_stack_sorted(*a))
		ft_printf("KO\n");
	else
		ft_printf("OK\n");
	free(line);
}

/**
 * Entry point for the stack checker program.
 *
 * This program reads commands from standard input to manipulate a stack of
 * numbers according to given operations. It initializes two stacks, 'a' and 'b',
 * populates stack 'a' with input arguments, and processes each command to
 * manipulate the stacks. After processing all commands, it determines if stack
 * 'a' is sorted and stack 'b' is empty, indicating a successful sort, and
 * outputs the result ("OK" for success, "KO" for failure).
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments, including the program name.
 * @return Returns EXIT_SUCCESS on completion.
 */
int	main(int argc, char **argv)
{
	t_stack_node	*a;
	char			*line;
	char			**tab;

	tab = NULL;
	a = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		tab = ft_split(argv[1], ' ');
	else if (argc > 2)
		tab = &argv[1];
	populate_stack_a(&a, argc, tab);
	line = get_next_line(0);
	if (!line && !is_stack_sorted(a))
		ft_printf("KO\n");
	else if (!line && is_stack_sorted(a))
		ft_printf("KO\n");
	else
		validate_and_print_result(&a, line);
	free_stack(&a);
	free(line);
	return (EXIT_SUCCESS);
}
