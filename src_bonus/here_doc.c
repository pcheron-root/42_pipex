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
