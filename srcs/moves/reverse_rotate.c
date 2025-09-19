/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:30:20 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/18 14:54:47 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static void	rev_rotate_one(t_stack *stack)
{
	t_node	*node;

	if (stack->size <= 1)
		return ;
	node = stack_pop_bottom(stack);
	stack_push_top(stack, node);
}

void	rra(t_stack *a)
{
	rev_rotate_one(a);
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	rev_rotate_one(b);
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b)
{
	rev_rotate_one(a);
	rev_rotate_one(b);
	write(1, "rrr\n", 4);
}
