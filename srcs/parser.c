/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:27:56 by toandrad          #+#    #+#             */
/*   Updated: 2025/12/03 12:26:38 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/push_swap.h"

static int	safe_atoi(const char *s, int *result)
{
	long	sign;
	long	value;
	int		i;

	i = 0;
	sign = 1;
	value = 0;
	if (s[i] == '+' || s[i] == '-')
		if (s[i++] == '-')
			sign = -1;
	if (!s[i])
		return (-1);
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (-1);
		value = value * 10 + (s[i] - '0');
		if (sign * value > INT_MAX || sign * value < INT_MIN)
			return (-1);
		i++;
	}
	*result = (int)(sign * value);
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

static int	validate_and_push(t_stack *a, const char *token)
{
	int		value;
	t_node	*node;

	if (safe_atoi(token, &value) == -1)
		return (-1);
	if (has_dup(a, value))
		return (-1);
	node = node_new(value);
	if (!node)
		return (-1);
	stack_push_bottom(a, node);
	return (0);
}

static int	parse_arg(t_stack *a, char *arg)
{
	char	**tokens;
	int		j;

	if (!arg[0])
		return (-1);
	tokens = ft_split(arg, ' ');
	if (!tokens)
		return (-1);
	j = 0;
	while (tokens[j])
	{
		if (validate_and_push(a, tokens[j]) == -1)
		{
			while (tokens[j])
				free(tokens[j++]);
			free(tokens);
			return (-1);
		}
		j++;
	}
	j = 0;
	while (tokens[j])
		free(tokens[j++]);
	free(tokens);
	return (0);
}

int	parse_args(int ac, char **av, t_stack *a)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (parse_arg(a, av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
