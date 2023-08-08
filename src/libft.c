/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:56:59 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/08 16:41:19 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str && str[i])
        i++;
    return (i);
}

void    ft_memcpy(char *dest, char *src, int i)
{
    int j;

    if (!dest || !src)
        return ;
    if (src < dest)
    {
        j = 0;
        while (j < i)
        {
            dest[j] = src[j];
            j++;
        }
    }
    else
    {
        while (i)
        {
            dest[i] = src[i];
            i--;
        }
    }
}

bool    ft_is_char_in_str(char c, char *str)
{
    if (str)
    {
        while (*str)
        {
            if (*str == c)
                return (true);
            str++;
        }
    }
    return (false);
}

// option 0 -> on ne free rien
// option 1 -> free le left
// option 2 -> free le right
// option 3 -> free le left et le right
bool	ft_strjoin(char **dest, char *left, char *right, int option)
{
	int len_left;
	int len_right;

	if (!left || !right)
		return (write(2, "strjoin : we cant join NULL\n", 29), true);
	len_left = ft_strlen(left);
	len_right = ft_strlen(right);
	*dest = malloc(len_left + len_right + 1);
	if (!*dest)
		return (false);
	ft_memcpy(*dest, left, len_left);
	ft_memcpy(*dest + len_left, left, len_right + 1);
	if (option & 1)
		free(left);
	if (option & 2)
		free(right);
	return (true);
}
