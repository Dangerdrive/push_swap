/*push.c*/
#include "../inc/push_swap.h"

// Note: Please keep documentation within 80 columns for readability.

// Note: Please keep documentation within 80 columns for readability.

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
 * Transfers the top node from the source stack to the top of the destination stack.
 * 
 * This function moves the top (head) node of the source stack to become the new top node
 * of the destination stack. It correctly updates pointers to maintain the integrity of both
 * stacks. If the source stack is empty, the function does nothing.
 *
 * @param dest Pointer to the pointer of the top node of the destination stack.
 * @param src Pointer to the pointer of the top node of the source stack.
 */
static void	push(t_stack_node **dest, t_stack_node **src)
{
	t_stack_node	*node_to_push;

	if (!*src)
		return ;
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
		(*src)->prev = NULL;
	node_to_push->prev = NULL;
	if (!*dest)
	{
		*dest = node_to_push;
		node_to_push->next = NULL;
	}
	else
	{
		node_to_push->next = *dest;
		node_to_push->next->prev = node_to_push;
		*dest = node_to_push;
	}
}

/**
 * Pushes the top node from stack 'b' to stack 'a' and optionally prints the operation.
 *
 * @param a Pointer to the top of stack 'a', which will receive the top node from stack 'b'.
 * @param b Pointer to the top of stack 'b', the source stack for the push operation.
 * @param print If false, prints "pa\n" to indicate the push action; does not print if true.
 */
void	pa(t_stack_node **a, t_stack_node **b)
{
	push(a, b);
	ft_printf("pa\n");
}

/**
 * Pushes the top node from stack 'b' to stack 'a' and optionally prints the operation.
 *
 * @param a Pointer to the top of stack 'a', which will receive the top node from stack 'b'.
 * @param b Pointer to the top of stack 'b', the source stack for the push operation.
 * @param print If false, prints "pa\n" to indicate the push action; does not print if true.
 */
void	pb(t_stack_node **b, t_stack_node **a)
{
	push(b, a);
	ft_printf("pb\n");
}

/*reverse_rotate.c*/
/**
 * Performs a reverse rotation on a given stack.
 *
 * In a reverse rotation, the last element of the stack becomes the first,
 * effectively rotating the stack upwards. The function does nothing if the
 * stack is empty or has only one element.
 *
 * @param stack Pointer to the top node of the stack to be reverse rotated.
 */
static void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = find_last(*stack);
	last->prev->next = NULL;
	last->next = *stack;
	last->prev = NULL;
	*stack = last;
	last->next->prev = last;
}

/**
 * Performs a reverse rotate operation on stack 'a' and optionally prints the operation.
 *
 * This function applies a reverse rotation on stack 'a', moving the last element to the top of the stack.
 *
 * @param a Pointer to the top node of stack 'a' to be reverse rotated.
 * @param print If false, "rra\n" is printed to indicate the reverse rotate action; no output if true.
 */
void	rra(t_stack_node **a)
{
	reverse_rotate(a);
	ft_printf("rra\n");
}

/**
 * Performs a reverse rotate operation on stack 'b' and optionally prints the operation.
 *
 * This function applies a reverse rotation on stack 'b', moving the last element to the top of the stack.
 *
 * @param b Pointer to the top node of stack 'b' to be reverse rotated.
 * @param print If false, "rra\n" is printed to indicate the reverse rotate action; no output if true.
 */
void	rrb(t_stack_node **b)
{
	reverse_rotate(b);
	ft_printf("rrb\n");
}

/**
 * Performs a reverse rotate operation on both stacks 'a' and 'b' and optionally prints the operation.
 *
 * This function applies a reverse rotation on stacks 'a' and 'b', moving the last element to the top of the stack.
 *
 * @param a Pointer to the top node of stacks 'a' and 'b' to be reverse rotated.
 * @param b Pointer to the top node of stack 'b' to be reverse rotated.
 * @param print If false, "rra\n" is printed to indicate the reverse rotate action; no output if true.
 */
void	rrr(t_stack_node **a, t_stack_node **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ft_printf("rrr\n");
}

/*rotate.c*/
/**
 * Rotates the elements of a given stack upwards.
 *
 * The first element becomes the last one, and all other elements move up by one position.
 * This operation is skipped if the stack is empty or contains only one element.
 *
 * @param stack Pointer to the stack to be rotated.
 */
