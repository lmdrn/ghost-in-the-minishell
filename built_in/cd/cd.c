#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int SUCCESS =1 ;
int ERROR = 0;
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;
	int		s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	str = malloc((sizeof(*str) * s1_len) + 1);
	if (str == NULL)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
int	ft_strncmp(const char *s1, const char *s2, size_t nbytes)
{
	size_t	i;

	i = 0;
	while ((i < nbytes) && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] > s2[i])
			return ((((unsigned char *)s1)[i]) - ((unsigned char *)s2)[i]);
		if (s1[i] < s2[i])
			return ((((unsigned char *)s1)[i]) - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	int			i;
	int			j;
	int			count;

	i = 0;
	j = 0;
	count = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(count + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = ((char *)s2)[j++];
	str[i] = '\0';
	return (str);
}


 // struct pour l'env : t_environment	*env_copy;
 typedef struct s_environment
 {
	 char					*key;
	 char					*value;
	 struct s_environment	*next;
 }	t_environment;

enum e_types {
	cmd,
	builtin,
	args,
	flags,
	filein,
	fileout,
	delimiter,
	is_pipe,
	ch_g,
	ch_d,
	dbl_ch_g,
	dbl_ch_d
};

typedef struct s_type
{
	char			*text;
	int				type;
	struct s_type	*next;
}	t_type;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;

}	t_args;

typedef struct s_commande
{
	char				*cmd;
	t_args				*args;
	char				*fdin;
	char				*fdout;
	struct s_commande	*next;
}	t_commande;

