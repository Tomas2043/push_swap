/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:15:01 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/19 10:57:16 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	find_min_pos(t_stack *s)
{
	int		pos;
	int		minv;
	int		i;
	t_node	*cur;

	if (s->size == 0)
		return (-1);
	pos = 0;
	i = 0;
	minv = s->top->value;
	cur = s->top;
	while (cur)
	{
		if (cur->value < minv)
		{
			minv = cur->value;
			pos = i;
		}
		cur = cur->next;
		i++;
	}
	return (pos);
}

static void	rotate_to_top(t_stack *s, int pos)
{
	int	steps;

	if (pos < 0 || pos >= s->size)
		return ;
	if (pos <= s->size / 2)
	{
		while (pos--)
			ra(s);
	}
	else
	{
		steps = s->size - pos;
		while (steps--)
			rra(s);
	}
}

static void	push_min_to_b(t_stack *a, t_stack *b)
{
	int	pos;

	pos = find_min_pos(a);
	rotate_to_top(a, pos);
	pb(a, b);
}

void	sort4(t_stack *a, t_stack *b)
{
	push_min_to_b(a, b);
	sort3(a);
	pa(a, b);
}

void	sort5(t_stack *a, t_stack *b)
{
	if (a->size <= 3)
	{
		sort3(a);
		return ;
	}
	if (a->size == 4)
	{
		sort4(a, b);
		return ;
	}
	push_min_to_b(a, b);
	push_min_to_b(a, b);
	sort3(a);
	if (b->size == 2 && b->top->value < b->top->next->value)
		sb(b);
	pa(a, b);
	pa(a, b);
}
