/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:36:58 by toandrad          #+#    #+#             */
/*   Updated: 2025/05/30 16:31:18 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ptr_recursive(unsigned long long ptr);

int	ft_putptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	len += ft_putstr("0x");
	len += ft_ptr_recursive(ptr);
	return (len);
}

static int	ft_ptr_recursive(unsigned long long ptr)
{
	int		len;
	char	*hex;

	len = 0;
	hex = "0123456789abcdef";
	if (ptr >= 16)
		len += ft_ptr_recursive(ptr / 16);
	len += ft_putchar(hex[ptr % 16]);
	return (len);
}
