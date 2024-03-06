/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:23:52 by fde-alen          #+#    #+#             */
/*   Updated: 2024/03/06 20:37:31 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "../libs/libft/libft.h"
# include "../libs/ft_printf/ft_printf.h"

typedef struct s_stack_node
{
	int					value;
	int					position;
	int					total_moves;
	bool				is_above_median;
	bool				is_optimal_move;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}	t_stack_node;

//***Handle errors
bool			is_valid_number(char *str_n);
bool			has_duplicate(t_stack_node *a, int n);
void			free_stack(t_stack_node **stack);
void			exit_with_error(t_stack_node **a, bool print);

//***Sort utils
void			rotate_both(t_stack_node **a, t_stack_node **b,
					t_stack_node *optimal_node);
void			rev_rotate_both(t_stack_node **a, t_stack_node **b,
					t_stack_node *optimal_node);
t_stack_node	*get_optimal_node(t_stack_node *stack);
void			set_positions(t_stack_node *stack);
void			rotate_min_to_top(t_stack_node **a);

//***Stack initiation
void			populate_stack_a(t_stack_node **a, char **argv);
void			add_node_back(t_stack_node **stack, int n);
void			init_node(t_stack_node *stack);



//***Nodes initiation
void			prepare_stack_a(t_stack_node *a, t_stack_node *b);
void			prepare_stack_b(t_stack_node *a, t_stack_node *b);
void			set_positions(t_stack_node *stack);
void			set_optimal_move(t_stack_node *stack);
t_stack_node	*get_optimal_node(t_stack_node *stack);
void			rotate_until_target_top(t_stack_node **stack,
					t_stack_node *target_node, char stack_name);

//***Stack utils
int				stack_len(t_stack_node *stack);
t_stack_node	*find_last(t_stack_node *stack);
bool			is_stack_sorted(t_stack_node *stack);
t_stack_node	*get_min_value_node(t_stack_node *stack);
t_stack_node	*get_max_value_node(t_stack_node *stack);

//***Commands
void			swap(t_stack_node **stack);
void			sa(t_stack_node **a);
void			sb(t_stack_node **b);
void			ss(t_stack_node **a, t_stack_node **b);
void			rotate(t_stack_node **stack);
void			ra(t_stack_node **a);
void			rb(t_stack_node **b);
void			rr(t_stack_node **a, t_stack_node **b);
void			reverse_rotate(t_stack_node **stack);
void			rra(t_stack_node **a);
void			rrb(t_stack_node **b);
void			rrr(t_stack_node **a, t_stack_node **b);
void			push(t_stack_node **dest, t_stack_node **src);
void			pa(t_stack_node **a, t_stack_node **b);
void			pb(t_stack_node **b, t_stack_node **a);

//***Algorithm
void			sort_three_nodes(t_stack_node **a);
void			sort_stack_a(t_stack_node **a, t_stack_node **b);

#endif