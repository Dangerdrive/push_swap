

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

// void	init_stack(t_stack_node stack)
// {
// 	stack->value = 0;
// 	stack->current_position = -1;
// 	stack->final_index = -1;
// 	stack->push_price = 0;
// 	stack->above_median = false;
// 	stack->cheapest = false;
// 	stack->target_node = NULL;
// 	stack->next = NULL;
// 	stack->prev = NULL;
// }
/*movements*/

void	rr(t_stack_node **a, t_stack_node **b, bool print)
{
	rotate(a);
	rotate(b);
	if (!print)
		ft_printf("rr\n");
}

void	rotate_both(t_stack_node **a, t_stack_node **b,
	t_stack_node *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rr(a, b, false);
	current_index(*a);
	current_index(*b);
}

void	prep_for_push(t_stack_node **stack, t_stack_node *top_node,
	char stack_name)
{
	while (*stack != top_node)
	{
		if (stack_name == 'a')
		{
			if (top_node->above_median)
				ra(stack, false);
			else
				rra(stack, false);
		}
		else if (stack_name == 'b')
		{
			if (top_node->above_median)
				rb(stack, false);
			else
				rrb(stack, false);
		}
	}
}

void	move_a_to_b(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = get_cheapest(*a);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		rev_rotate_both(a, b, cheapest_node);
	prep_for_push(a, cheapest_node, 'a');
	prep_for_push(b, cheapest_node->target_node, 'b');
	pb(b, a, false);
}

void	move_b_to_a(t_stack_node **a, t_stack_node **b)
{
	prep_for_push(a, (*b)->target_node, 'a');
	pa(a, b, false);
}

void	min_on_top(t_stack_node **a)
{
	while ((*a)->value != find_min(*a)->value)
	{
		if (find_min(*a)->above_median)
			ra(a, false);
		else
			rra(a, false);
	}
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
		stack->current_position = i; //curent_position or final_index?
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

void	set_target_b(t_stack_node *a, t_stack_node *b)
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
			b->target_node = find_min(a);
		else
			b->target_node = target_node;
		b = b->next;
	}

}

