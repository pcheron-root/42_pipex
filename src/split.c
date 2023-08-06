/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 21:33:23 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/05 21:38:46 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static int	ft_count_word(char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			j++;
		}
		if (j > 0)
			k++;
		while (s[i] && s[i] == c)
			i++;
	}
	return (k);
}

static int	ft_word_len(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		j++;
	}
	return (j);
}

static char	**ft_split2(char const *s, char **strs, char c, int i)
{
	int	j;
	int	k;

	j = 0;
	while (j < ft_countw(s, c))
	{
		strs[j] = malloc(sizeof(char) * (ft_word_len(s, c, i) + 1));
		if (!strs[j])
			return (ft_free_strs(strs), NULL);
		k = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			strs[j][k] = s[i];
			i++;
			k++;
		}
		strs[j][k] = '\0';
		j++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;

	if (!s)
		return (write(2, "split : we cant split NULL\n", 28), NULL);
	strs = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	return (ft_split2(s, strs, c, i));
}
