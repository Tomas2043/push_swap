/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:09:23 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/18 14:54:42 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static void	rotate_one(t_stack *stack)
{
	t_node	*node;

	if (stack->size <= 1)
		return ;
	node = stack_pop_top(stack);
	stack_push_bottom(stack, node);
}

void	ra(t_stack *a)
{
	rotate_one(a);
	write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
	rotate_one(b);
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
	rotate_one(a);
	rotate_one(b);
	write(1, "rr\n", 3);
}
