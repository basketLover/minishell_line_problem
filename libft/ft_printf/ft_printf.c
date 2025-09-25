/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariserr <mariserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:41:13 by mariserr          #+#    #+#             */
/*   Updated: 2024/01/23 12:50:34 by mariserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_char(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_put_str(char *str)
{
	int	counter;

	counter = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[counter])
	{
		write(1, &str[counter], 1);
		counter++;
	}
	if (counter < 0)
		return (-1);
	return (counter);
}

int	ft_put_nbr(int n)
{
	int	counter;

	counter = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		counter = 11;
	}
	else if (n < 0)
	{
		counter += write(1, "-", 1);
		n *= (-1);
		counter += ft_put_nbr(n);
	}
	else if (n > 9)
	{
		counter += ft_put_nbr(n / 10);
		counter += ft_put_nbr(n % 10);
	}
	else
		counter += ft_put_char(n + 48);
	if (counter < 0)
		return (-1);
	return (counter);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			i++;
			counter += ft_get_type(string[i], args);
		}
		else
			counter += ft_put_char(string[i]);
		i++;
	}
	va_end(args);
	if (counter < 0)
		return (-1);
	return (counter);
}
