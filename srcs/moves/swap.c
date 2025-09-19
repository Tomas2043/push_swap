/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:08:04 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/18 14:54:37 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static void	swap_one(t_stack *stack)
{
	t_node	*n1;
	t_node	*n2;

	if (stack->size <= 1)
		return ;
	n1 = stack_pop_top(stack);
	n2 = stack_pop_top(stack);
	stack_push_top(stack, n1);
	stack_push_top(stack, n2);
}

void	sa(t_stack *a)
{
	swap_one(a);
	write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
	swap_one(b);
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
	swap_one(a);
	swap_one(b);
	write(1, "ss\n", 3);
}
