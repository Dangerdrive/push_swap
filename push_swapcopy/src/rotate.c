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