/* -------------------prototype-----------------------------*/
int check_args(t_commande *cmd_lst);
int check_path(char *str);
int	ft_cd(t_environment *env_copy, char *path);
void add_node_at_end(t_environment **head, char *key, char *value);
int go_home(t_environment *env_copy, char *home);
char *get_home(t_environment *head);
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
char *get_home(t_environment *head)
{
	while (head != NULL) {
		if (strcmp(head->key, "HOME") == 0)
		{
			return head->value;
		}
		head = head->next;
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
int check_args(t_commande *cmd_lst)
{
	t_commande *current = cmd_lst;
	int	i;
	//parcourt le node
	i = 0;
	if ((current->args->arg == NULL) || (current->args->arg[0] == '~' && current->args->arg[1] == '\0'))
		return(0);
	else if (strcmp(current->args->arg, "..") == 0)
	{
		// remonter d'un répertoire
		if (chdir("..") != 0)
		{
			printf("cd: Failed to change directory");
			return ERROR;
		}
	}
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	if (i > 1)
		return (-1);
	else
		return (i);
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
	int ret;

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

	//trop d'arguments
	if ((arg = check_args(cmd_lst)) == -1)
	{
		printf("cd: too many arguments\n");
		return (ERROR);
	}
	//pas acces à home
	else if ((home = get_home(env_copy)) == NULL)
	{
		printf("cd: Home not set\n");
		return (ERROR);
	}
	//doit retourner a la racine
	else if (arg == 0)
	{
		if (go_home(env_copy, home) == ERROR)
		{
			printf("can't go home");
			return(ERROR);
		}
	}
	else if (arg <= 1)
	{
		if (ft_cd(env_copy,cmd_lst->args->arg) == ERROR)
		{
			printf("path to file doesn't exist");
			return (ERROR);
		}
	}
	ft_cd(env_copy,cmd_lst->args->arg);
	return (SUCCESS);


}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//int main() {
//	t_commande *cmd_lst = NULL;
//	t_environment *env_copy = NULL;
//	char buffer[256];
//
//	// Lire les commandes depuis l'entrée standard et les ajouter à la liste
//	printf("Entrez vos commandes (terminer avec Ctrl + D ou Ctrl + Z):\n");
//	while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
//		// Ajouter une nouvelle commande à la liste
//		t_commande *new_cmd = malloc(sizeof(t_commande));
//		new_cmd->cmd = ft_strdup("cd"); // Pour tester la commande cd
//		new_cmd->args = malloc(sizeof(t_args));
//		new_cmd->args->arg = ft_strdup(buffer); // Utilisez la ligne complète comme argument pour cd
//		new_cmd->args->next = NULL;
//		new_cmd->fdin = NULL;
//		new_cmd->fdout = NULL;
//		new_cmd->next = NULL;
//
//		// Ajouter la nouvelle commande à la fin de la liste
//
//		// Afficher la commande ajoutée pour vérification
//		printf("Commande ajoutée: %s", buffer);
//	}
//
//	// Initialiser la liste d'environnement (env_copy) avec des valeurs par défaut
//	add_node_at_end(&env_copy, "HOME", "/home/utilisateur");
//	add_node_at_end(&env_copy, "PWD", "/home/utilisateur");
//	add_node_at_end(&env_copy, "OLDPWD", "/home/utilisateur/ancien");
//
//	// Appeler la fonction builtin_cd avec la première commande de la liste et la liste d'environnement
//	builtin_cd(cmd_lst, env_copy);
//
//	// Libérer la mémoire allouée pour la liste de commandes et la liste d'environnement
//	// Vous devez remplacer cette fonction par celle que vous avez pour libérer la mémoire
//	// free_cmd_list(cmd_lst);
//	// free_env_list(env_copy);
//
//	return 0;
//}
// Fonction pour libérer la mémoire allouée pour une liste de commandes
void free_cmd_list(t_commande *head)
{
	while (head != NULL) {
		t_commande *temp = head;
		head = head->next;

		// Libérer la mémoire allouée pour la commande et ses arguments
		free(temp->cmd);
		free(temp->args->arg);
		free(temp->args);

		// Libérer la mémoire allouée pour les descripteurs de fichiers (si nécessaire)
		// free(temp->fdin);
		// free(temp->fdout);

		// Libérer la mémoire allouée pour la commande actuelle
		free(temp);
	}
}

// Fonction pour libérer la mémoire allouée pour une liste d'environnement
void free_env_list(t_environment *head)
{
	while (head != NULL) {
		t_environment *temp = head;
		head = head->next;

		// Libérer la mémoire allouée pour la clé et la valeur
		free(temp->key);
		free(temp->value);

		// Libérer la mémoire allouée pour le nœud d'environnement actuel
		free(temp);
	}
}

int main(int argc, char *argv[])
{
	t_commande *cmd_lst = NULL;
	t_environment *env_copy = NULL;

	// Lire les commandes depuis les arguments de la ligne de commande et les ajouter à la liste
	for (int i = 1; i < argc; i++) {
		// Ajouter une nouvelle commande à la liste
		t_commande *new_cmd = malloc(sizeof(t_commande));
		new_cmd->cmd = ft_strdup("cd"); // Pour tester la commande cd
		new_cmd->args = malloc(sizeof(t_args));
		new_cmd->args->arg = ft_strdup(argv[i]); // Utilisez l'argument comme argument pour cd
		new_cmd->args->next = NULL;
		new_cmd->fdin = NULL;
		new_cmd->fdout = NULL;
		new_cmd->next = NULL;

		// Ajouter la nouvelle commande à la fin de la liste
		if (cmd_lst == NULL) {
			cmd_lst = new_cmd;
		} else {
			t_commande *temp = cmd_lst;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = new_cmd;
		}

		// Afficher la commande ajoutée pour vérification
		printf("Commande ajoutée: %s\n", argv[i]);
	}

//	// Initialiser la liste d'environnement (env_copy) avec des valeurs par défaut
//	add_node_at_end(&env_copy, "HOME", "/home/utilisateur");
//	add_node_at_end(&env_copy, "PWD", "/home/utilisateur");
//	add_node_at_end(&env_copy, "OLDPWD", "/home/utilisateur/ancien");

	// Appeler la fonction builtin_cd avec la première commande de la liste et la liste d'environnement
	builtin_cd(cmd_lst, env_copy);
	// Après avoir appelé votre fonction cd
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Répertoire actuel: %s\n", cwd);
	} else {
		perror("getcwd() error");
	}

	// Libérer la mémoire allouée pour la liste de commandes et la liste d'environnement
	free_cmd_list(cmd_lst);
	free_env_list(env_copy);

	return 0;
}