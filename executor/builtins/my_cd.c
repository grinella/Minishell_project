#include "../../include/minishell.h"

char	*get_env(char *search, t_mini *mini)
{
	int i;
	int	search_len;

	search_len = ft_strlen(search);
	i = 0;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], search, search_len) == 0)
			return (mini->env[i] + search_len + 1);
		i++;
	}
	return (NULL);
}

char	**ft_realloc(char **mtr_old, char *str, int size)
{
	char **mtr_new;
	int i;

	mtr_new = malloc(sizeof(char*) * (size));
	i = 0;
	while (i < size)
	{
		printf("realloc\n");
		if(mtr_old[i])
		{
			mtr_new[i] = mtr_old[i];
			free(mtr_old[i]);
		}
		else
			mtr_new[i] = str;
		i++;
	}
	free_matrix(mtr_old);
	mtr_new[i] = NULL;
	return (mtr_new);
}

void	set_pwd(char *old, char *new, t_mini *mini)
{
	int i;

	i = 0;
	while (mini->env[i])
	{
		printf("while 1\n");
		if (ft_strncmp(mini->env[i], "PWD=", 4) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("PWD=", new);
			break ;
		}
		else
			i++;
	}
	printf("OLIVER BEARMANNNN \n");
	i = 0;
	while (mini->env[i])
	{
		usleep(500);
		printf("while 2\n");
		if (ft_strncmp(mini->env[i], "OLDPWD=", 7) == 0)
		{
			printf("sto freando e riassegnando\n");
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("OLDPWD=", old);
			break ;
		}
		else
			i++;
	}
	printf("fine while 2\n");
	if (mini->env[i] == NULL)
		mini->env = ft_realloc(mini->env, ft_strjoin("OLDPWD=", old), sizeof(char*) * (i + 1));
}

void	my_cd(t_mini *mini, t_toks *toks)
{
	char	*oldpwd;

	if (toks->word[1] == NULL)
	{
		printf("solo cd");
		oldpwd = getcwd(0, 0);
		chdir(get_env("HOME", mini));
		set_pwd(oldpwd, get_env("HOME", mini), mini); //reset PWD and OLDPWD in env matrix
	}
	else if (toks->word[1] && chdir(toks->word[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", toks->word[1]);
		g_exit_status = 1;
	}
	else
	{
		oldpwd = getcwd(0, 0);
		printf("old pwd %s\n", oldpwd);
		chdir(toks->word[1]);
		set_pwd(oldpwd, getcwd(0, 0), mini);
	}
}
