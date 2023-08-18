/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 13:47:37 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/11 12:40:38 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_exec(int i, char **argv, char **env)
{
	char	**cmd;
	char	**paths;
	char	*path;

	cmd = ft_split(argv[i + 2], ' ');
	if (!cmd)
		exit(1);
	if (ft_is_char_in_str(cmd[0]))
	{
		execve(cmd[0], cmd, env);
		ft_free_strs(cmd);
		exit(127);// voir minishell
	}
	if (!ft_get_paths(&paths, env))
		(ft_free_strs(cmd), exit(1));
	if (!ft_build_path(&path, cmd[0]))
		(ft_free_strs(cmd), ft_free_strs(paths), exit(1));
	execve(cmd[0], cmd, env);
	(ft_free_strs(cmd), ft_free_strs(paths), free(path));
	return (127);
}

void	ft_child(int i, char **argv, char **env, int pipe[2])
{
	int	fd[2];

	fd[0] = 0;
	fd[1] = 1;
	if (!ft_open(i, argv, fd))
		(ft_close(fd), ft_close(pipe), exit (1));
	if (!ft_dup(i, fd, pipe))
		(ft_close(fd), ft_close(pipe), exit (1));
	ft_exec(i, argv, env);
}

int	ft_exit_status(pid_t last_pid)
{
	pid_t	wpid;
	int		wstatus;
	int		return_status;

	while (true)
	{
		wpid = wait(&wstatus);
		if (wpid < 0)
			break ;
		if (wpid == last_pid)
		{
			if (WIFEXITED(wstatus))
				return_status = WEXITSTATUS(wstatus);
			else
				return_status = 128 + WTERMSIG(wstatus);
		}
	}
	return (return_status);
}

int main(int argc, char **argv, char **env)
{
    int		i;
	int		pip[2];
	pid_t	last_pid;

	if (argc != 5)
		return (write(2, "pipex : wrong number of argument\n", 34), 1);
	if (pipe(pip) < 0)
		return (write(2, "pipe failed\n", 13), 1);
	i = 0;
	while (i < 2)
	{
		last_pid = fork();
		if (last_pid < 0)
			return (write(2, "pipex : fork failed\n", 21), 1);
		else if (!last_pid)
			ft_child(i, argv, env, pip);
		i++;
	}
	close(pip[0]);
	close(pip[1]);
    return (ft_exit_status(last_pid));
}
