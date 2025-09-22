/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:50:11 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/22 13:41:31 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	get_max_bits(t_stack *a)
{
	int		max_num;
	int		bits;

	if (a->size == 0)
		return (0);
	max_num = a->size - 1;
	bits = 0;
	while ((max_num >> bits) != 0)
		bits++;
	return (bits);
}

static void	normalize_stack(t_stack *a)
{
	t_node	*cur;
	t_node	*cmp;
	int		rank;

	cur = a->top;
	while (cur)
	{
		rank = 0;
		cmp = a->top;
		while (cmp)
		{
			if (cmp->value < cur->value)
				rank++;
			cmp = cmp->next;
		}
		cur->value = rank;
		cur = cur->next;
	}
}

static void	process_bit(t_stack *a, t_stack *b, int bit, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (((a->top->value >> bit) & 1) == 0)
			pb(a, b);
		else
			ra(a);
		i++;
	}
	while (b->size > 0)
		pa(a, b);
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	bit;
	int	original_size;

	if (a->size <= 5)
		return ;
	normalize_stack(a);
	max_bits = get_max_bits(a);
	original_size = a->size;
	bit = 0;
	while (bit < max_bits)
	{
		process_bit(a, b, bit, original_size);
		bit++;
	}
}
