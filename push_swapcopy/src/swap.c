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
