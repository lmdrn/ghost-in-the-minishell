#include "../minishell.h"

void print_env_builtin(t_environment  *env_copy)
{
	int                i;
	i = 0;
	if (env_copy!= NULL)
	{
		while (env_copy[i].key != NULL)
		{
			printf("%s=%s", env_copy[i].key, env_copy[i].value);
			if (env_copy[i + 1].key != NULL)
				printf("\n");
			i++;
		}
	} else
		return;

}