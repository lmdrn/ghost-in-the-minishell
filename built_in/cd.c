#include "../minishell.h"

void print_value(t_environment    *env_copy, char *key)
{
	int                i;
	i = 0;
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, key) == 0)
			printf("Key: %s, Value: %s\n", env_copy[i].key, env_copy[i].value);
		i++;
	}
}

/* -------------------prototype-----------------------------*/
int	ft_cd(t_environment *env_copy, char *path);
void add_node_at_end(t_environment **head, char *key, char *value);
int go_home(t_environment *env_copy, char *home);
char *get_home(t_environment *head);
t_environment	*last_node(t_environment *head);
int check_is_in_env(t_environment *env_copy, char *var);
int check_path(char *path);
int static	check_args_cd(t_commande *cmd_lst);
void update_pwd_oldpwd(t_environment *env_copy, char *change_pwd);
int go_home(t_environment *env_copy, char *home);
int builtin_cd(t_commande *cmd_lst, t_environment *env_copy);
/*------ utils liste------*/
t_environment	*last_node(t_environment *head)
{
	if (!head)//secu si existe pas
		return (NULL);
	while (head->next != NULL) // tant que le pointeur du prochain n'est pas null, donc pas fin
		head = head->next; // passe au prochain
	return (head); //retourne l'adresse du node et pas du pointeur
}
void add_node_at_end(t_environment **head, char *key, char *value) {
	// Créer un nouveau nœud
	t_environment *new_node = malloc(sizeof(t_environment));
	if (new_node == NULL) {
		perror("Erreur d'allocation mémoire pour le nouveau nœud");
		exit(EXIT_FAILURE);
	}

	// attribue la valeur pour la key et la valeur
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	//secu si les valeurs sont vides
	if (new_node->key == NULL || new_node->value == NULL) {
		perror("Erreur d'allocation mémoire pour la clé ou la valeur");
		exit(EXIT_FAILURE);
	}
	// Le nouveau nœud est ajouté à la fin, donc son prochain nœud est NULL
	new_node->next = NULL;

	// Secu si la liste est vide, le nouveau nœud devient la tête
	if (*head == NULL) {
		*head = new_node;
		return;
	}

	// Trouver le dernier nœud et ajouter le nouveau nœud à la fin de la liste
	t_environment *last = last_node(*head);
	last->next = new_node;
}

//char *get_home(t_environment *env_copy)
//{
//	if (env_copy == NULL)
//		return (NULL);
//	while (env_copy != NULL && env_copy->key != NULL)
//	{
//		if (strcmp(env_copy->key, "HOME") == 0)
//		{
//			return env_copy->value;
//		}
//		env_copy = env_copy->next;
//	}
//	return NULL; // HOME n'est pas défini
//}
char *get_home(t_environment *env_copy)
{
	if (env_copy == NULL)
		return NULL;

	int i = 0;

	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, "HOME") == 0)
		{
			return env_copy[i].value;
		}
		i++;
	}

	return NULL; // HOME n'est pas défini
}


/*------ check liste------*/
int check_is_in_env(t_environment *env_copy, char *var)
{
	int length;
	t_environment *current;

	length = ft_strlen(var);
	current = env_copy;

	while (current)
	{
		if (ft_strncmp(current->key, var, length) == 0)
			return (SUCCESS);
		current = current->next;
	}

	add_node_at_end(&env_copy, var, 0);
	return (ERROR);
}
int check_path(char *path)
{
	if (access(path, F_OK) != -1)
		return (SUCCESS);
	else
	{
		printf( "cd : no such file or directory :%s\n", path);
		return (ERROR);
	}
}

int static check_args_cd(t_commande *cmd_lst)
{
	t_commande *current = cmd_lst;
	t_commande *temp = cmd_lst;
	int	i;
	//parcourt le node
	i = 0;
	if (current != NULL)
	{
		while (current->args != NULL && ((current->args->arg[0] == ' ') || (current->args->arg[0] == '\t')))
		{
			current->args = current->args->next;
		}
		if (temp->args == NULL )
		{
			printf("il n'y a aucuuuun arguments, ok");
			return (0);
		}
		if (ft_strcmp(current->args->arg, "~") == 0 )//&& current->args->arg[1] == '\0')
		{
			printf("il y a le tild, ok");
			return (0);
		}

		else if (strcmp(current->args->arg, "..") == 0) {
			// remonter d'un répertoire
			if (chdir("..") != 0)
			{
				printf("cd: Failed to change directory");
				return ERROR;
			}
		}
	}
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	if (i > 1)
	{
		printf("trop d'artgumetns");
		return (-1);
	}

	else
		return (-1);
}

/*------real shit------*/

