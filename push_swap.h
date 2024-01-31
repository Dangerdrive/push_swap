//
// Created by fde-alen on 1/24/24.
//

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef enum e_bool
{
	false = 0,
	true = 1
} bool;

typedef struct	s_stack_node
{
	int                 value;
	int                 current_position;
	int                 final_index;
	int                 push_price;
	bool                above_median;
	bool                cheapest;
	struct s_stack_node *target_node;
	struct s_stack_node *next;
	struct s_stack_node *prev;
}				t_stack_node;

#endif // PUSH_SWAP_H