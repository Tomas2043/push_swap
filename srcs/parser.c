/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:27:56 by toandrad          #+#    #+#             */
/*   Updated: 2025/09/22 12:31:56 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	safe_atoi(const char *s, int *out)
{
	long	sign;
	long	res;
	int		i;

	i = 0;
	sign = 1;
	res = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	if (!s[i])
		return (-1);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (-1);
		res = res * 10 + (s[i] - '0');
		if (sign * res > INT_MAX || sign * res < INT_MIN)
			return (-1);
		i++;
	}
	*out = (int)(sign * res);
	return (0);
}

static int	has_dup(t_stack *a, int v)
{
	t_node	*cur;

	cur = a->top;
	while (cur)
	{
		if (cur->value == v)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static int	push_value(t_stack *a, const char *tok)
{
	int		v;
	t_node	*n;

	if (safe_atoi(tok, &v) == -1)
		return (-1);
	if (has_dup(a, v))
		return (-1);
	n = node_new(v);
	if (!n)
		return (-1);
	stack_push_bottom(a, n);
	return (0);
}

static int	parse_split_arg(t_stack *a, char *arg)
{
	char	**parts;
	int		j;

	if (!arg[0])
		return (-1);
	parts = ft_split(arg, ' ');
	if (!parts)
		return (-1);
	j = 0;
	while (parts[j])
	{
		if (push_value(a, parts[j]) == -1)
		{
			while (parts[j])
				free(parts[j++]);
			free(parts);
			return (-1);
		}
		j++;
	}
	j = 0;
	while (parts[j])
		free(parts[j++]);
	free(parts);
	return (0);
}

int	parse_args(int ac, char **av, t_stack *a)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (parse_split_arg(a, av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
