
#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>

typedef struct s_env
{
    char    **env;
    int     hd_status;
    int     pipeline[2][2];
}           t_env;

# endif