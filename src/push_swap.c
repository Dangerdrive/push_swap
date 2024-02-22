

//
// Created by fde-alen on 1/24/24.
//
#include "../includes/push_swap.h"


//sa (swap a): Swap the first 2 elements at the top of stack a.
//Do nothing if there is only one or no elements.

//sb (swap b): Swap the first 2 elements at the top of stack b.
//Do nothing if there is only one or no elements.

//ss : sa and sb at the same time.
//pa (push a): Take the first element at the top of b and put it at the top of a.
//Do nothing if b is empty.
//pb (push b): Take the first element at the top of a and put it at the top of b.
//Do nothing if a is empty.
//ra (rotate a): Shift up all elements of stack a by 1.
//The first element becomes the last one.
//rb (rotate b): Shift up all elements of stack b by 1.
//The first element becomes the last one.
//rr : ra and rb at the same time.
//rra (reverse rotate a): Shift down all elements of stack a by 1.
//The last element becomes the first one.
//rrb (reverse rotate b): Shift down all elements of stack b by 1.
//The last element becomes the first one.
//rrr : rra and rrb at the same time.

void	init_stack(s_stack_node stack)
{
	stack->value = 0;
	stack->current_position = -1;
	stack->final_index = -1;
	stack->push_price = 0;
	stack->above_median = false;
	stack->cheapest = false;
	stack->target_node = NULL;
	stack->next = NULL;
	stack->prev = NULL;
}

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
		stack->index = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		i++; //++i
	}
}

void	set_target_a(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_b;
	t_stack_node	*target_node;
	long			match_index;

	while (a)
	{
		if (current_b->value < a->value && current_b->value > match_index)
		{
			match_index = current_b->value;
			target_node = current_b;
		}
		current_b = current_b->next;
	}
	if (match_index == LONG_MIN)
		a->target_node = find_max(b);
	else
		a->target_node = target_node;
	a = a->next;
}

void	cost_analysis_a(t_stack_node *a, t_stack_node *b)
{
	size_t len_a;
	size_t len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (a)
	{
		a->push_price = a->final_index;
		if (!(a->above_median))
			a->push_price = len_a - (a->final_index);
		if (a->target_node->above_median)
			a->push_price += a->target_node->final_index;
		else
			a->push_price +=len_b - (a->target_node->final_index);
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
		if (stack->push_price < cheapest_value)
		{
			cheapest_value = stack->push_price;
			cheapest_node = stack;
		}
		stack = stack->next;
	}
	cheapest_node->cheapest = true;

}

void	init_nodes_a(t_stack_node *a, t_stack_node *b)
{
	current_index(a);
	current_index(b);
	set_target_a(a, b);
	cost_analysis_a(a, b);
	set_cheapest(a);
}

void	sort_stacks(t_stack_node **a, t_stack_node **b)
{
	size_t	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a, false);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a, false);
	while (len_a-- > 3 !stack_sorted(*a))
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
	min_on_top(a);
}

void	sort_three(t_stack_node **a)
{
	t_stack_node	*biggest_node;

	biggest_node = find_max(*a);
	if (biggest_node == *a)
		ra(a, false)
	else if ((*a)->next == biggest_node)
		rra(a, false)
	if ((*a)->value > (*a)->next->value)
		sa(a, false)
}

bool	stack_sorted(t_stack_node *stack)
{
	if (!stack)
		return (false);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

t_stack_node	*find_min(s_stack_node *stack)
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

void	append_node(t_stack_node **stack, int value)
{
	t_stack_node	*new_node;
	t_stack_node	*last_node;

	if (!stack)
		return;
	new_node = malloc(sizeof(t_stack_node));
	if (!new_node)
		return;
	new_node->next = NULL;
	new_node->value = value;
	if (!(*stack))
	{
		*stack = new_node;
		new_node->prev = NULL;
	}
	else
	{
		last_node = find_last(*stack);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

void	init_stack_a(t_stack_node **a, char **av)
{
	long	value;
	int		i;

	i = 0;
	while (av[i])
	{
		if (error_sintax(av[i]))
			free_errors(a);
		value = atol(av[i]);
		if (value > INT_MAX || value < INT_MIN)
			free_errors(a);
		if (duplicate_value(*a, (int)value)) // int(value)
			free_errors(a);
		append_node(a, (int)value); //node add back
		i++;
}
}


int	main(int ac, char **av) {
	t_stack_node stack_a;
	t_stack_node stack_b;

	stack_a = NULL;
	stack_b = NULL;

	if (ac == 1 || (ac == 2 && !av[1][0]))
		return (1); //create error message
	else if (ac == 2)
		av = ft_split(av[1], ' ');
	init_stack_a(&stack_a, av + 1);
	if (!stack_sorted(stack_a))
	{
		if (stack_len(stack_a))
			sa(&stack_a, false);
		else if(stack_len(&stack_a == 3))
			sort_three(&stack_a);
		else
		sort_stacks(&stack_a, &stack_b);
	}
	free_stacks(&stack_a);
	return (0);
}

