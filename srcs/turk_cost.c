/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:12:51 by toandrad          #+#    #+#             */
/*   Updated: 2025/12/15 15:22:45 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static void	exec_both_rot(t_stack *a, t_stack *b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		rr(a, b);
		(*cost_a)--;
		(*cost_b)--;
	}
	while ((*cost_a)-- > 0)
		ra(a);
	while ((*cost_b)-- > 0)
		rb(b);
}

static void exec_both_rrot(t_stack *a, t_stack *b, int *cost_a, int *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		rrr(a, b);
		(*cost_a)--;
		(*cost_b)--;
	}
	while ((*cost_a)-- > 0)
		rra(a);
	while ((*cost_b)-- > 0)
		rrb(b);
}

static void execute_moves(t_stack *a, t_stack *b, int tpos, int cidx)
{
	int	cost_ra;
	int	cost_rra;
	int	cost_rb;
	int	cost_rrb;

	cost_ra = tpos;
	cost_rra = a->size - tpos;
	cost_rb = cidx;
	cost_rrb = b->size - cidx;
	if (cost_ra <= cost_rra && cost_rb <= cost_rrb)
		exec_both_rot(a, b, &cost_ra, &cost_rb);
	else if (cost_rra < cost_ra && cost_rrb < cost_rb)
		exec_both_rrot(a, b, &cost_rra, &cost_rrb);
	else
	{
		rotate_to_position_a(a, tpos);
		rotate_to_position_b(b, cidx);
	}
}

void	push_cheapest_to_a(t_stack *a, t_stack *b)
{
	int	cheapest_index;
	int	b_value;
	int	target_pos;

	cheapest_index = find_cheapest_index(a, b);
	b_value = get_b_value_at_index(b, cheapest_index);
	target_pos = find_target_pos_in_a(a, b_value);
	execute_moves(a, b, target_pos, cheapest_index);
	pa(a, b);
}

int	calculate_cost(t_stack *a, t_stack *b, int b_index)
{
	int	b_value;
	int	target_pos_a;
	int	cost_b;
	int	cost_a;

	b_value = get_b_value_at_index(b, b_index);
	if (b_value == INT_MAX)
		return (INT_MAX);
	target_pos_a = find_target_pos_in_a(a, b_value);
	cost_b = calculate_rotation_cost(b_index, b->size);
	cost_a = calculate_rotation_cost(target_pos_a, a->size);
	return (cost_a + cost_b);
}
