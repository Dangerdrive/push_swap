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