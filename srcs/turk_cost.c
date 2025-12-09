/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 11:12:51 by toandrad          #+#    #+#             */
/*   Updated: 2025/10/06 11:17:34 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	calculate_rotation_cost(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	else
		return (size - pos);  
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
