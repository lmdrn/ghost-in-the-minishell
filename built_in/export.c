#include "../minishell.h"

void	just_replace_value(char *value, int index, t_environment *env_copy);
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

void more_space_env(t_environment **pEnvironment, t_var *pVar);

/*------- Check arguments--------*/

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

/*------- Lecture et check env--------*/
void print_env_export(t_environment *env_copy, int size_filled)
{
	if (env_copy == NULL) {
		printf("Env is empty or invalid.\n");
		return;
	}

	int i = 0;
	while (i <= size_filled && env_copy[i].key != NULL)
	{
		printf("Key: %s, Value: %s", env_copy[i].key, env_copy[i].value);

		if (i < size_filled - 1 && env_copy[i + 1].key != NULL)
		{
			printf("\n");
		}

		i++;
	}
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

int count_args_export(t_commande *cmd_lst) {
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

void no_arg_so_print_env_exports(t_environment *env_copy, int nb_args, int size_filled)
{
	if (nb_args == 0)
		print_env_export(env_copy, size_filled);
}

void double_env(t_environment **env_copy, int size_total, int factor)
{
	size_total *= factor;
	t_environment	*new_env;
	int i;

	new_env = malloc(sizeof(t_environment) * (size_total + 1));
	if (new_env == NULL)
	{
		printf("Malloc failed bigger env\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	if (*env_copy != NULL)
	{
		while ((*env_copy)[i].key != NULL && (*env_copy)[i].value != NULL) {
			new_env[i].key = strdup((*env_copy)[i].key);
			new_env[i].value = strdup((*env_copy)[i].value);
			i++;
		}
		while (i < size_total)
		{
			new_env[i].key = strdup("ghostintheminishellwegotit");
			new_env[i].value = strdup("ghostintheminishellwegotit");
			i++;
		}

		new_env[size_total].key = NULL;
		new_env[size_total].value = NULL;
//		free(*env_copy); // Libère l'ancien tableau
		*env_copy = new_env; // Met à jour le pointeur
	}
	return ;
}

int 	fill_slot(char *key, char *value, t_environment *env_copy, int index, int size_filled_env)
{
	int current_index ; // on a arreté index jusqu'a tout filled..

	current_index = index +1 ; // va au prochain qui doit etre vide () en theorie
	if ((env_copy)[current_index].key != NULL && env_copy[current_index].value != NULL)
	{
		free((env_copy)[current_index].key);   // Libère l'ancienne clé si elle existe
		free((env_copy)[current_index].value); // Libère l'ancienne valeur si elle existe

		(env_copy)[current_index].key = strdup(key);
		(env_copy)[current_index].value = strdup(value);
		return(size_filled_env + 1);
	}
	return(ERROR);



}

int if_exist_in_env(char *key, t_environment *env_origin, int size)
{
	int i;
	t_environment *env_copy;

	if(key == NULL)
		return (-1);
	env_copy = env_origin;
	i = 0;
	while (size > 0)
	{
		if (strcmp(env_copy[i].key, key) == 0)
			return (i);
		i++;
		size--;
	}
	return (-1);
}

void remplace_old_value(char *value, int index, t_environment **env_copy)
{
	printf("USER env = %s\n", (*env_copy)[index].key);
	if ((*env_copy)[index].key != NULL || ft_strcmp((*env_copy)[index].value, "\"\"") == 0)
		free((*env_copy)[index].value);
	(*env_copy)[index].value = strdup(value);
}

int	create_more_space (t_environment **env_copy, int size_total)
{
	double_env(env_copy, size_total, 2);
	return (SUCCESS);
}

int check_env_is_full();

int fill_env(t_commande *cmd_lst, t_environment *env_copy, int nb_args, int size_filled_env, int size_total)
{
	t_commande *current = cmd_lst;
	char *key;
	char *value;
	int index;

	while (nb_args != 0)
	{
		value = get_value_export(current->args->arg);
		key = get_key_export(current->args->arg);
		index = if_exist_in_env(key, env_copy, size_filled_env);
		printf("index = %d\n", index);
		printf("value = %s\n", value);
		if (index != -1)
		{
			if (size_filled_env < size_total)
				size_filled_env = fill_slot(key, value, env_copy, index, size_filled_env);
			if (size_filled_env == size_total)
				create_more_space(&env_copy, size_total);
		}
		else
			remplace_old_value(value, index, &env_copy);
		if (key != NULL)
		{
			free(key);
			key = NULL;
		}
		if(value != NULL)
		{
			free(value);
			value = NULL;
		}
		nb_args--;
	}
	return (ERROR);
}

int calculate_sizes_filled(t_environment *env_copy)
{
	int count = 0;

	if (env_copy != NULL)
	{
		while ((env_copy)[count].key != NULL && (env_copy)[count].value != NULL &&
			   strcmp((env_copy)[count].key, "ghostintheminishellwegotit") != 0 &&
			   strcmp((env_copy)[count].value, "ghostintheminishellwegotit") != 0)
		{
			count++;
		}
	}

	return count;
}

int calculate_size_env(t_environment *env_copy)//size total
{
	int count;

	count = 0;
	while (env_copy[count].key != NULL)
		count++;
	return (count);
}
void printCommandList(t_commande *cmdList) {
	t_commande *current = cmdList;

	while (current != NULL) {
		printf("Command: %s\n", current->cmd);

		// Imprimer les arguments
		t_args *args = current->args;
		while (args != NULL) {
			printf("  Arg: %s\n", args->arg);
			args = args->next;
		}


		printf("\n");

		// Passer à la commande suivante dans la liste
		current = current->next;
	}
}

int export_main(t_commande *cmd_lst, t_environment **env_copy)
{

	int nb_args;
//	int valid_args;
	int size_filled_env;
	int size_total;

//	printf("\n avant :export_main =  %s\n\n", cmd_lst->args->arg);
	size_filled_env = calculate_sizes_filled(*env_copy);
	size_total = calculate_size_env(*env_copy);

	nb_args = count_args_export(cmd_lst);
	if (nb_args == -1) {
		return (ERROR);
	}
//	no_arg_so_print_env_exports(*env_copy, nb_args, size_filled_env);
	fill_env(cmd_lst, *env_copy, nb_args, size_filled_env, size_total);

	return (SUCCESS);

}

/*------- tools--------*/



//t_environment *make_bigger(t_environment **env_copy, int factor, t_var *count_env)// j'ai modifie 3eme param...louche
////est appelé pour agrandir la taille d'un tableau plein
//{
//	//int size_env = env_count_env_copy(env_copy);// peit etre pas necessaire..deja compter dans builtin...sauf si efface?
//	count_env->count_total = (count_env->count_total * factor);
//	t_environment *new_env = malloc(sizeof(t_environment) * ((count_env->count_total) + 1));
//
//	if (new_env == NULL)
//	{
//		printf("Malloc failed bigger env\n");
//		exit(EXIT_FAILURE);
//	}
//
//	int i = 0;
//	if (env_copy!= NULL)
//	{
//		while (env_copy[i]->key != NULL && env_copy[i]->value!= NULL )//&& i < size_env
//		{
//			new_env[i].key = strdup(env_copy[i]->key);
//			new_env[i].value = strdup(env_copy[i]->value);
//			i++;
//		}
//
//		// remplie de vide les slot libre
//		while (i < count_env->count_total)
//		{
//			new_env[i].key = NULL;
//			new_env[i].value = NULL;
//			i++;
//		}
//
//		new_env[count_env->count_total].key = NULL;
//		new_env[count_env->count_total].value = NULL;
//
//		return new_env;
//	}
//	return NULL;
//}










//void search_empty_fill(t_environment **env_copy, char *key, char *value, t_var *count_env)// besoin tab total
//{
//	int	i;
//	i = 0;
//
//	int tab_size = count_env->count_total;
//	while (env_copy!= NULL && i < tab_size)
//	{
//		if ( (env_copy[i]->key == NULL) && (env_copy[i]->value == NULL))
//		{
//			env_copy[i]->key = ft_strdup(key);
//			env_copy[i]->value = ft_strdup(value);
//			printf("ona reussis a remplir le vide \n");
//			count_env->count_filled++;
//			return;
//		}
//		i++;
//	}
//
//	free(key);
//	free(value);
//}



//int check_args_export(t_commande *cmd_lst, t_environment *env_copy, t_var *count_env)
//{
//
//	t_commande *current = cmd_lst;
//	int	i =0;
//	//int count_tab = 0;
//	if (current != NULL)
//	{
//		t_args *args = current->args;
//		while (args != NULL)
//		{
//			i++;
//			args = args->next;
//		}
//		if (i == 0)
//		{
//			print_env(env_copy, count_env->count_filled); // c'est ok..imprime que remplie
//			//print_env_builtin(env_copy); //ancien env
//			return(SUCCESS);
//		}
//		if (i == 1) // plusieurs varaible init
//		{
//			int j = 0;
//			while (j <= i && current != NULL)
//			{
//				char *value = get_value_export(current->args->arg);
////				if (value == NULL)
////				{
////					printf("je suis value nuuuuuul\n");
////					//trigger a juste mettre la valeur du node existant a null ou juste en creer un..osef en vrai
////				}
//				char *key = get_key_export(current->args->arg, value);
//				printf("\nvoici la keyyy %s et voici la value : %s\n",key, value);
//				printf("======================= \n imprimer env avant de check\n");
//				//print_env(env_copy, count_env->count_filled);
//				printf("=============================\n");
//				if (key != NULL && check_good_variable(key) == ERROR)// extrait variable, avant = et check si que lettre
//				{
//					printf("ce n;est pas unn bonne varaible\n"); //plop=
//					return (ERROR);
//				}
//				if (env_copy == NULL)
//					return (ERROR);
//				if (check_is_in_env_export(env_copy, key, count_env) == ERROR)
//				{
//					printf("check avant verifier si il y a des slot vide ou non\n");
//					if (check_is_in_env_export(env_copy, "",count_env) == ERROR)// pas de slot vide
//					{
//
//						printf("i want a bigger train \n");
//						//print_env(env_copy, 27);
//						printf("\n");
//						bigger_env_copy(&env_copy, count_env); // here &count_tab
//						//count_env->count_total = count_env->count_filled;// remet a jour le compte total
//						printf("--------\n");
//						//print_env(env_copy, 54);
//						printf("\n");
//						printf(" c'est moi qui ai la plus grosse\n");
//						printf(" quantite total du tableau %d\n", count_env->count_total);
//					}
//					printf("on a trouvé une place de parc :)\n");
//					search_empty_fill(&env_copy, key, value, count_env);  //a besoin de savoir la taille totale
//					printf("--------\n");
//					print_env(env_copy, count_env->count_filled); // 54.. on veut la valeur dedans le pointeur
//					return(SUCCESS);
//
//				}
//				else
//				{
//					printf("on va changer le papier peint\n");
//					change_value_key(key, value, &env_copy, NULL);
//					//return(SUCCESS);
//
//				}
//				printf ("j'ai continue rtout droit\n");
//				j++;
//				current = current->next;
//				value = NULL;
//				free(key);
//				key = NULL;
//			}
//
//		}
//		else
//		{
//			printf("travail en cours \n");
//			return (1);
//		}
//	}
//	printf("j'ai finii\n");
//	return (0);
//}



//#include "../minishell.h"
//
//
//char *get_value_export(char *str);
//char *get_key_export(char *str, char *value);
//int	check_good_variable(char * str);
//int builtin_export(t_commande *cmd_lst, t_environment *env_copy, t_var *count_env);
////size_t get_current_size(t_environment *env_copy);
////void bigger_tab(t_environment **env_copy, size_t size_factor);
////void get_big_tab(t_environment **env_copy);
//void search_empty_fill(t_environment *env_copy, char *key, char *value, t_var *count_env);
//
//int env_count_env_copy(t_environment *env_copy);
//t_environment *make_bigger(t_environment *env_copy, int factor, t_var *count_env);
//
//void bigger_env_copy(t_environment **env_copy, t_var *count_env);
//
////void get_big_tab(t_environment **env_copy)
////{
////	size_t size_current_tab = get_current_size(*env_copy);
////	bigger_tab(env_copy,size_current_tab);
////}
////size_t get_current_size(t_environment *env_copy)
////{
////	size_t current_size = 0;
////
////	while (env_copy[current_size].key != NULL && env_copy[current_size].value != NULL) {
////		++current_size;
////	}
////	return current_size;
////}
////void bigger_tab(t_environment **env_copy, size_t size_factor)
////{
////	size_t new_tab_size = (size_factor) * 2;
////
////	t_environment *new_tab = (t_environment *)malloc(new_tab_size * sizeof(t_environment));
////
////	if (new_tab != NULL) {
////		// Copiez les éléments existants dans le nouveau tableau
////		size_t i = 0;
////		while (i < size_factor) {
////			new_tab[i] = *env_copy[i];
////			++i;
////		}
////
////		// Libérez la mémoire de l'ancien tableau
////		free(*env_copy);
////
////		// Mettez à jour le pointeur et la taille
////		*env_copy = new_tab;
////		size_factor = new_tab_size;
////
////		// Initialisez les nouvelles parties du tableau si nécessaire
////		while (i < size_factor) {
////			env_copy[i]->key = NULL;
////			env_copy[i]->value = NULL;
////			++i;
////		}
////
////		printf("Tableau agrandi avec succès.\n");
////	} else {
////		fprintf(stderr, "Erreur lors de l'agrandissement du tableau.\n");
////	}
////}
//
//int env_count_env_copy(t_environment *env_copy) // taille remplie du coup..sauf si appelé par env_bigger qui appelle quand ce'st plein
//{
//	int count = 0;
//	while (env_copy[count].key != NULL)
//		count++;
//	printf("taillle de env %d\n", count);
//	return count;
//}
//
//t_environment *make_bigger(t_environment *env_copy, int factor, t_var *count_env)// j'ai modifie 3eme param...louche
////est appelé pour agrandir la taille d'un tableau plein
//{
//	//int size_env = env_count_env_copy(env_copy);// peit etre pas necessaire..deja compter dans builtin...sauf si efface?
//	count_env->count_total = (count_env->count_total * factor);
//	t_environment *new_env = malloc(sizeof(t_environment) * ((count_env->count_total) + 1));
//
//	if (new_env == NULL)
//	{
//		printf("Malloc failed bigger env\n");
//		exit(EXIT_FAILURE);
//	}
//
//	int i = 0;
//	while (env_copy[i].key != NULL && env_copy[i].value!= NULL )//&& i < size_env
//	{
//		new_env[i].key = strdup(env_copy[i].key);
//		new_env[i].value = strdup(env_copy[i].value);
//		i++;
//	}
//
//	// remplie de vide les slot libre
//	while (i < count_env->count_total)
//	{
//		new_env[i].key = NULL;
//		new_env[i].value = NULL;
//		i++;
//	}
//
//	new_env[count_env->count_total].key = NULL;
//	new_env[count_env->count_total].value = NULL;
//
//	return new_env;
//}
//
//void bigger_env_copy(t_environment **env_copy, t_var *count_env)
//{
//	t_environment *temp = make_bigger(*env_copy, 2, count_env);//tab plein
//		free_env_struct(*env_copy);
//		*env_copy = temp;
//	printf("doooone it's bigger\n");
//
//}
//// pourrait retourner le nombre de fois que ca agrnadie...pour avoir le nombre total
//void change_value_key(char *key, char *new_value, t_environment *env_copy, t_var *count_env)
//{
//	if (key == NULL || env_copy == NULL) {
//		// Gérer l'erreur ou retourner si key ou env_copy est NULL
//		return;
//	}
//
//	int i = 0;
//	while (env_copy[i].key != NULL && i < count_env->count_total)
//	{
//		if (strcmp(env_copy[i].key, key) == 0)
//		{
//			if (env_copy[i].value != NULL)
//			{
//				free(env_copy[i].value); // Libérer l'ancienne valeur
//			}
//			env_copy[i].value = ft_strdup(new_value);
//			break;
//		}
//		i++;
//	}
//}
//
//
//size_t  ft_strcspn(const char *s, const char *reject)
//{
//	int     i = 0;
//	int     j = 0;
//
//	while (s[i] != '\0')
//	{
//		j = 0;
//		while (reject[j] != '\0')
//		{
//			if(s[i] == reject[j])
//				return (i);
//			j++;
//		}
//		i++;
//	}
//	return (i);
//}
//#include <stddef.h>
//#include <stdlib.h>
//int	check_good_variable(char *str)
//{
//	while (*str)
//	{
//		if (!ft_isalpha(*str))
//			return (ERROR);
//		str++;
//	}
//	return (SUCCESS);
//}
//char *ft_strndup(const char *src, size_t n)
//{
//	size_t i = 0;
//	while (src[i] != '\0' && i < n) {
//		i++;
//	}
//
//	char *dest = (char *)malloc(i + 1);
//	if (dest == NULL) {
//		return NULL;
//	}
//
//	i = 0;
//	while (src[i] != '\0' && i < n) {
//		dest[i] = src[i];
//		i++;
//	}
//	dest[i] = '\0';
//
//	return dest;
//}
//char *get_value_export(char *str)
//{
//	char *result;
//	result = (strchr(str, '=')+1);
//	if (str != NULL)
//		if (result == NULL)
//			return NULL;
//	return(result);
//}
//char *get_key_export(char *str, char *value)
//{
//	if (str != NULL && value != NULL)
//	{
//		// Calcule la longueur de la sous-chaîne avant le délimiteur
//		size_t key_length = value - (str + 1);// pour enelever le =
//
//		// Utilise ft_strndup pour créer une copie de la sous-chaîne
//		return (ft_strndup(str, key_length) );
//	}
//
//	return NULL;
//}
//
//void search_empty_fill(t_environment *env_copy, char *key, char *value, t_var *count_env)// besoin tab total
//{
//	int	i;
//	i = 0;
//
//	int tab_size = count_env->count_total;
//	while (env_copy!= NULL && i < tab_size)
//	{
//		if ( (env_copy[i].key == NULL) && (env_copy[i].value == NULL))
//		{
//			env_copy[i].key = ft_strdup(key);
//			env_copy[i].value = ft_strdup(value);
//			printf("ona reussis a remplir le vide \n");
//			count_env->count_filled++;
//			return;
//		}
//		i++;
//	}
//
//	free(key);
//	free(value);
//}
//
//int check_args_export(t_commande *cmd_lst, t_environment *env_copy, t_var *count_env)
//{
//
//	t_commande *current = cmd_lst;
//	int	i =0;
//	//int count_tab = 0;
//	if (current != NULL)
//	{
//		t_args *args = current->args;
//		while (args != NULL)
//		{
//			i++;
//			args = args->next;
//		}
//		if (i == 0)
//		{
//			print_env(env_copy, count_env->count_filled); // c'est ok..imprime que remplie
//			//print_env_builtin(env_copy); //ancien env
//			return(SUCCESS);
//		}
//		if (i == 1) // plusieurs varaible init
//		{
//			int j = 0;
//			while (j <= i && current != NULL)
//			{
//				char *value = get_value_export(current->args->arg);
////				if (value == NULL)
////				{
////					printf("je suis value nuuuuuul\n");
////					//trigger a juste mettre la valeur du node existant a null ou juste en creer un..osef en vrai
////				}
//				char *key = get_key_export(current->args->arg, value);
//				printf("\nvoici la keyyy %s et voici la value : %s\n",key, value);
//				if (key != NULL && check_good_variable(key) == ERROR)// extrait variable, avant = et check si que lettre
//				{
//					printf("ce n;est pas unn bonne varaible\n"); //plop=
//					return (ERROR);
//				}
//				if (check_is_in_env(env_copy, key) == ERROR)
//				{
//					if (check_is_in_env(env_copy, "") == ERROR)// pas de slot vide
//					{
//
//						printf("i want a bigger train \n");
//						//print_env(env_copy, 27);
//						printf("\n");
//						bigger_env_copy(&env_copy, count_env); // here &count_tab
//						//count_env->count_total = count_env->count_filled;// remet a jour le compte total
//						printf("--------\n");
//						//print_env(env_copy, 54);
//						printf("\n");
//						printf(" c'est moi qui ai la plus grosse\n");
//						printf(" quantite total du tableau %d\n", count_env->count_total);
//					}
//					printf("on a trouvé une place de parc :)\n");
//					search_empty_fill(env_copy, key, value, count_env);  //a besoin de savoir la taille totale
//					printf("--------\n");
//					print_env(env_copy, count_env->count_filled); // 54.. on veut la valeur dedans le pointeur
//					return(SUCCESS);
//
//				}
//				else
//				{
//					printf("on va changer le papier peint\n");
//					change_value_key(key, value, env_copy, NULL);
//					//return(SUCCESS);
//
//				}
//				printf ("j'ai continue rtout droit\n");
//				j++;
//				current = current->next;
//				value = NULL;
//				free(key);
//				key = NULL;
//			}
//
//		}
//		else
//		{
//			printf("travail en cours \n");
//			return (1);
//		}
//	}
//	printf("j'ai finii\n");
//	return (0);
//}
//
//int	builtin_export(t_commande *cmd_lst, t_environment *env_copy, t_var *count_env)//, t_commande *cmd_lst
//{
//
//	if (check_args_export(cmd_lst, env_copy, count_env) == ERROR)
//		return (ERROR);
//	return (SUCCESS);
//}