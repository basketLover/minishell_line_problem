/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:11:20 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:48:37 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((start > s_len) && (len + start) > (s_len))
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	subs = (char *) malloc ((len + 1) * sizeof (char));
	if (subs == NULL)
		return (NULL);
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
/*
int	main()
{
	void *str= ft_substr("I love Basketball", 2, 8);
	printf("%s\n", str);
	return (0);
	free(str);
}*/
