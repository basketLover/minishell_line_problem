/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:36:20 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:45:15 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

static int	int_counter(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i += 1;
		nb *= (-1);
	}
	if (nb < 10)
		return (1 + i);
	else
		return (1 + i + int_counter(nb / 10));
}

static char	*ft_memory_dest(int len)
{
	char	*mem_dest;

	mem_dest = (char *) malloc ((len +1) * sizeof (char));
	if (!mem_dest)
		return (NULL);
	mem_dest[0] = '0';
	return (mem_dest);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		len;
	long	nb;

	nb = n;
	len = int_counter(nb);
	result = ft_memory_dest(len);
	if (!result)
		return (NULL);
	if (nb < 0)
		nb *= (-1);
	i = len - 1;
	while (nb != 0)
	{
		result[i] = ((nb % 10) + 48);
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		result[0] = '-';
	result[len] = '\0';
	return (result);
}
/*
int main()
{
	int n = -147483;
	void *result = ft_itoa(n);
	printf("%s\n", result);;
	free(result);
	return (0);
}*/
