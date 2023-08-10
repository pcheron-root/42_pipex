
#include "../include/pipex.h"

bool    ft_env_init(int argc, char **argv, char **env, t_env *local_env)
{
    local_env->env = env;
    if (!strncmp(argv[1], "here_doc", 9))
    {
        local_env->hd_status = 1;
        if (!ft_)
    }
    return (true);
}

int main(int argc, char **argv, char **env)
{
    t_env   local_env;

    if (argc < 5)
		return (write(2, "pipex : need more arguments\n", 34), 1);
    if (!ft_env_init(argc, argv, env))
        return (1);
}


