
#include "../include/pipex.h"

void    ft_memcpy(char *dest, char *src, int i)
{
    int j;

    if (src < dest)
    {
        j = 0;
        while (j < i)
        {
            dest[j] = src[j];
            j++;
        }
    }
    else
    {
        while (i)
        {
            dest[i] = src[i];
            i--;
        }
    }
}

// option 0 -> on ne free rien
// option 1 -> free le left
// option 2 -> free le right
// option 3 -> free le left et le right
bool	ft_strjoin(char **pablo, char *left, char *right, int option)
{
	int len_left;
	int len_right;

	if (!left || !right)
		return (true);
	len_left = ft_strlen(left);
	len_right = ft_strlen(right);
	*pablo = malloc(len_left + len_right + 1);
	if (!*pablo)
		return (false);
	ft_memcpy(*pablo, left, len_left);
	ft_memcpy(*pablo + len_left, left, len_right + 1);
	if (option & 1)
		free(left);
	if (option & 2)
		free(right);
	return (true);
}
