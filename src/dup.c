/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 21:04:29 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/05 21:17:52 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	ft_dup(int i, int fd[2], int pipe[2])
{
	if (!i)
	{
		if (dup2(fd[0], 0) < 0)
			return (write(2, "pipex : dup2 failed\n", 21), false);
		if (dup2(pipe[1], 1) < 0)
			return (write(2, "pipex : dup2 failed\n", 21), false);
	}
	else
	{
		if (dup2(pipe[0], 0) < 0)
			return (write(2, "pipex : dup2 failed\n", 21), false);
		if (dup2(fd[1], 1) < 0)
			return (write(2, "pipex : dup2 failed\n", 21), false);
	}
	return (ft_close(fd), ft_close(pipe), true);
}