void	cost_analysis_a(t_stack_node *a, t_stack_node *b)
{
	size_t	len_a;
	size_t	len_b;

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
			a->push_price += len_b - (a->target_node->final_index);
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

void	init_nodes_b(t_stack_node *a, t_stack_node *b)
{
	current_index(a);
	current_index(b);
	set_target_b(a, b);
}

void	sort_stacks(t_stack_node **a, t_stack_node **b)
{
	size_t	len_a;

	len_a = stack_len(*a);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a, false);
	if (len_a-- > 3 && !stack_sorted(*a))
		pb(b, a, false);
	while (len_a-- > 3 && !stack_sorted(*a))
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
		ra(a, false);
	else if ((*a)->next == biggest_node)
		rra(a, false);
	if ((*a)->value > (*a)->next->value)
		sa(a, false);
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

t_stack_node	*find_min(t_stack_node *stack)
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
	t_stack_node *stack_a;
	t_stack_node *stack_b;

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



/*
gcc push_swap.c                                                                                             fde-alen@c2r12p1
push_swap.c:47:2: warning: implicit declaration of function 'rotate' is invalid in C99 [-Wimplicit-function-declaration]
        rotate(a);
        ^
push_swap.c:58:2: warning: implicit declaration of function 'current_index' is invalid in C99 [-Wimplicit-function-declaration]
        current_index(*a);
        ^
push_swap.c:70:5: warning: implicit declaration of function 'ra' is invalid in C99 [-Wimplicit-function-declaration]
                                ra(stack, false);
                                ^
push_swap.c:72:5: warning: implicit declaration of function 'rra' is invalid in C99 [-Wimplicit-function-declaration]
                                rra(stack, false);
                                ^
push_swap.c:77:5: warning: implicit declaration of function 'rb' is invalid in C99 [-Wimplicit-function-declaration]
                                rb(stack, false);
                                ^
push_swap.c:79:5: warning: implicit declaration of function 'rrb' is invalid in C99 [-Wimplicit-function-declaration]
                                rrb(stack, false);
                                ^
push_swap.c:88:18: warning: implicit declaration of function 'get_cheapest' is invalid in C99 [-Wimplicit-function-declaration]
        cheapest_node = get_cheapest(*a);
                        ^
push_swap.c:88:16: warning: incompatible integer to pointer conversion assigning to 't_stack_node *' (aka 'struct s_stack_node *') from 'int' [-Wint-conversion]
        cheapest_node = get_cheapest(*a);
                      ^ ~~~~~~~~~~~~~~~~
push_swap.c:93:3: warning: implicit declaration of function 'rev_rotate_both' is invalid in C99 [-Wimplicit-function-declaration]
                rev_rotate_both(a, b, cheapest_node);
                ^
push_swap.c:96:2: warning: implicit declaration of function 'pb' is invalid in C99 [-Wimplicit-function-declaration]
        pb(b, a, false);
        ^
push_swap.c:102:2: warning: implicit declaration of function 'pa' is invalid in C99 [-Wimplicit-function-declaration]
        pa(a, b, false);
        ^
push_swap.c:107:24: warning: implicit declaration of function 'find_min' is invalid in C99 [-Wimplicit-function-declaration]
        while ((*a)->value != find_min(*a)->value)
                              ^
push_swap.c:107:38: error: member reference type 'int' is not a pointer
        while ((*a)->value != find_min(*a)->value)
                              ~~~~~~~~~~~~  ^
push_swap.c:109:21: error: member reference type 'int' is not a pointer
                if (find_min(*a)->above_median)
                    ~~~~~~~~~~~~  ^
push_swap.c:110:4: warning: implicit declaration of function 'ra' is invalid in C99 [-Wimplicit-function-declaration]
                        ra(a, false);
                        ^
push_swap.c:112:4: warning: implicit declaration of function 'rra' is invalid in C99 [-Wimplicit-function-declaration]
                        rra(a, false);
                        ^
push_swap.c:116:6: error: conflicting types for 'current_index'
void    current_index(t_stack_node *stack)
        ^
push_swap.c:58:2: note: previous implicit declaration is here
        current_index(*a);
        ^
push_swap.c:124:11: warning: implicit declaration of function 'stack_len' is invalid in C99 [-Wimplicit-function-declaration]
        median = stack_len(stack) / 2;
                 ^
push_swap.c:153:20: warning: implicit declaration of function 'find_max' is invalid in C99 [-Wimplicit-function-declaration]
                a->target_node = find_max(b);
                                 ^
push_swap.c:153:18: warning: incompatible integer to pointer conversion assigning to 'struct s_stack_node *' from 'int' [-Wint-conversion]
                a->target_node = find_max(b);
                               ^ ~~~~~~~~~~~
push_swap.c:180:21: warning: implicit declaration of function 'find_min' is invalid in C99 [-Wimplicit-function-declaration]
                        b->target_node = find_min(a);
                                         ^
push_swap.c:180:19: warning: incompatible integer to pointer conversion assigning to 'struct s_stack_node *' from 'int' [-Wint-conversion]
                        b->target_node = find_min(a);
                                       ^ ~~~~~~~~~~~
push_swap.c:193:10: warning: implicit declaration of function 'stack_len' is invalid in C99 [-Wimplicit-function-declaration]
        len_a = stack_len(a);
                ^
push_swap.c:249:10: warning: implicit declaration of function 'stack_len' is invalid in C99 [-Wimplicit-function-declaration]
        len_a = stack_len(*a);
                ^
push_swap.c:250:22: warning: implicit declaration of function 'stack_sorted' is invalid in C99 [-Wimplicit-function-declaration]
        if (len_a-- > 3 && !stack_sorted(*a))
                            ^
push_swap.c:251:3: warning: implicit declaration of function 'pb' is invalid in C99 [-Wimplicit-function-declaration]
                pb(b, a, false);
                ^
push_swap.c:259:2: warning: implicit declaration of function 'sort_three' is invalid in C99 [-Wimplicit-function-declaration]
        sort_three(a);
        ^
push_swap.c:269:6: error: conflicting types for 'sort_three'
void    sort_three(t_stack_node **a)
        ^
push_swap.c:259:2: note: previous implicit declaration is here
        sort_three(a);
        ^
push_swap.c:273:17: warning: implicit declaration of function 'find_max' is invalid in C99 [-Wimplicit-function-declaration]
        biggest_node = find_max(*a);
                       ^
push_swap.c:273:15: warning: incompatible integer to pointer conversion assigning to 't_stack_node *' (aka 'struct s_stack_node *') from 'int' [-Wint-conversion]
        biggest_node = find_max(*a);
                     ^ ~~~~~~~~~~~~
push_swap.c:275:3: warning: implicit declaration of function 'ra' is invalid in C99 [-Wimplicit-function-declaration]
                ra(a, false);
                ^
push_swap.c:277:3: warning: implicit declaration of function 'rra' is invalid in C99 [-Wimplicit-function-declaration]
                rra(a, false);
                ^
push_swap.c:279:3: warning: implicit declaration of function 'sa' is invalid in C99 [-Wimplicit-function-declaration]
                sa(a, false);
                ^
push_swap.c:282:6: error: conflicting types for 'stack_sorted'
bool    stack_sorted(t_stack_node *stack)
        ^
push_swap.c:250:22: note: previous implicit declaration is here
        if (len_a-- > 3 && !stack_sorted(*a))
                            ^
push_swap.c:295:15: error: conflicting types for 'find_min'
t_stack_node    *find_min(t_stack_node *stack)
                 ^
push_swap.c:107:24: note: previous implicit declaration is here
        while ((*a)->value != find_min(*a)->value)
                              ^
push_swap.c:334:15: warning: implicit declaration of function 'find_last' is invalid in C99 [-Wimplicit-function-declaration]
                last_node = find_last(*stack);
                            ^
push_swap.c:334:13: warning: incompatible integer to pointer conversion assigning to 't_stack_node *' (aka 'struct s_stack_node *') from 'int' [-Wint-conversion]
                last_node = find_last(*stack);
                          ^ ~~~~~~~~~~~~~~~~~
push_swap.c:348:7: warning: implicit declaration of function 'error_sintax' is invalid in C99 [-Wimplicit-function-declaration]
                if (error_sintax(av[i]))
                    ^
push_swap.c:349:4: warning: implicit declaration of function 'free_errors' is invalid in C99 [-Wimplicit-function-declaration]
                        free_errors(a);
                        ^
push_swap.c:353:7: warning: implicit declaration of function 'duplicate_value' is invalid in C99 [-Wimplicit-function-declaration]
                if (duplicate_value(*a, (int)value)) // int(value)
                    ^
push_swap.c:375:7: warning: implicit declaration of function 'stack_len' is invalid in C99 [-Wimplicit-function-declaration]
                if (stack_len(stack_a))
                    ^
push_swap.c:376:4: warning: implicit declaration of function 'sa' is invalid in C99 [-Wimplicit-function-declaration]
                        sa(&stack_a, false);
                        ^
push_swap.c:377:30: warning: comparison between pointer and integer ('t_stack_node **' (aka 'struct s_stack_node **') and 'int') [-Wpointer-integer-compare]
                else if(stack_len(&stack_a == 3))
                                  ~~~~~~~~ ^  ~
push_swap.c:382:2: warning: implicit declaration of function 'free_stacks' is invalid in C99 [-Wimplicit-function-declaration]
        free_stacks(&stack_a);
        ^
38 warnings and 6 errors generated.
*/