void update_pwd_oldpwd(t_environment *env_copy, char *change_pwd)
{
	char *current_pwd;


	current_pwd = getcwd(NULL, 0);
	printf("\n current pwd %s \n", current_pwd);
	// Construire les chaînes "PWD=" et "OLDPWD="
	//new_pwd = ft_strjoin("PWD=", change_pwd + 1); // Ignorer le premier caractère (=)
	//printf("\n etape 2\n");
	printf("\netape 3 \n");

	// Rechercher et mettre à jour la valeur de "PWD" et "OLDPWD"
	int i = 0;
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, "PWD") == 0)
		{
			free(env_copy[i].value); // Libérer l'ancienne valeur
			env_copy[i].value = ft_strdup(change_pwd); // Mettre à jour la valeur (ignorer le premier caractère)
			printf("\n etape pwd\n");
			break;
		}
		i++;
	}
	while (env_copy[i].key != NULL)
	{
		if (strcmp(env_copy[i].key, "OLDPWD") == 0)
		{
			free(env_copy[i].value); // Libérer l'ancienne valeur
			env_copy[i].value = ft_strdup(current_pwd); // Mettre à jour la valeur
			printf("\n eatape oldpqd\n");
			break;
		}
		i++;
	}

	print_value(env_copy, "PWD");
	print_value(env_copy, "OLDPWD");
	// Libérer la mémoire allouée par getcwd, strjoin
	free(current_pwd);
}

//void update_pwd_oldpwd(t_environment **head, char *change_pwd)
//{
//	char *current_pwd;
//	char *new_pwd;
//	char *old_pwd;
//
//	current_pwd = getcwd(NULL, 0);
//
//	// Construire les chaînes "PWD=" et "OLDPWD="
//	new_pwd = ft_strjoin("PWD=", change_pwd);// pas garder le =?
//	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
//
//	// Rechercher et mettre à jour la valeur de "PWD" et "OLDPWD"
//	int i = 0;
//	while ((*head)[i].key != NULL)
//	{
//		if (strcmp((*head)[i].key, "PWD") == 0)
//		{
//			free((*head)[i].value); // Libérer l'ancienne valeur
//			(*head)[i].value = ft_strdup(change_pwd); // Mettre à jour la valeur
//		}
//		else if (strcmp((*head)[i].key, "OLDPWD") == 0)
//		{
//			free((*head)[i].value); // Libérer l'ancienne valeur
//			(*head)[i].value = ft_strdup(current_pwd); // Mettre à jour la valeur
//		}
//		i++;
//	}
//
//	// Libérer la mémoire allouée par getcwd, strjoin
//	free(current_pwd);
//	free(new_pwd);
//	free(old_pwd);
//}

//void update_pwd_oldpwd(t_environment **head, char *change_pwd)
//{
//	char *current_pwd;
//	char *new_pwd;
//	char *old_pwd;
//
//	current_pwd = getcwd(NULL, 0);
//
//	// Construire les chaînes "PWD=" et "OLDPWD="
//	new_pwd = ft_strjoin("PWD=", change_pwd);
//	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
//
//	// Rechercher et mettre à jour la valeur de "PWD"
//	t_environment *current = *head;
//	while (current != NULL)
//	{
//		if (strcmp(current->key, "PWD") == 0)
//		{
//			free(current->value); // Libérer l'ancienne valeur
//			current->value = ft_strdup(change_pwd); // Mettre à jour la valeur
//			break;
//		}
//		else if (strcmp(current->key, "OLDPWD") == 0)
//		{
//			free(current->value); // Libérer l'ancienne valeur
//			current->value = ft_strdup(current_pwd); // Mettre à jour la valeur
//			break;
//		}
//		current = current->next;
//	}
//
//	// Libérer la mémoire allouée par getcwd, strjoin
//	free(current_pwd);
//	free(new_pwd);
//	free(old_pwd);
//}
/* retourne 0 pour mener à HOME, -1 si erreur et autre si ok, parfcours la liste*/
int go_home(t_environment *env_copy, char *home)
{
	if (chdir(home) != 0)
	{
		printf ("cd: Home non accessible");
		return (ERROR);
	}

	else
	{
		printf("\n je suis arriv´´jusqu ici\n");
		update_pwd_oldpwd(env_copy, home);
	}


	//leaks aussi ici
	return (SUCCESS);
}
int	ft_cd(t_environment *env_copy, char *path)
{
	//gerer les ..


	if (check_path(path) == ERROR)
		return (ERROR);
	check_is_in_env(env_copy, "PWD");
	check_is_in_env(env_copy, "OLDPWD");
	update_pwd_oldpwd(env_copy, path);
	return (SUCCESS);

}
int builtin_cd(t_commande *cmd_lst, t_environment *env_copy)
{
	char *home;
	int arg;
	arg = 0;
	home = NULL;
	//trop d'arguments
	arg = check_args_cd(cmd_lst);
	printf("\n voici la valeur de arg avabt traitment %d\n", arg);
	//plus de 1 arguments
	if (arg == -1)
	{
		printf("cd: too many arguments\n");
		free(home);
		return (ERROR);
	}
	//pas acces à home
	home = get_home(env_copy);
	if (home == NULL)
	{
		printf("cd: Home not set\n");
		free(home);
		return (ERROR);
	}
	//doit retourner a la racine
	if (arg == 0)
	{
		//leaks peut pas aller vers go home
		printf("\nvoici la valeur de home %s\n", home);
		if (go_home(env_copy, home) == ERROR)
		{
			printf("can't go home");
			free(home);
			return(ERROR);
		}
		free(home);
		return(SUCCESS);
	}
	if (arg == 1 || arg == -1)
	{
		if (ft_cd(env_copy,cmd_lst->args->arg) == ERROR)
		{
			printf("path to file doesn't exist");
			free(home);
			return (ERROR);
		}
	}
	ft_cd(env_copy,cmd_lst->args->arg);// iciiii prend pas en compte si cd sans argument...va pas au bonne nedroit
	free(home);
	return (SUCCESS);


}

