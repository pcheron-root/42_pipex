
#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_env
{
    char    **env;
    int     hd_status;
    int     fd[2];
    int     pipeline[2][2];
}           t_env;

# endif