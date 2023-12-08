#include "../minishell.h"

void add_node_at_end(t_environment *head, char *key, char *value);
char *get_value_export(char *str);
char *get_key_export(char *str, char *value);
int	check_good_variable(char * str);
int builtin_export(t_commande *cmd_lst, t_environment *env_copy);

void change_value_key(char *key, char *new_value, t_environment *env_copy)
{
	int	i;

	i = 0;
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, key) == 0)
		{
			free(env_copy[i].value); // Libérer l'ancienne valeur
			env_copy[i].value = ft_strdup(new_value);
			break;
		}
		i++;
	}
}

size_t  ft_strcspn(const char *s, const char *reject)
{
	int     i = 0;
	int     j = 0;

	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if(s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
#include <stddef.h>
#include <stdlib.h>
int	check_good_variable(char *str)
{
	while (*str)
	{
		if (!ft_isalpha(*str))
			return (ERROR);
		str++;
	}
	return (SUCCESS);
}
char *ft_strndup(const char *src, size_t n)
{
	size_t i = 0;
	while (src[i] != '\0' && i < n) {
		i++;
	}

	char *dest = (char *)malloc(i + 1);
	if (dest == NULL) {
		return NULL;
	}

	i = 0;
	while (src[i] != '\0' && i < n) {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return dest;
}
char *get_value_export(char *str)
{
	char *result;
	result = (strchr(str, '=')+1);
	if (str != NULL)
		if (result == NULL)
			return NULL;
	return(result);
}
char *get_key_export(char *str, char *value)
{
	if (str != NULL && value != NULL)
	{
		// Calcule la longueur de la sous-chaîne avant le délimiteur
		size_t key_length = value - (str + 1);// pour enelever le =

		// Utilise ft_strndup pour créer une copie de la sous-chaîne
		return (ft_strndup(str, key_length) );
	}

	return NULL;
}


int static check_args_export(t_commande *cmd_lst, t_environment *env_copy)
{
	t_commande *current = cmd_lst;
	int	i =0;
	if (current != NULL)
	{

		t_args *args = current->args;
		while (args != NULL)
		{
			i++;
			args = args->next;
		}
		if (i == 0)
		{
			print_env_builtin(env_copy);
			return(SUCCESS);
		}
		if (i == 1) // plusieurs varaible init
		{
			printf("je suis ici\n");
			int j = 0;
			while (j <= i && current != NULL)
			{
				printf("je suis dans la bouuuucle\n");
				char *value = get_value_export(current->args->arg);
				if (value == NULL)
				{
					printf("je suis value nuuuuuul\n");
					//trigger a juste mettre la valeur du node existant a null ou juste en creer un..osef en vrai
				}
				printf(" et laaaaaa\n");
				char *key = get_key_export(current->args->arg, value);
				printf("voici la keyyy %s et voici la value : %s\n",key, value);
				if (check_good_variable(key) == ERROR)// extrait variable, avant = et check si que lettre
				{
					printf("ce n;est pas unn bonne varaible\n"); //plop=
					return (ERROR);
				}
				if (check_is_in_env(env_copy, key) == ERROR)
				{
					printf("node a rajouter la varaible existe pas\n");
					add_node_at_end(head, key, value);
				}
				else
				{
					//printf("on va changer le papier peint\n");
					change_value_key(key, value, env_copy);

				}
//				printf ("j'ai continue rtout droit\n");
				j++;
				current = current->next;
				value = NULL;
				free(key);
				key = NULL;
			}

		}
		else
		{
			//printf("travail en cours \n");
			return (1);
		}



	}
	//printf("j'ai finii\n");
	return (0);
}

int builtin_export(t_commande *cmd_lst, t_environment *env_copy)//, t_commande *cmd_lst
{

	if (check_args_export(cmd_lst, env_copy) == ERROR)
		return (ERROR);
	return (SUCCESS);
}