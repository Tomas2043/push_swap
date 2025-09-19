/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:04:24 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/19 12:10:50 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	count_nodes(t_stack *s)
{
	t_node	*cur;
	int		n;

	cur = s->top;
	n = 0;
	while (cur)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}

static int	check_bidirectional(t_stack *s)
{
	t_node	*cur;
	t_node	*prev;

	prev = NULL;
	cur = s->top;
	while (cur)
	{
		if (cur->prev != prev)
			return (0);
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

int	stack_check_integrity(t_stack *s, const char *label)
{
	(void)label;
	if (!s)
		return (0);
	if (s->size == 0 && (s->top || s->bottom))
		return (write(2, "Integrity: empty mismatch\n", 26), 0);
	if (s->size > 0 && (!s->top || !s->bottom))
		return (write(2, "Integrity: null end\n", 20), 0);
	if (s->top && s->top->prev)
		return (write(2, "Integrity: top prev\n", 20), 0);
	if (s->bottom && s->bottom->next)
		return (write(2, "Integrity: bottom next\n", 23), 0);
	if (count_nodes(s) != s->size)
		return (write(2, "Integrity: size mismatch\n", 25), 0);
	if (!check_bidirectional(s))
		return (write(2, "Integrity: broken links\n", 24), 0);
	return (1);
}
