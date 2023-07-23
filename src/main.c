
#include "../include/pipex.h"



int main(int argc, char **argv, char **env)
{
    int		i;
	pid_t	last_pid;
	t_env   local_env;

	if (argc != 5)
		return (write(2, "Error!\n", 7), 1);
	i = 0;
	while (i < argc - 3 )
	{
		last_pid = fork();
		if (last_pid < 0)
			return (ft_putstr_fd("Aaaaalbannnn!\n", 2), 1);
		else if (last_pid == 0)
			ft_child(i, argv, env, pip);
		i++;
	}
	close(pip[0]);
	close(pip[1]);
    return 0;
}

