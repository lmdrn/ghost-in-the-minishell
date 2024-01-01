#include "../minishell.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void no_arg_so_print_env_exports(t_environment **env_copy, int nb_args)
{
	if (nb_args == 0)
	{
		bubble_sort_env(env_copy); // Mettre à jour env_copy
		print_sorted_env(*env_copy);
	}
}

//
//void no_arg_so_print_env_exports(t_environment *env_copy, int nb_args)
//{
//	t_environment *env_tmp;
//	if (nb_args == 0)
//	{
//		printf("Avant le tri :\n");
//		print_sorted_env(env_copy);
//		printf("\n");
//
//		env_tmp = bubble_sort_env(env_copy);
//
//		printf("Après le tri (env_tmp) :\n");
//		print_sorted_env(env_tmp);
//		printf("\n");
//
//		env_copy = env_tmp;
//
//		printf("Après la mise à jour de env_copy :\n");
//		print_sorted_env(env_copy);
//		printf("\n");
//	}
//}


int need_swap(t_environment *a, t_environment *b)
{
	// Vérifie si l'une des clés est NULL et gère ce cas
	if (a->key == NULL || b->key == NULL)
	{
		if (a->key == NULL && b->key != NULL)
		{
			return 1; // Considérer NULL comme inférieur à toute chaîne non-NULL
		}
		if (a->key != NULL && b->key == NULL)
		{
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

//swap d'origin
// void swap_nodes(t_environment **prevNodeNext, t_environment *current, t_environment *next)
//{
//	*prevNodeNext = next;
//	current->next = next->next;
//	next->next = current;
//}

void swap_nodes(t_environment *a, t_environment *b)
{
	// Échanger les valeurs key et value
	char *temp_key = a->key;
	char *temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}



//
//t_environment *bubble_sort_env(t_environment *head)
//{
//	int swapped;
//	t_environment *current;
//	t_environment *prev = NULL;
//	t_environment *temp_head = head;
//
//	if (head == NULL)
//		return NULL;
//
//	do {
//		swapped = 0;
//		current = temp_head;
//		prev = NULL;
//
//		while (current->next != NULL) {
//			if (need_swap(current, current->next)) {
//				// Échanger les nœuds
//				t_environment *temp = current->next;
//				current->next = temp->next;
//				temp->next = current;
//
//				// Ajuster le pointeur précédent
//				if (prev == NULL)
//					temp_head = temp;
//				else
//					prev->next = temp;
//
//				swapped = 1;
//				prev = temp; // Mettre à jour le pointeur précédent après l'échange
//			} else {
//				prev = current;
//				current = current->next;
//			}
//		}
//	} while (swapped);
//
//	return temp_head; // Retourner la nouvelle tête de la liste
//}

//
//t_environment *bubble_sort_env(t_environment *head)
//{
//	int             swapped;
//	t_environment   **current;
//	t_environment   *temp_head;
//
//	if (head == NULL)
//		return NULL;
//	swapped = 1;
//	while (swapped)
//	{
//		swapped = 0;
//		temp_head = head;
//		current = &temp_head;
//		while ((*current)->next != NULL)
//		{
//			if (need_swap(*current, (*current)->next))
//			{
//				swap_nodes(current, *current, (*current)->next);
//				swapped = 1;
//			}
//			current = &(*current)->next;
//		}
//	}
//	return (temp_head);
//}


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
				swap_nodes( *current, (*current)->next);
				swapped = 1;
			}
			current = &(*current)->next;
		}
	}
	printf("liste triée \n");
}


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

int fill_env(t_commande *cmd_lst, t_environment **env_copy, int nb_args)
{
	t_commande *current = cmd_lst;
	char *key;
	char *value;
	int exist;
	if (nb_args == 0)
	{
		return(SUCCESS);
	}
	while (nb_args != 0)
	{
		value = get_value_export(current->args->arg);
		key = get_key_export(current->args->arg);
		exist = if_exist_in_env(key, *env_copy); // Use *env_copy here

		if (exist == -1) // need space
		{
			printf("new_node ajouté\n");
			add_node(env_copy, key, value); // Directly pass env_copy
		}
		else
		{
			remplace_old_value(value, key, *env_copy); // Use *env_copy here
		}
		nb_args--;
		if(nb_args != 0)
			cmd_lst = cmd_lst->next;
	}
	return (ERROR); // Consider returning SUCCESS if the function completes normally
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
			{
				printf("mauvais arguments\n");
				return (-1);
			}
			current = current->next;
		}
		return count;
	}
}

int export_main(t_commande *cmd_lst, t_environment **env_copy)
{
	int nb_args;

	nb_args = count_args_export(cmd_lst);
	if (nb_args == -1)
	{
		printf("erreur nb_args\n");
		return (ERROR);
	}
//	printf("in export main = %p\n", *env_copy);



	// Pass the pointer to the no_arg_so_print_env_exports function
	no_arg_so_print_env_exports(env_copy, nb_args);
	// Pass the pointer to the fill_env function
	fill_env(cmd_lst, env_copy, nb_args);


	return (SUCCESS);
}
