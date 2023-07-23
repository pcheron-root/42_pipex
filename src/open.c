
bool	ft_open_infile(int	*fd, char *file)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		return (false);// utiliser perror
	return (true);
}

bool	ft_open_outfile(int	*fd, char *file)
{
	*fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (*fd < 0)
		return (false);// utiliser perror
	return (true);
}

bool	ft_open(int i, char **argv, int	fds[2])
{
	if (!i)
		return (ft_open_infile(&(fds[0]), argv[1]));
	else
		return (ft_open_outfile(&(fds[1]), argv[4]));
}
