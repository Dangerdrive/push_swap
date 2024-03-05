/*push.c*/
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


/*reverse_rotate.c*/


/*rotate.c*/


/*sort_stacks.c*/
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
static void	rotate_both(t_stack_node **a,
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
static void	rev_rotate_both(t_stack_node **a,
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
 * Moves the top node from stack 'a' to 'b', optimizing nodes for pushing.
 *
 * This function transfers the top node from stack 'a' to 'b', updating nodes
 * in both stacks for the next push. It manages rotation and reverse rotation
 * in both stacks to optimize push positioning.
 *
 * @param a Pointer to the top node of stack 'a', source for the push.
 * @param b Pointer to the top node of stack 'b', destination for the push.
 */
static void	move_a_to_b(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = get_optimal_node(*a);
	if (cheapest_node->is_above_median
		&& cheapest_node->target_node->is_above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->is_above_median)
		&& !(cheapest_node->target_node->is_above_median))
		rev_rotate_both(a, b, cheapest_node);
	prep_for_push(a, cheapest_node, 'a');
	prep_for_push(b, cheapest_node->target_node, 'b');
	pb(b, a);
}

/**
 * Moves the top node from stack 'b' to 'a', updating nodes for optimal
 * pushing.
 *
 * This function transfers the top node from stack 'b' to 'a', and updates
 * nodes in both stacks for the next push operation. It also manages rotation
 * and reverse rotation in both stacks to optimize the push position.
 *
 * @param a Pointer to the top node of stack 'a', the destination for the push.
 * @param b Pointer to the top node of stack 'b', the source for the push.
 */
static void	move_b_to_a(t_stack_node **a, t_stack_node **b)
{
	prep_for_push(a, (*b)->target_node, 'a');
	pa(a, b);
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
static void	rotate_min_to_top(t_stack_node **a)
{
	while ((*a)->value != get_min_value_node(*a)->value)
	{
		if (get_min_value_node(*a)->is_above_median)
			ra(a);
		else
			rra(a);
	}
}

void	sort_stacks(t_stack_node **a, t_stack_node **b)
{
	int	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !is_stack_sorted(*a))
		pb(b, a);
	if (len_a-- > 3 && !is_stack_sorted(*a))
		pb(b, a);
	while (len_a-- > 3 && !is_stack_sorted(*a))
	{
		init_nodes_a(*a, *b);
		move_a_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	set_positions(*a);
	rotate_min_to_top(a);
}

/*sort_three*/

/**
 * Sorts a stack with three elements using a specific sequence of operations.
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
void	sort_three(t_stack_node **a)
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

/*swap.c*/

/*handle_errors.c*/
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
 * @return Returns true if a duplicate value is found; otherwise, returns false.
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

//keep the documentation within 80 columns

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
void free_stack(t_stack_node **stack)
{
	t_stack_node *next_node;
	t_stack_node *current_node;

	if (!stack)
		return;
	
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
 * an "Error" message to standard output to inform the user of the issue. Finally,
 * it exits the program with a status code of 1, indicating an error has occurred.
 *
 * @param a Double pointer to the top node of the stack that needs to be freed
 *          due to an error condition.
 */
void	free_errors(t_stack_node **a)
{
	free_stack(a);
	ft_printf("Error\n");
	exit(1);
}

/*init_a_to_b.c*/
/**
 * Assigns the current position to each node in the stack and marks if it is above
 * the median position.
 *
 * Iterates through the stack, assigning each node an index starting from 0 and
 * determining if it is positioned above or below the median of the stack's
 * length. This classification aids in optimizing operations that depend on
 * the node's position relative to the stack's median.
 *
 * @param stack Pointer to the top node of the stack to be indexed.
 */
void	set_positions(t_stack_node *first_node)
{
	int	i;
	int	median;

	i = 0;
	if (!first_node)
		return ;
	median = stack_len(first_node) / 2;
	while (first_node)
	{
		first_node->position = i;
		if (i <= median)
			first_node->is_above_median = true;
		else
			first_node->is_above_median = false;
		first_node = first_node->next;
		++i;
	}
}

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
 * Identifies and marks the node with the minimum total moves as the optimal move.
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
void	init_nodes_a(t_stack_node *a, t_stack_node *b)
{
	set_positions(a);
	set_positions(b);
	set_targets_for_a(a, b);
	calculate_moves_for_a(a, b);
	set_optimal_move(a);
}

/*init_b_to_a.c*/
/**
 * Assigns each node in stack 'b' a target node in stack 'a' for optimal movement.
 *
 * Iterates through stack 'b', for each node, finding the closest higher value in
 * stack 'a'. This closest higher value is marked as the target node for movements.
 * If no higher value is found (implying 'b' node's value is higher than all in 'a'),
 * the target is set to the minimum value node in 'a', ensuring logical stack operations.
 *
 * @param a The source stack from which target nodes are identified.
 * @param b The target stack for which nodes are being analyzed and assigned targets.
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
void	init_nodes_b(t_stack_node *a, t_stack_node *b)
{
	set_positions(a);
	set_positions(b);
	set_targets_for_b(a, b);
}

/*split.c*/

/*
 Both functions, `ft_split()` `split()` split a string into an array of substrings using a specified delimiter character.
 However, the differences are:

 #1	Function Signature:
	- `ft_split` takes a constant string (const char *s) as input.
	- `split` takes a mutable string (char *s) as input.

#2	Input Mutability:
	- `ft_split` takes a constant string (const char *s) as input, indicating that it does not modify the input string.
	- `split` takes a mutable string (char *s) as input, indicating it may modify the input string during tokenization.
	- Mutable strings can be modified in-place, meaning you can change the characters within the string without creating
	  a new string object.
	- Immutable strings, on the other hand, cannot be modified once they are created. Any operation that appears to modify
	  an immutable string actually creates a new string with the desired changes.

#TOKENIZATION:
	- Tokenization is the process of breaking down a text or a sequence of characters into smaller units called tokens.
	- Tokens are typically words, phrases, symbols, or other meaningful elements within the text.
	- In the case of push_swap,  Word tokenization is the process of splitting text into words or word-like units.
	  It involves identifying word boundaries and separating words from each other. For example, in the sentence "Tokenization
	  is important," the words "Tokenization," "is," and "important" are individual tokens.
	- Purpose:
	  Tokenization is a preprocessing step that simplifies text analysis tasks.
	  It allows text to be represented in a form that can be easily processed by algorithms and models.

#3	Memory Management:
	- `ft_split` allocates memory for the resulting string array and the individual substrings within the function,
	  and frees memory
	- `split` also allocates memory for the resulting string array and substrings but relies on the caller to free the memory.

#4	Static Variable Usage:
	- `ft_split` does not use static variables in its implementation.
	- `split` uses a static variable cursor to keep track of the position in the input string for tokenization.

#5	Error Handling:
	- `ft_split` returns NULL if memory allocation fails during the tokenization process.
	- `split` exits the program with an error code if the number of words is zero.

In summary, both functions perform string tokenization, but they have differences in terms of input mutability, memory
management, and error handling.
*/

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
static void	add_node_back(t_stack_node **stack, int n)
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
			free_errors(a);
		value = ft_atol(argv[i]);
		if (value > INT_MAX || value < INT_MIN)
			free_errors(a);
		if (has_duplicate(*a, (int)value))
			free_errors(a);
		add_node_back(a, (int)value);
		i++;
	}
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
 * Realigns stack to prepare a specific node for push operation.
 *
 * Adjusts the given stack by rotating or reverse rotating it until the
 * specified node is at the top. This preparation step is crucial for
 * efficiently executing a push operation. It determines the direction
 * of rotation based on the node's position relative to the median and
 * applies the appropriate rotation command based on the stack's identity.
 *
 * @param stack Pointer to the stack ('a' or 'b') to be adjusted.
 * @param top_node The node to move to the top of the stack.
 * @param stack_name Identifier for the stack ('a' or 'b').
 */
void	prep_for_push(t_stack_node **stack,
						t_stack_node *top_node,
						char stack_name)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->is_above_median)
				ra(stack);
			else
				rra(stack);
		}
		else if (stack_name == 'b')
		{
			if (top_node->is_above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}

/*stack_utils.c*/
/**
 * Calculates the length of a stack.
 *
 * Iterates through the stack, incrementing a counter for each node encountered
 * until it reaches the end of the stack. This function is useful for 
 * determining the size of the stack, which can be essential for operations 
 * that depend on the stack's current state.
 *
 * @param stack Pointer to the top node of the stack.
 * @return The total number of nodes in the stack. Returns 0 if the stack is empty.
 */
int	stack_len(t_stack_node *first_node)
{
	int	len;

	if (!first_node)
		return (0);
	len = 0;
	while (first_node)
	{
		first_node = first_node->next;
		len++;
	}
	return (len);
}

/**
 * Finds and returns the last node in a stack.
 *
 * Traverses the stack from the top node to the end, returning the last node
 * in the sequence. If the stack is empty, returns NULL.
 *
 * @param stack Pointer to the top node of the stack to be traversed.
 * @return Pointer to the last node in the stack, or NULL if stack is empty.
 */
t_stack_node	*find_last(t_stack_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

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
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

/**
 * Identifies and returns the node with the minimum value in a stack.
 *
 * Begins with the assumption that the minimum value is the largest possible
 * long value. Iterates through the stack, updating the minimum value and
 * corresponding node as it finds lower values.
 *
 * @param stack Pointer to the first node of the stack to search through.
 * @return Pointer to the node with the minimum value; NULL if the stack is
 *         empty.
 */
t_stack_node	*get_min_value_node(t_stack_node *stack)
{
	long			min;
	t_stack_node	*min_node;

	if (!stack)
		return (NULL);
	min = LONG_MAX;
	while (stack)
	{
		if (stack->value < min)
		{
			min = stack->value;
			min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

/**
 * Finds and returns the node with the maximum value in a stack.
 *
 * Iterates through the stack to identify the node with the highest value.
 * Initializes the maximum value as the smallest possible long to ensure
 * any stack value is larger. Updates the max value and max node pointer
 * as it traverses the stack.
 *
 * @param stack The starting node of the stack to search.
 * @return Pointer to the node with the maximum value, or NULL if the
 * stack is empty.
 */
t_stack_node	*get_max_value_node(t_stack_node *stack)
{
	long			max;
	t_stack_node	*max_node;

	if (!stack)
		return (NULL);
	max = LONG_MIN;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_node = stack;
		}
		stack = stack->next;
	}
	return (max_node);
}

/*push_swap.c*/
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
			sort_three(&a);
		else
			sort_stacks(&a, &b);
	}
	free_stack(&a);
	// char **tmp = argv;
	// while (*tmp)
	// {
	// 	free(*tmp);
	// 	tmp++;
	// }
	// free(tmp);
	return (0);
}
