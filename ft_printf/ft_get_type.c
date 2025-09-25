/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:16:00 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 17:02:38 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_u(long n)
{
	int	counter;

	counter = 0;
	if (n > 9)
	{
		counter += ft_put_u(n / 10);
		counter += ft_put_u(n % 10);
	}
	if (n >= 0 && n <= 9)
		counter += ft_put_char(n + 48);
	if (counter < 0)
		return (-1);
	return (counter);
}

int	ft_put_x(unsigned int n, int type)
{
	char	*letter;

	if (type == 'x')
		letter = "0123456789abcdef";
	else
		letter = "0123456789ABCDEF";
	return (ft_put_hexa(n, letter));
}

int	ft_put_hexa(unsigned long n, char *letter)
{
	int	counter;

	counter = 0;
	if (n >= 16)
	{
		counter += ft_put_hexa(n / 16, letter);
		counter += ft_put_hexa(n % 16, letter);
	}
	else
		counter += ft_put_char(letter[n]);
	if (counter < 0)
		return (-1);
	return (counter);
}

int	ft_put_p(void *arg)
{
	int				counter;
	char			*letter;
	unsigned long	arg2;

	counter = 0;
	letter = "0123456789abcdef";
	arg2 = (unsigned long) arg;
	counter += ft_put_str("0x");
	counter += ft_put_hexa(arg2, letter);
	return (counter);
}

int	ft_get_type(char type, va_list args)
{
	int	counter;

	counter = 0;
	if (type == 'c')
		counter += ft_put_char(va_arg(args, int));
	if (type == 's')
		counter += ft_put_str(va_arg(args, char *));
	if (type == 'd' || type == 'i')
		counter += ft_put_nbr(va_arg(args, int));
	if (type == 'u')
		counter += ft_put_u(va_arg(args, unsigned int));
	if (type == 'p')
		counter += ft_put_p(va_arg(args, void *));
	if (type == 'x' || type == 'X')
		counter += ft_put_x(va_arg(args, int), type);
	if (type == '%')
		counter += ft_put_char('%');
	return (counter);
}
