#include "../inc/push_swap.h"

/**
 * Moves the top node from one stack to another.
 *
 * Transfers the top node of the source stack (src) to the destination stack
 * (dest), adjusting the linked list pointers accordingly. This operation is
 * the foundation of the push operation in stack manipulation algorithms. If
 * src is empty, the operation is skipped to preserve stack integrity.
 *
 * @param dest Pointer to the top of the destination stack.
 * @param src Pointer to the top of the source stack.
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