static void	rotate(t_stack_node **stack)
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
 * and optionally prints the operation.
 *
 * Rotates stack 'a' by moving the top element to the bottom, effectively
 * cycling the stack's elements. This prepares 'a' for subsequent manipulations
 *
 * @param a Pointer to the top of stack 'a' for rotation.
 * @param print When false, "ra" is printed; silent if true.
 */
void	ra(t_stack_node **a)
{
	rotate(a);
	ft_printf("ra\n");
}

/**
 * Rotates stack 'b' upwards, optionally printing "rb".
 *
 * Elements in stack 'b' are rotated upwards, moving the top element to the
 * bottom. This action rearranges the stack for further operations.
 *
 * @param b Pointer to stack 'b''s top node for rotation.
 * @param print If false, prints "rb" to signal the rotation; silent if true.
 */

void	rb(t_stack_node **b)
{
	rotate(b);
	ft_printf("rb\n");
}

/**
 * Rotates stacks 'a' and 'b' upwards, optionally printing "rr".
 *
 * Elements in stacks 'a' and 'b' are rotated upwards, with the first element
 * moving to the last position. This uniform action aligns both stacks for
 * subsequent operations.
 *
 * @param a Pointer to stack 'a''s top node for rotation.
 * @param b Pointer to stack 'b''s top node for rotation.
 * @param print Controls printing of "rr" to indicate rotation.
 */
void	rr(t_stack_node **a, t_stack_node **b)
{
	rotate(a);
	rotate(b);
	ft_printf("rr\n");
}

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
	current_index(*a);
	current_index(*b);
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
								t_stack_node *cheapest_node)
{
	while (*b != cheapest_node->target_node
		&& *a != cheapest_node)
		rrr(a, b);
	current_index(*a);
	current_index(*b);
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
	current_index(*a);
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
/**
 * Swaps the top two elements of a given stack.
 *
 * This function swaps the top two elements of a given stack. 
 * It does nothing if the stack is empty
 * or has only one element.
 *
 * @param head Pointer to the top node of the stack to be swapped.
 */
static void	swap(t_stack_node **head)
{
	if (!*head || !(*head)->next)
		return ;
	*head = (*head)->next;
	(*head)->prev->prev = *head;
	(*head)->prev->next = (*head)->next;
	if ((*head)->next)
		(*head)->next->prev = (*head)->prev;
	(*head)->next = (*head)->prev;
	(*head)->prev = NULL;
}

/**
 * Swaps the top two elements of stack 'a' and optionally prints the operation.
 *
 * This function swaps the top two elements of stack 'a',
 *  effectively reversing their positions.
 *
 * @param a Pointer to the top node of stack 'a' to be swapped.
 * @param print If false, "sa\n" is printed to indicate the swap action;
 *  no output if true.
 */
void	sa(t_stack_node	**a)
{
	swap(a);
	ft_printf("sa\n");
}

/**
 * Swaps the top two elements of stack 'b' and optionally prints the operation.
 *
 * This function swaps the top two elements of stack 'b',
 *  effectively reversing their positions.
 *
 * @param b Pointer to the top node of stack 'b' to be swapped.
 * @param print If false, "sb\n" is printed to indicate the swap action;
 *  no output if true.
 */
void	sb(t_stack_node **b)
{
	swap(b);
	ft_printf("sb\n");
}

/**
 * Swaps the top two elements of stacks 'a' and 'b' and optionally
 *  prints the operation.
 *
 * This function swaps the top two elements of stacks 'a' and 'b',
 * effectively reversing their positions.
 *
 * @param a Pointer to the top node of stack 'a' to be swapped.
 * @param b Pointer to the top node of stack 'b' to be swapped.
 * @param print If false, "ss\n" is printed to indicate the swap action;
 *  no output if true.
 */
void	ss(t_stack_node **a, t_stack_node **b)
{
	swap(a);
	swap(b);
	ft_printf("ss\n");
}

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

/*
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

void	free_errors(t_stack_node **a)
{
	free_stack(a);
	ft_printf("Error\n");
	exit(1);
}

/*init_a_to_b.c*/
void	current_index(t_stack_node *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->position = i;
		if (i <= median)
			stack->is_above_median = true;
		else
			stack->is_above_median = false;
		stack = stack->next;
		++i;
	}
}

