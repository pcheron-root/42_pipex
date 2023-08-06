/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:51:09 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/05 21:10:50 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

bool	ft_open_infile(int	*fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		write(2, "pipex : ", 9);
		write(2, file, ft_strlen(file));
		write(2, " : ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (false);
	}
	return (true);
}

bool	ft_open_outfile(int	*fd, char *file)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (*fd < 0)
	{
		write(2, "pipex : ", 9);
		write(2, file, ft_strlen(file));
		write(2, " : ", 3);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (false);
	}
	return (true);
}

bool	ft_open(int i, char **argv, int	fds[2])
{
	if (!i)
		return (ft_open_infile(&(fds[0]), argv[1]));
	else
		return (ft_open_outfile(&(fds[1]), argv[4]));
}

void	ft_close(int fd[2])
{
	if (fd[0] > 2)
	{
		close(fd[0]);
		fd[0] = 0;
	}
	if (fd[1] > 2)
	{
		close(fd[0]);
		fd[1] = 0;
	}
}
