#include "../minishell.h"
int check_is_in_env(t_environment *env_copy, char *var);
void add_node_at_end(t_environment *head, char *key, char *value);
char *get_value_export(char *str);
char *get_key_export(char *str);
int	check_good_variable(char * str);// check que si lettre et avec le =

char *get_key_export(char *str)
{

}
int static check_args_export(t_commande *cmd_lst, t_environment *env_copy)
{
	t_commande *current = cmd_lst;
	int	i =0;
	if (current != NULL)
	{

		t_args *args = current->args;
		while (current.args[i] != NULL)
		{
			i++;
		}
		if (i == 0)
		{
			print_env_builtin(env_copy);
		}
		if (i >= 1)
		{
			int j = 0
			while (i >= j)
			{
				if (check_good_variable(current.args[j]) == ERROR)
					return (ERROR);
				value = get_value_export(current.args[j]);
				key = get_key_export(current.args[j])
				add_node_at_end(env_copy, key, value);
				j--;
				value = NULL;
				key = NULL;
			}
		}


	}
}

int builtin_export(t_environment *env_copy)//, t_commande *cmd_lst
{
	char *var;
	var = NULL;

	check_is_in_env(env_copy, var);
	return (0);
}