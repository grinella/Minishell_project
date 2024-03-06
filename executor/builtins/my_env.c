#include "../include/minishell.h"

char	*get_env_char(char *var, char **envp, int n)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i] != NULL)
	{
		if (n < 0)
		{
			if (strncmp(envp[i], var, strlen(var)) == 0) // If a match is found, get the substring after the equal sign
			{
				value = strchr(envp[i], '=');
				if (value != NULL)
					return (value + 1); // Return the substring after the equal sign
			}
		}
		else // If n is non-negative, compare the first n characters
		{
			if (strncmp(envp[i], var, n) == 0) // If a match is found, get the substring after the equal sign
			{
				value = strchr(envp[i], '=');
				if (value != NULL)
					return (value + 1); // Return the substring after the equal sign
			}
		}
		i++;
	}
	return (NULL);// Return NULL if the environment variable is not found
}

/*int main() {
	char *env[] = {"VAR1=value1", "VAR2=value2", "VAR3=value3", NULL};
	char *result = get_env_char("VAR2", env, -1);
	if (result != NULL) {
		printf("Environment variable value: %s\n", result);
	} else {
		printf("Environment variable not found\n");
	}
	return 0;
}*/

char	**set_env(char *var, char *value, char **envp, int n)
{
	int		i;
	char	*new_entry;
	int		count;
	char	**new_envp;

	i = 0;
	count = 0;
	if (n < 0)
	{
		n = strlen(var);
	}
	// Create auxiliary strings by joining the variable name and value with '='
	new_entry = ft_calloc(strlen(var) + strlen(value) + 2);
	strcpy(new_entry, var);
	strcat(new_entry, "=");
	strcat(new_entry, value);
	// Count the number of entries in the original environment variable array
	while (envp[count] != NULL)
	{
		count++;
	}
	// Create a new environment variable array with one additional entry
	new_envp = ft_calloc((count + 2) * sizeof(char *));
	if (new_envp == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	// Copy the original environment variable entries to the new array using a while loop
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (new_envp[i] == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// Add the new entry to the new environment variable array
	new_envp[count] = new_entry;
	new_envp[count + 1] = NULL;
	return (new_envp);
}

void	my_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

/*int main() {
	char *env[] = {"VAR1=Value1", "VAR2=Value2", NULL};
	char **new_env = set_env("VAR3", "Value3", env, -1);
	int i = 0;
	while (new_env[i] != NULL) {
		printf("%s\n", new_env[i]);
		i++;
	}
	i = 0;
	while (new_env[i] != NULL) {
		free(new_env[i]);
		i++;
	}
	free(new_env);

	return 0;
}*/