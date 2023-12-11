#include "../minishell.h"

void add_node_at_end(t_environment *head, char *key, char *value);
char *get_value_export(char *str);
char *get_key_export(char *str, char *value);
int	check_good_variable(char * str);
int builtin_export(t_commande *cmd_lst, t_environment *env_copy);
size_t get_current_size(t_environment *env_copy);
void bigger_tab(t_environment **env_copy, size_t size_factor);
void get_big_tab(t_environment **env_copy);
void search_empty_fill(t_environment *env_copy, char *key, char *value, int count_tab);

int env_count_env_copy(t_environment *env_copy);
t_environment *copy_env_bigger(t_environment *env_copy, int factor, int *count_struct);

void bigger_env_copy(t_environment **env_copy, int *count_tab);

//void get_big_tab(t_environment **env_copy)
//{
//	size_t size_current_tab = get_current_size(*env_copy);
//	bigger_tab(env_copy,size_current_tab);
//}
//size_t get_current_size(t_environment *env_copy)
//{
//	size_t current_size = 0;
//
//	while (env_copy[current_size].key != NULL && env_copy[current_size].value != NULL) {
//		++current_size;
//	}
//	return current_size;
//}
//void bigger_tab(t_environment **env_copy, size_t size_factor)
//{
//	size_t new_tab_size = (size_factor) * 2;
//
//	t_environment *new_tab = (t_environment *)malloc(new_tab_size * sizeof(t_environment));
//
//	if (new_tab != NULL) {
//		// Copiez les éléments existants dans le nouveau tableau
//		size_t i = 0;
//		while (i < size_factor) {
//			new_tab[i] = *env_copy[i];
//			++i;
//		}
//
//		// Libérez la mémoire de l'ancien tableau
//		free(*env_copy);
//
//		// Mettez à jour le pointeur et la taille
//		*env_copy = new_tab;
//		size_factor = new_tab_size;
//
//		// Initialisez les nouvelles parties du tableau si nécessaire
//		while (i < size_factor) {
//			env_copy[i]->key = NULL;
//			env_copy[i]->value = NULL;
//			++i;
//		}
//
//		printf("Tableau agrandi avec succès.\n");
//	} else {
//		fprintf(stderr, "Erreur lors de l'agrandissement du tableau.\n");
//	}
//}

int env_count_env_copy(t_environment *env_copy)
{
	int count = 0;
	while (env_copy[count].key != NULL)
		count++;
	printf("taillle de env %d\n", count);
	return count;
}

t_environment *copy_env_bigger(t_environment *env_copy, int factor, int *count_struct)
{
	int count = env_count_env_copy(env_copy);
	*count_struct = (count * factor);
	t_environment *new_env = malloc(sizeof(t_environment) * ((count * factor) + 1));

	if (new_env == NULL)
	{
		printf("Malloc failed bigger env\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (env_copy[i].key != NULL)
	{
		new_env[i].key = strdup(env_copy[i].key);
		new_env[i].value = strdup(env_copy[i].value);
		i++;
	}

	// remplie de vide les slot libre
	while (i < (count * factor))
	{
		new_env[i].key = NULL;
		new_env[i].value = NULL;
		i++;
	}

	new_env[count + factor].key = NULL;
	new_env[count + factor].value = NULL;

	return new_env;
}

void bigger_env_copy(t_environment **env_copy, int *count_tab)
{
	t_environment *temp = copy_env_bigger(*env_copy, 2, count_tab);
		free_env_struct(*env_copy);
		*env_copy = temp;
	printf("doooone it's bigger\n");

}

void change_value_key(char *key, char *new_value, t_environment *env_copy)
{
	if (key == NULL || env_copy == NULL) {
		// Gérer l'erreur ou retourner si key ou env_copy est NULL
		return;
	}

	int i = 0;
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, key) == 0)
		{
			if (env_copy[i].value != NULL)
			{
				free(env_copy[i].value); // Libérer l'ancienne valeur
			}
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

void search_empty_fill(t_environment *env_copy, char *key, char *value, int count_tab)
{
	int	i;
	i = 0;
	while (env_copy!= NULL && i < count_tab)
	{
		if ( (env_copy[i].key == NULL) && (env_copy[i].value == NULL))
		{
			env_copy[i].key = ft_strdup(key);
			env_copy[i].value = ft_strdup(value);
			printf("ona reussis a remplir le vide \n");
			return;
		}
		i++;
	}

	free(key);
	free(value);
}

int static check_args_export(t_commande *cmd_lst, t_environment *env_copy)
{
	t_commande *current = cmd_lst;
	int	i =0;
	int count_tab = 0;
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
			int j = 0;
			while (j <= i && current != NULL)
			{
				char *value = get_value_export(current->args->arg);
//				if (value == NULL)
//				{
//					printf("je suis value nuuuuuul\n");
//					//trigger a juste mettre la valeur du node existant a null ou juste en creer un..osef en vrai
//				}
				char *key = get_key_export(current->args->arg, value);
				printf("\nvoici la keyyy %s et voici la value : %s\n",key, value);
				if (key != NULL && check_good_variable(key) == ERROR)// extrait variable, avant = et check si que lettre
				{
					printf("ce n;est pas unn bonne varaible\n"); //plop=
					return (ERROR);
				}
				if (check_is_in_env(env_copy, key) == ERROR)
				{
					if (check_is_in_env(env_copy, "") == ERROR)// pas de slot vide
					{

						printf("i want a bigger train \n");
						//print_env(env_copy, 27);
						printf("\n");
						bigger_env_copy(&env_copy, &count_tab); // here
						printf("--------\n");
						//print_env(env_copy, 54);
						printf("\n");
						printf(" c'est moi qui ai la plus grosse\n");
						printf(" count tab %d\n", count_tab);
					}
					printf("on a trouvé une place de parc :)\n");
					search_empty_fill(env_copy, key, value, count_tab);  //11h50
					printf("--------\n");
					//print_env(env_copy, 54);
					return(SUCCESS);

				}
				else
				{
					printf("on va changer le papier peint\n");
					change_value_key(key, value, env_copy);
					//return(SUCCESS);

				}
				printf ("j'ai continue rtout droit\n");
				j++;
				current = current->next;
				value = NULL;
				free(key);
				key = NULL;
			}

		}
		else
		{
			printf("travail en cours \n");
			return (1);
		}
	}
	printf("j'ai finii\n");
	return (0);
}

int builtin_export(t_commande *cmd_lst, t_environment *env_copy)//, t_commande *cmd_lst
{

	if (check_args_export(cmd_lst, env_copy) == ERROR)
		return (ERROR);
	return (SUCCESS);
}