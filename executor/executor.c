char	*find_path(t_mini *mini, char **env)
{
	struct stat	buff;
	int			i;
	char		**base;
	char		*temp;
	char		*path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
	{
		i++;
	}
	base = ft_split((env[i] + 5), ':');
	i = -1;
	while (base && base[++i])
	{
		temp = ft_strjoin(base[i], "/");
		if (!lstat(ft_strjoin(temp, mini->toks[0]), &buff))
		{
			path = ft_strjoin(temp, mini->toks[0]);
			free(temp);
			return (path);
		}
	}
	free(temp);
	return (NULL);
}
