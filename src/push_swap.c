

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




int	main(int ac, char **av) {
	t_stack_node stack_a;
	t_stack_node stack_b;

	stack_a = NULL;
	stack_b = NULL;

	if (ac == 1 || (ac == 2 && !av[1][0]))
		return (1); //create error message
	else if (ac == 2)
		av = ft_split(av[1], ' ');
	init_stack_a(&stack_a, av + 1)
	if (!stack_sorted(stack_a)) {
		if (stack_len(stack_a))
			sa(&stack_a, false);
		else_if(stack_len(stack_a == 3))
		sort_three(&stack_a);
		else
		sort_stacks(&stack_a, &stack_b)
	}
	free_stacks(&stack_a);
	return (0);
}

