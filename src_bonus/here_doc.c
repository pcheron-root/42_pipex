/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:35:43 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/08 16:47:39 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static unsigned long	ft_get_random_nbr(void)
{
	static unsigned long	x = 42;

	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return (x);
}

char	*ft_random_file_generator(void)
{
	unsigned char	buffer[8];
	int				fd;
	unsigned long	nbr;
	char			*file_name;
	char			*dest;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		nbr = ft_get_random_nbr();
	else
	{
		read(fd, buffer, 8);
		close(fd);
		ft_memcpy(&nbr, buffer, 8);
	}
	file_name = ft_itoa(nbr);
	if (!file_name)
		return (NULL);
	if (!ft_strjoin(&dest, "/tmp/heredoc_", file_name, 2))
		return (NULL);
	return (dest);
}

bool	ft_get_random_name(t_env *env)
{
	while (1)
	{
		env->hd_name = ft_random_file_generator();
		if (!env->hd_name)
			return (false);
		if (access(env->hd_name, F_OK))
			break ;
		free(env->hd_name);
	}
	return (true);
}

bool	ft_get_here_doc(char **argv, t_env *env)
{
	int			fd;
	char		*line;
	static int	i = 1;

	if (!ft_get_random_name(env))
		return (write(2, "here_doc : allocation failed\n", 30), false);
	fd = open(env->hd_name, O_WRONLY | O_CREAT, 0774);
	if (fd == -1)
		return (free(env->hd_name), write(2, "pipex : here_doc creation failed\n", 34), false);
	while ("jusqu'ici tout va bien")
	{
		write(0, "> ", 2);// ca risque de cassser un truc
		line = ft_get_next_line(0);
		if (!ft_strncmp(line, argv[2], ft_strlen(argv[2])) && line[ft_strlen(argv)] == '\n')
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
		i++;
	}
	return (close(fd), true);
}
