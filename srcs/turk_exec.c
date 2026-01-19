/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:47:50 by toandrad          #+#    #+#             */
/*   Updated: 2025/12/16 10:54:08 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static void	exec_both_rot(t_stack *a, t_stack *b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rr(a, b);
		(*ca)--;
		(*cb)--;
	}
	while ((*ca)-- > 0)
		ra(a);
	while ((*cb)-- > 0)
		rb(b);
}

static void	exec_both_rrot(t_stack *a, t_stack *b, int *ca, int *cb)
{
	while (*ca > 0 && *cb > 0)
	{
		rrr(a, b);
		(*ca)--;
		(*cb)--;
	}
	while ((*ca)-- > 0)
		rra(a);
	while ((*cb)-- > 0)
		rrb(b);
}

void	execute_moves(t_stack *a, t_stack *b, int tpos, int cidx)
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
