/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdolores <mdolores@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 12:47:03 by mariserr          #+#    #+#             */
/*   Updated: 2025/05/12 11:47:24 by mdolores         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "../libft.h"

static int	word_counter(char const *s, char c)
{
	int	w_count;
	int	i;

	w_count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			w_count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (w_count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	tab = (char **)malloc(sizeof (char *) * (word_counter(s, c) + 1));
	if (!s || !tab)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] != c && s[i])
			i++;
		if (i > j)
			tab[k++] = ft_substr(s, j, i - j);
	}
	tab[k] = NULL;
	return (tab);
}
/*
void    display_split_result(char **res)
{
    for (int i = 0; res[i] != NULL; i++)
    {
        printf("Mot %d: %s\n", i + 1, res[i]);
    }
}

void    test_ft_split()
{
    char const *test1 = "Petit test";
    char const *test2 = "    Petits tests  des  familles       ";
    char const *test3 = "Ceci,,,,,,,est,,un,,,test,,,";

    printf("Test 1 : '%s'\n", test1);
    printf("Test 2 : '%s'\n", test2);
    printf("Test 3 : '%s'\n\n", test3);

    char **res1 = ft_split(test1, ' ');
    char **res2 = ft_split(test2, ' ');
    char **res3 = ft_split(test3, ',');

    printf("Résultat pour test1:\n");
    display_split_result(res1);

    printf("\nRésultat pour test2:\n");
    display_split_result(res2);

    printf("\nRésultat pour test3:\n");
    display_split_result(res3);

    for (int i = 0; res1[i] != NULL; i++) free(res1[i]);
    for (int i = 0; res2[i] != NULL; i++) free(res2[i]);
    for (int i = 0; res3[i] != NULL; i++) free(res3[i]);
    free(res1);
    free(res2);
    free(res3);    
}

int    main(void)
{
    //Test de ft_split//
    printf("Testing ft_split:\n");
    test_ft_split();
    printf("\n");
}*/
