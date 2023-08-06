/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 09:43:51 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/23 09:59:24 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	ft_build_path(char **dest, char *file, char **possible_paths)
{
	int	i;

	i = 0;
	while (possible_paths[i])
	{
		if (!ft_strjoin(dest, file, "/", 0))
			return (false);
		if (!ft_strjoin(dest, *dest, file, 1))
			return (false);
		i++;
		if (!access(*dest, F_OK | X_OK))
			return (true);
	}
	return (true);
}

bool	ft_get_paths(char ***dest, char **env)
{
	int	i;

	i = 0;
	*dest = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			*dest = ft_split(env[i] + 5, ':');
			if (!*dest)
				return (false);
			return (true);
		}
		i++;
	}
	return (true);
}
