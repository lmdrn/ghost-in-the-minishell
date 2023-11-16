#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
 // char		c; stock env
 // je reprend env ou je prend moi meme
//char **env_copy

 int check_args(t_commande *cmd_lst);
int	change_directories(char *str)
int check_path(char *str);
void add_in_env(char ***env_copy, const char *var);

/*
 * strjoin PWD + new path
 * strjoin oldpwd+ old path
 * update pwd ->old
 * home ->pwd
 */

int check_is_in_env(char **env_copy, char *var)
{
	int length;
	int i;

	i = 0;
	length = ft_strlen(var);
	while (env_copy)
	{
		if (ft_strncmp(env_copy[i], var, length) == 0)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

void add_in_env(char ***env_copy, char *var)
{
	// Parcourir le tableau pour trouver la première ligne vide
	int i = 0;
	while ((*env_copy)[i] != NULL) {
		if ((*env_copy)[i][0] == '\0') {
			// Ligne vide trouvée, libérer la mémoire associée
			free((*env_copy)[i]);
			break;
		}
		i++;
	}

	// Vérifier s'il n'y a pas de ligne vide
	if ((*env_copy)[i] == NULL) {
		fprintf(stderr, "Erreur : Aucune ligne vide disponible dans le tableau.\n");
		exit(EXIT_FAILURE);
	}

	// Allouer de la mémoire pour la nouvelle variable
	(*env_copy)[i] = strdup(var);
	if ((*env_copy)[i] == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
}

void update_pwd_oldpwd(char **env_copy, char *change_pwd)
{
	char *current_pwd;
	char *old_pwd;
	char *new_pwd;

	current_pwd = getcwd(NULL, 0);
	//fail possible?
	new_pwd = ft_strjoin("PWD=",change_pwd);
	old_pwd = ft_strjoin("OLDPWD=",current_pwd);
	if (check_is_in_env(env_copy, "PWD") == ERROR)
		add_in_env(env_copy, new_pwd);
	//else cherche la ligne avec pwd et change


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
/* retourne 0 pour mener à HOME, -1 si erreur et autre si ok*/
int check_args(t_commande *cmd_lst)
{
	t_commande *current = cmd_lst;
	int	i;

	if ((current->args->arg == NULL) || (current->args->arg == '~'))
		return(0);
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

int go_home(char **env_copy, char *home)
{
	if (chdir(home) != 0)
	{
		printf ("cd: Home non accessible");
		return (ERROR);
	}
	else
		update_pwd_oldpwd(env_copy, home);
	return (SUCCESS);
}

int builtin_cd(t_commande *cmd_lst, char **env_copy)
{
	char *home;
	int arg;

	if ((arg = check_args(cmd_lst)) == -1)
	{
		printf("cd: too many arguments\n")
		return (ERROR);
	}
	if ((home = get_home(env_copy)) == NULL)
	{
		printf("cd: Home not set\n");
		return (ERROR);
	}
	else if (arg == 0)
	{
		if (go_home(env_copy, home));

	}

}