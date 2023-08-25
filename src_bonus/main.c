
#include "../include/pipex.h"

bool    ft_env_init(int argc, char **argv, char **env, t_env *local_env)
{
    local_env->env = env;
    if (!strncmp(argv[1], "here_doc", 9))
    {
		if (argc < 6)
			return (write(2, "pipex : need more arguments\n", 34), false);
        local_env->hd_status = 1;
        if (!ft_)// remplire le hd
    }
    return (true);
}

void	ft_exec(int i, char **argv, t_env *env)
{
	char	**cmd;
	char	**paths;
	char	*path;

	cmd = ft_split(argv[i + 2 + env->hd_status], ' '); // modifier en splitbool
	if (!cmd)
		exit(1);
	if (ft_is_char_in_str(cmd[0]))//
	{
		execve(cmd[0], cmd, env);
		ft_free_strs(cmd);
		exit(127);// voir minishell
	}
	if (!ft_get_paths(&paths, env->env))
		(ft_free_strs(cmd), exit(1));
	if (!ft_build_path(&path, cmd[0]))
		(ft_free_strs(cmd), ft_free_strs(paths), exit(1));
	execve(cmd[0], cmd, env->env);
	(ft_free_strs(cmd), ft_free_strs(paths), free(path)); // + free les trucs de l'env
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
    t_env   local_env;
	pid_t	last_pid;
	int		i;

    if (argc < 5)
		return (write(2, "pipex : need more arguments\n", 34), 1);
    if (!ft_env_init(argc, argv, env, &local_env))
        return (1);
	i = 0;
	while (i < argc - 3 - local_env.hd_status)
	{
		if (argv[i + 4 + local_env.hd_status])	// en gros c'est "si il y a une commande apres moi"
			pipe(local_env.pipeline[i % 2]);	// j'ouvre une pipe
		last_pid = fork();
		if (!last_pid)
			ft_child(argc, argv, local_env);
		if (i)												// "si il y a une commande avant moi"
			ft_close_pipe(local_env.pipeline[(i - 1) % 2]);	// je ferme la pipe precedente
		i++;
	}
    return (ft_exit_status(last_pid));
}


