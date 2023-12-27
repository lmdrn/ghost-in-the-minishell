#include "../minishell.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void no_arg_so_print_env_exports(t_environment *env_copy, int nb_args)
{
	(void)env_copy;
	if (nb_args == 0)
	{
		bubble_sort_env(&env_copy);
		print_sorted_env(env_copy);
		//printf("je n'ai aucune argument\n");
	}
}

int need_swap(t_environment *a, t_environment *b) {
	// Vérifie si l'une des clés est NULL et gère ce cas
	if (a->key == NULL || b->key == NULL) {
		if (a->key == NULL && b->key != NULL) {
			return 1; // Considérer NULL comme inférieur à toute chaîne non-NULL
		}
		if (a->key != NULL && b->key == NULL) {
			return 0; // Considérer toute chaîne non-NULL comme supérieure à NULL
		}
		return 0; // Si les deux clés sont NULL, ne pas échanger
	}

	// Votre logique existante
	int swap = strcmp(a->key, b->key) > 0;
	return swap;
}

//int need_swap(t_environment *a, t_environment *b)
//{
//	int swap = strcmp(a->key, b->key) > 0;
//	return swap;
//}

void swap_nodes(t_environment **prevNodeNext, t_environment *current, t_environment *next)
{
	*prevNodeNext = next;
	current->next = next->next;
	next->next = current;
}

void	bubble_sort_env(t_environment **head)
{
	int				swapped;
	t_environment	**current;

	if (*head == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while ((*current)->next != NULL)
		{
			if (need_swap(*current, (*current)->next))
			{
				swap_nodes(current, *current, (*current)->next);
				swapped = 1;
			}
			current = &(*current)->next;
		}
	}
}

//void print_sorted_env(t_environment *env_copy)
//{
//	t_environment *current = env_copy;
//
//	while (current->next != NULL)
//	{
//
//		if (current->key != NULL && current->value == NULL )
//			printf("%s\n", current->key);
//		else if (current->key != NULL && current->value != NULL )
//			printf("%s=%s\n", current->key, current->value);
//		current = current->next;
//	}
//}
void print_sorted_env(t_environment *env_copy)
{
	t_environment *current = env_copy;

	while (current != NULL)  // Modifié pour inclure le dernier nœud
	{
		if (current->key != NULL)
		{
			if (current->value == NULL)
			{
				printf("%s\n", current->key);
			} else
			{
				printf("%s=%s\n", current->key, current->value);
			}
		}
		current = current->next;
	}
}


int print_normal_variable(t_environment *env_copy, int size_env, char *minus, char *maj)
{
	int	i;
	int env_checked;
	t_environment *current;

	i = 0;
	env_checked = 0;
	while ((i < 26) && (env_checked < size_env))
	{
		current = env_copy;
		while (current != NULL)
		{
			if (current->key != NULL && (current->key[0] == minus[i] || current->key[0] == maj[i]))
			{
				printf("%s=%s\n", current->key, current->value);
				env_checked++;
			}
			current = current->next;
		}
		i++;
	}
	return (env_checked);
}

int ft_strchrint(char *s, char c)
{
	unsigned char	letter;
	int				i;

	i = 0;
	letter = c;
	while ((s[i] != '\0') && (s[i] != letter))
		i++;
	if (s[i] == letter)
		return (i);
	return (0);
}
char *get_value_export(char *str)
{
	char *res;
	int equal;

	if (str == NULL)
		return (NULL);
	equal = ft_strchrint(str, '=');
	if (equal == 0)
		return (NULL);
	if (str[equal + 1] == '\0')
		return (ft_strdup("\"\""));
	res = ft_strdup(&str[equal + 1]);
	return (res);
}

char *get_key_export(char *str)
{
	char	*res;
	int		equal;
	int		i;

	if (str == NULL)
		return (NULL);
	equal = ft_strchrint(str, '=');

	if (equal == 0)
		return (str);
	res = malloc(sizeof(char) * equal + 1);
	i = 0;
	while(equal > 0)
	{
		res[i] = str[i];
		i++;
		equal--;
	}
	res[i] = '\0';
	return (res);
}

int valid_cmd(char *arg)
{
	int i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
		{
			i++;
			break;
		}
		if (!ft_isalpha(arg[i]))
		{
			return (ERROR);
		}
		i++;
	}
	while (arg[i] != '\0')
	{
		if (!ft_isalpha(arg[i]) && !ft_isdigit(arg[i]))
		{
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

//void no_arg_so_print_env_exports(t_environment *env_copy, int nb_args, int size_env)
//{
//	if (nb_args == 0)
//		print_env_order_alpha(env_copy, size_env);
//}

int if_exist_in_env(char *key, t_environment *env_origin)
{

	t_environment *current;

	if(key == NULL)
		return (ERROR);
	current = env_origin;

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (SUCCESS);
		current= current->next;
	}
	return (-1);
}

void remplace_old_value(char *value, char *key, t_environment *env_copy)
{
	t_environment *current = env_copy;

	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (current->value != NULL)
				free(current->value);
			current->value = strdup(value);
			if (current->value == NULL )
			{
				fprintf(stderr, "Erreur d'allocation mémoire pour les champs key ou value\n");
				exit(EXIT_FAILURE);
			}
		}
		current = current->next;

	}
}

int fill_env(t_commande *cmd_lst, t_environment *env_copy, int nb_args) // *env_copy
{
	t_commande *current = cmd_lst;
	char *key;
	char *value;
	int exist;
	if (nb_args == 0)
	{
		//printf("c'est fini\n");
		return(SUCCESS);
	}
	while (nb_args != 0)
	{
		value = get_value_export(current->args->arg);
		key = get_key_export(current->args->arg);
		exist = if_exist_in_env(key, env_copy);

		if (exist == -1) // need space
			add_node(&env_copy, key, value);
		else
		{
			remplace_old_value(value, key, env_copy);
		}
		nb_args--;
		if( nb_args != 0)
			cmd_lst = cmd_lst->next;
	}
	return (ERROR);
}



int count_args_export(t_commande *cmd_lst)
{
	{
		int count;
		t_args *current;

		count = 0;
		current = cmd_lst->args;
		while (current != NULL) {
			count++;
			if (valid_cmd(current->arg) == ERROR)
				return (-1);
			current = current->next;
		}
		return count;
	}
}

int export_main(t_commande *cmd_lst, t_environment *env_copy)
{
	(void)cmd_lst;
	(void)env_copy;

		int nb_args;

	nb_args = count_args_export(cmd_lst);
	if (nb_args == -1)
		return (ERROR);
	no_arg_so_print_env_exports(env_copy, nb_args);
	fill_env(cmd_lst, env_copy, nb_args);
	return (SUCCESS);
}
