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
void print_env_builtin_export(t_environment  *env_copy)//fprint tout
{
	int                i;
	i = 0;
	if (env_copy != NULL)
	{
		while (env_copy[i].key != NULL)
		{
			printf("%s=%s\n", env_copy[i].key, env_copy[i].value);
			i++;
		}
	}
}

void print_env_alphabet_analysis(t_environment *env_copy, int size_filled)
{
	// Chaîne de caractères représentant l'alphabet
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
	char alpha_big[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Indice pour chaque lettre de l'alphabet
	int i ;
	i = 0;
	// Boucle pour chaque lettre de l'alphabet
	int total_elements = 0;
	int j;
	while (i < 26 && total_elements <= size_filled)
	{
		char minus = alphabet[i];
		char maj = alpha_big[i];

		j = 0;

		while (j <=size_filled )
		{
			if (env_copy[j].key != NULL && (env_copy[j].key[0] == minus || env_copy[j].key[0] == maj))
			{
				// Ajoutez votre logique d'impression ici, par exemple, imprimez les éléments qui commencent par la lettre courante
				printf("%s=%s\n", env_copy[j].key, env_copy[j].value);
				total_elements++;
			}

			j++;
		}

		i++;
	}
	i = 0;
	while (i < 26 && total_elements < size_filled)
	{
		char minus = alphabet[i];
		char maj = alpha_big[i];
		j = 0;

		while (j < size_filled)
		{
			if ((env_copy[j].key != NULL && (env_copy[j].key[0] == '_')) && strlen(env_copy[j].key) >= 4)
			{
				if (env_copy[j].key[3] == minus || env_copy[j].key[3] == maj)
				{
					// Ajoutez votre logique d'impression ici, par exemple, imprimez les éléments qui commencent par la lettre courante après '_'
					printf("%s=%s\n", env_copy[j].key, env_copy[j].value);
					total_elements++;
				}
			}
			j++;
		}
		i++;
	}
}


void print_env_export(t_environment *env_copy, int size_filled)
{
	if (env_copy == NULL) {
		printf("Env is empty or invalid.\n");
		return;
	}

	int i = 0;
	while (i <= size_filled && env_copy[i].key != NULL)
	{
		printf("%s=%s", env_copy[i].key, env_copy[i].value);

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
		//print_env_export(env_copy, size_filled);
		print_env_alphabet_analysis(env_copy, size_filled);
}

void double_env(t_environment *env_copy, int size_total, int factor)
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
	if (env_copy != NULL)
	{
		while ((env_copy)[i].key != NULL && (env_copy)[i].value != NULL) {
			new_env[i].key = strdup((env_copy)[i].key);
			new_env[i].value = strdup((env_copy)[i].value);
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
		//free(*env_copy); // Libère l'ancien tableau
		env_copy = new_env; // Met à jour le pointeur
		free_env_struct(new_env);

	}
	return ;
}

int 	fill_slot(char *key, char *value, t_environment *env_copy, int index, int size_filled_env)
{
	int current_index ;
	(void)index;
	current_index = size_filled_env;
	if ((env_copy)[current_index].key != NULL && env_copy[current_index].value != NULL)
	{
		free((env_copy)[current_index].key);
		free((env_copy)[current_index].value);
		if ((env_copy)[current_index].key == NULL)
			printf("on a liberer la key\n");
		(env_copy)[current_index].key = strdup(key);
		(env_copy)[current_index].value = strdup(value);
//		printf("Après l'allocation : key = %s, value = %s\n", (env_copy)[current_index].key, (env_copy)[current_index].value);

		return(current_index);
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

void remplace_old_value(char *value, int index, t_environment *env_copy)
{
	printf("USER key = %s\n", (env_copy)[index].key);
	if ((env_copy)[index].key != NULL || ft_strcmp((env_copy)[index].value, "\"\"") == 0)
		free((env_copy)[index].value);
	(env_copy)[index].value = strdup(value);
	printf("USER value = %s\n", (env_copy)[index].value);
}

int	create_more_space (t_environment *env_copy, int size_total)
{
	double_env(env_copy, size_total, 2); // avant juste env_copy
	printf("yes c'est plus grand\n");
	//print_env_builtin_export(*env_copy);
	//yeah...ca print bien tout le tableau
	return (SUCCESS);
}

int check_env_is_full();

int fill_env(t_commande *cmd_lst, t_environment *env_copy, int nb_args, int size_filled_env, int size_total) // *env_copy
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

		if (index == -1) // need space
		{
			if (size_filled_env == size_total)
			{
				create_more_space(env_copy, size_total); // is okaaaay
				size_total *= 2;
			}
			printf("\n==================================\n");
			printf("size total apres agrandissement %d\n", size_total);
			printf("size_total = %d\n", size_total);
			printf("size_filled_env = %d\n", size_filled_env);
			print_env_builtin_export(env_copy);
			size_filled_env = fill_slot(key, value, env_copy, index, size_filled_env);

		}
		else
		{
			remplace_old_value(value, index, env_copy);
			printf("on a juste remplacer la valeur \n");
		}
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
	while (env_copy[count].key != NULL && env_copy[count].value != NULL)
		count++;
	return (count);
}
void printCommandList(t_commande *cmdList)
{
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

int export_main(t_commande *cmd_lst, t_environment *env_copy)
{

	int nb_args;
	int size_filled_env;
	int size_total;

	size_filled_env = calculate_sizes_filled(env_copy); // comme si calcule une copy en env
	size_total = calculate_size_env(env_copy);
	nb_args = count_args_export(cmd_lst);
	if (nb_args == -1)
		return (ERROR);
//	printf("apres size_total avant no _arg filled = %d\n", size_total);
//	printf("apres size_filled_env avant no _arg = %d\n", size_filled_env);
	//printf("++pointeur avant, no_args %p\n", &env_copy);
	no_arg_so_print_env_exports(env_copy, nb_args, size_filled_env);
	//printf("++pointeur apres no_args, avant fille_env %p\n", &env_copy);
	printf("SIZE %lu\n", sizeof(*env_copy));
	fill_env(cmd_lst, env_copy, nb_args, size_filled_env, size_total);
	printf("SIZE %lu\n", sizeof(*env_copy));
	//printf("++pointeur apres fill_env %p\n", &env_copy);


//	print_env_builtin_export(*env_copy);

	return (SUCCESS);

}
