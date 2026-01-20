/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:05:37 by toandrad          #+#    #+#             */
/*   Updated: 2026/01/20 13:13:42 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static void	dispatch(t_stack *a, t_stack *b)
{
	if (a->size <= 1)
		return ;
	if (is_sorted(a))
		return ;
	if (a->size <= 3)
		sort3(a);
	else if (a->size <= 5)
		sort5(a, b);
	else
		turk_sort(a, b);
}

int	main(int ac, char **av)
{
	t_stack	a;
	t_stack	b;

	stack_init(&a);
	stack_init(&b);
	if (ac < 2)
		return (0);
	if (parse_args(ac, av, &a) == -1)
		return (error_exit(&a, &b));
	dispatch(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
