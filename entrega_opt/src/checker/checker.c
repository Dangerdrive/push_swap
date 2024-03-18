/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:42:41 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/07 13:55:20 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

/**
 * Populates stack 'a' with integers parsed from argv strings.
 *
 * Iterates over argv, converting each string to a long. Validates the
 * converted value for number format, range within INT_MIN and INT_MAX, and
 * uniqueness within the stack. On validation failure, frees resources and
 * exits. Successfully parsed integers are appended to stack 'a'.
 * This bonus version does not print errors.
 *
 * @param a Double pointer to the top of stack 'a'.
 * @param argv Null-terminated array of strings representing integers.
 */
static void	bonus_populate_stack_a(t_stack_node **a, char **argv)
{
	long	value;
	int		i;

	i = 0;
	while (argv[i])
	{
		if (!(is_valid_number(argv[i])))
			exit_with_error(a, false);
		value = ft_atol(argv[i]);
		if (value > INT_MAX || value < INT_MIN)
			exit_with_error(a, false);
		if (has_duplicate(*a, (int)value))
			exit_with_error(a, false);
		add_node_back(a, (int)value);
		i++;
	}
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

void	validate_and_print_result(t_stack_node **a, t_stack_node **b,
			char *line)
{
	char	*tmp;

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
	t_stack_node	*b;
	char			*line;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = ft_split(argv[1], ' ');
	bonus_populate_stack_a(&a, argv + 1);
	line = get_next_line(0);
	if (!line && !is_stack_sorted(a))
		ft_printf("KO\n");
	else if (!line && is_stack_sorted(a))
		ft_printf("KO\n");
	else
		validate_and_print_result(&a, &b, line);
	free_stack(&b);
	free_stack(&a);
	if (argc == 2)
		ft_free_split(argv, 1);
	return (EXIT_SUCCESS);
}
