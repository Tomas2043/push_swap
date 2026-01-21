/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:47:50 by toandrad          #+#    #+#             */
/*   Updated: 2026/01/21 13:34:45 by toandrad         ###   ########.fr       */
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

static void	exec_both_rrot(t_stack *a, t_stack *b, int *cost_a, int *cost_b)
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

void	execute_moves(t_stack *a, t_stack *b, int target_pos, int cheap_idx)
{
	int	cost_ra;
	int	cost_rra;
	int	cost_rb;
	int	cost_rrb;

	cost_ra = target_pos;
	cost_rra = a->size - target_pos;
	cost_rb = cheap_idx;
	cost_rrb = b->size - cheap_idx;
	if (cost_ra <= cost_rra && cost_rb <= cost_rrb)
		exec_both_rot(a, b, &cost_ra, &cost_rb);
	else if (cost_rra < cost_ra && cost_rrb < cost_rb)
		exec_both_rrot(a, b, &cost_rra, &cost_rrb);
	else
	{
		rotate_to_position_a(a, target_pos);
		rotate_to_position_b(b, cheap_idx);
	}
}
