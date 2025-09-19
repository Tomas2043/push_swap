/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 09:56:27 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/19 10:11:15 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	top_val(t_stack *s)
{
	return (s->top->value);
}

static int	mid_val(t_stack *s)
{
	return (s->top->next->value);
}

static int	bot_val(t_stack *s)
{
	return (s->bottom->value);
}

void	sort3(t_stack *a)
{
	int	t;
	int	m;
	int	b;

	if (a->size <= 1)
		return ;
	if (a->size == 2)
	{
		if (top_val(a) > mid_val(a))
			sa(a);
		return ;
	}
	t = top_val(a);
	m = mid_val(a);
	b = bot_val(a);
	if (t > m && t > b)
		ra(a);
	else if (m > t && m > b)
		rra(a);
	if (top_val(a) > mid_val(a))
		sa(a);
}