static void	set_target_a(t_stack_node *a, t_stack_node *b)//Find `a` node's target in stack `b`
{
	t_stack_node	*current_b;
	t_stack_node	*target_node;
	long			best_match_index;

	while (a)
	{
		best_match_index = LONG_MIN;
		current_b = b;
		while (current_b)
		{
			if (current_b->value < a->value
				&& current_b->value > best_match_index)
			{
				best_match_index = current_b->value;
				target_node = current_b;
			}
			current_b = current_b->next;
		}
		if (best_match_index == LONG_MIN)
			a->target_node = get_max_value_node(b);
		else
			a->target_node = target_node;
		a = a->next;
	}
}

static void	cost_analysis_a(t_stack_node *a, t_stack_node *b)
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

void	set_cheapest(t_stack_node *stack)
{
	long			cheapest_value;
	t_stack_node	*cheapest_node;

	if (!stack)
		return ;
	cheapest_value = LONG_MAX;
	while (stack)
	{
		if (stack->total_moves < cheapest_value)
		{
			cheapest_value = stack->total_moves;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
	cheapest_node->is_optimal_move = true;
}

void	init_nodes_a(t_stack_node *a, t_stack_node *b)
{
	current_index(a);
	current_index(b);
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest(a);
}

/*init_b_to_a.c*/
static void	set_target_b(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_a;
	t_stack_node	*target_node;
	long			best_match_index;

	while (b)
	{
		best_match_index = LONG_MAX;
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value
				&& current_a->value < best_match_index)
			{
				best_match_index = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (best_match_index == LONG_MAX)
			b->target_node = get_min_value_node(a);
		else
			b->target_node = target_node;
		b = b->next;
	}
}

void	init_nodes_b(t_stack_node *a, t_stack_node *b)
{
	current_index(a);
	current_index(b);
	set_target_b(a, b);
}

/*split.c*/
static int	count_words(char *s, char c)
{
	int		count;
	bool	inside_word;

	count = 0;
	while (*s)
	{
		inside_word = false;
		while (*s == c)
			++s;
		while (*s != c && *s)
		{
			if (!inside_word)
			{
				++count;
				inside_word = true;
			}
			++s;
		}
	}
	return (count);
}

static char	*get_next_word(char *s, char c)
{
	static int	cursor = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (s[cursor] == c)
		++cursor;
	while ((s[cursor + len] != c) && s[cursor + len])
		++len;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if (!next_word)
		return (NULL);
	while ((s[cursor] != c) && s[cursor])
		next_word[i++] = s[cursor++];
	next_word[i] = '\0';
	return (next_word);
}

char **split(char *s, char c)
{
	int		words_count;
	char	**result_array;
	int		i;

	i = 0;
	words_count = count_words(s, c);
	if (!words_count)
		exit(1);
	result_array = malloc(sizeof(char *) * (size_t)(words_count + 2));
	if (!result_array)
		return (NULL);
	while (words_count-- >= 0)
	{
		if (i == 0)
		{
			result_array[i] = malloc(sizeof(char));
			if (!result_array[i])
				return (NULL);
			result_array[i++][0] = '\0';
			continue ;
		}
		result_array[i++] = get_next_word(s, c);
	}
	result_array[i] = NULL;
	return (result_array);
}


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

/*stack_init.c*/
// static long	ft_atol(const char *s)
// {
// 	long	result;
// 	int		sign;

// 	result = 0;
// 	sign = 1;
// 	while (*s == ' ' || *s == '\t' || *s == '\n' || \
// 			*s == '\r' || *s == '\f' || *s == '\v')
// 		s++;
// 	if (*s == '-' || *s == '+')
// 	{
// 		if (*s == '-')
// 			sign = -1;
// 		s++;
// 	}
// 	while (ft_isdigit(*s))
// 		result = result * 10 + (*s++ - '0');
// 	return (result * sign);
// }

static void	append_node(t_stack_node **stack, int n)
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
	//node->next = NULL;
	node->value = n;
	if (!(*stack))
	{
		*stack = node;
		//node->prev = NULL;
	}
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
		append_node(a, (int)value);
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
