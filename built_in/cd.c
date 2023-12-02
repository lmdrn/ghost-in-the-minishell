#include "../minishell.h"



//size_t	ft_strlen(const char *s)
//{
//	size_t	i;
//
//	i = 0;
//	while (s[i] != '\0')
//		i++;
//	return (i);
//}
//
//char	*ft_strdup(const char *s1)
//{
//	char	*str;
//	int		i;
//	int		s1_len;
//
//	i = 0;
//	s1_len = ft_strlen(s1);
//	str = malloc((sizeof(*str) * s1_len) + 1);
//	if (str == NULL)
//		return (0);
//	while (s1[i])
//	{
//		str[i] = s1[i];
//		i++;
//	}
//	str[i] = '\0';
//	return (str);
//}
//int	ft_strncmp(const char *s1, const char *s2, size_t nbytes)
//{
//	size_t	i;
//
//	i = 0;
//	while ((i < nbytes) && ((s1[i] != '\0') || (s2[i] != '\0')))
//	{
//		if (s1[i] > s2[i])
//			return ((((unsigned char *)s1)[i]) - ((unsigned char *)s2)[i]);
//		if (s1[i] < s2[i])
//			return ((((unsigned char *)s1)[i]) - ((unsigned char *)s2)[i]);
//		i++;
//	}
//	return (0);
//}
//
//char	*ft_strjoin(char const *s1, char const *s2)
//{
//	char		*str;
//	int			i;
//	int			j;
//	int			count;
//
//	i = 0;
//	j = 0;
//	count = ft_strlen(s1) + ft_strlen(s2);
//	str = (char *)malloc(count + 1);
//	if (str == NULL)
//		return (NULL);
//	while (s1[i] != '\0')
//	{
//		str[i] = ((char *)s1)[i];
//		i++;
//	}
//	while (s2[j] != '\0')
//		str[i++] = ((char *)s2)[j++];
//	str[i] = '\0';
//	return (str);
//}
//
//
// // struct pour l'env : t_environment	*env_copy;
// typedef struct s_environment
// {
//	 char					*key;
//	 char					*value;
//	 struct s_environment	*next;
// }	t_environment;
//
//enum e_types {
//	cmd,
//	builtin,
//	args,
//	flags,
//	filein,
//	fileout,
//	delimiter,
//	is_pipe,
//	ch_g,
//	ch_d,
//	dbl_ch_g,
//	dbl_ch_d
//};
//
//typedef struct s_type
//{
//	char			*text;
//	int				type;
//	struct s_type	*next;
//}	t_type;
//
//typedef struct s_args
//{
//	char			*arg;
//	struct s_args	*next;
//
//}	t_args;
//
//typedef struct s_commande
//{
//	char				*cmd;
//	t_args				*args;
//	char				*fdin;
//	char				*fdout;
//	struct s_commande	*next;
//}	t_commande;

/* -------------------prototype-----------------------------*/
int check_path(char *str);
int	ft_cd(t_environment *env_copy, char *path);
void add_node_at_end(t_environment **head, char *key, char *value);
int go_home(t_environment *env_copy, char *home);
char *get_home(t_environment *head);
t_environment	*last_node(t_environment *head);
int check_is_in_env(t_environment *env_copy, char *var);
int check_path(char *path);
int static	check_args_cd(t_commande *cmd_lst);
void update_pwd_oldpwd(t_environment **head, char *change_pwd);
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
char *get_home(t_environment *env_copy)
{
	if (env_copy == NULL)
		return (NULL);
	while (env_copy != NULL && env_copy->key != NULL)
	{
		if (strcmp(env_copy->key, "HOME") == 0)
		{
			return env_copy->value;
		}
		env_copy = env_copy->next;
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
			printf("il n'y a aucun arguments, ok");
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
void update_pwd_oldpwd(t_environment **head, char *change_pwd)
{
	char *current_pwd;
	char *new_pwd;
	char *old_pwd;

	current_pwd = getcwd(NULL, 0);

	// Construire les chaînes "PWD=" et "OLDPWD="
	new_pwd = ft_strjoin("PWD=", change_pwd);
	old_pwd = ft_strjoin("OLDPWD=", current_pwd);

	// Rechercher et mettre à jour la valeur de "PWD"
	t_environment *current = *head;
	while (current != NULL)
	{
		if (strcmp(current->key, "PWD") == 0)
		{
			free(current->value); // Libérer l'ancienne valeur
			current->value = ft_strdup(change_pwd); // Mettre à jour la valeur
			break;
		}
		else if (strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value); // Libérer l'ancienne valeur
			current->value = ft_strdup(current_pwd); // Mettre à jour la valeur
			break;
		}
		current = current->next;
	}

	// Libérer la mémoire allouée par getcwd, strjoin
	free(current_pwd);
	free(new_pwd);
	free(old_pwd);
}
/* retourne 0 pour mener à HOME, -1 si erreur et autre si ok, parfcours la liste*/
int go_home(t_environment *env_copy, char *home)
{
	if (chdir(home) != 0)
	{
		printf ("cd: Home non accessible");
		return (ERROR);
	}
	else
		update_pwd_oldpwd(&env_copy, home);
	return (SUCCESS);
}
int	ft_cd(t_environment *env_copy, char *path)
{
	//gerer les ..


	if (check_path(path) == ERROR)
		return (ERROR);
	check_is_in_env(env_copy, "PWD");
	check_is_in_env(env_copy, "OLDPWD");
	update_pwd_oldpwd(&env_copy, path);
	return (SUCCESS);

}
int builtin_cd(t_commande *cmd_lst, t_environment *env_copy)
{
	char *home;
	int arg;
	home = NULL;
	//trop d'arguments
	if ((arg = check_args_cd(cmd_lst)) == -1)
	{
		printf("cd: too many arguments\n");
		return (ERROR);
	}
	//pas acces à home
	home = get_home(env_copy);
	if (home == NULL)
	{
		printf("cd: Home not set\n");
		return (ERROR);
	}
	//doit retourner a la racine
	if (arg == 0)
	{
		if (go_home(env_copy, home) == ERROR)
		{
			printf("can't go home");
			return(ERROR);
		}
	}
	if (arg <= 1)
	{
		if (ft_cd(env_copy,cmd_lst->args->arg) == ERROR)
		{
			printf("path to file doesn't exist");
			return (ERROR);
		}
	}
	ft_cd(env_copy,cmd_lst->args->arg);
	free(home);
	return (SUCCESS);


}

