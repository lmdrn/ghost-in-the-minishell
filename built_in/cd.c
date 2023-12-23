/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:37 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 18:13:40 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_args_cd(t_commande *cmd_lst);

int	go_home(t_environment *env_copy, char *home)
{
	update_pwd_oldpwd(env_copy, home);// on tente car tojour suodate a home
	if (chdir(home) != 0)
	{
		printf ("cd: Home non accessible");
		//free(home);
		//home == NULL;
		return (ERROR);
	}
	else
	{
		printf("\n on rentre a la maisonnn\n");
		return (SUCCESS);
	}
}

char	*get_home(t_environment *env_copy)
{

	t_environment *current;

	current = env_copy;
	if (env_copy == NULL)
	{
		printf("Home est nulle\n");
		return (NULL);
	}
	while (current!= NULL)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL); // HOME n'est pas défini
}

int count_args_cd(t_commande *cmd_lst)
{
	t_commande *current;
	current = cmd_lst;
	t_args  *args;
	int i = 0;
	if (current != NULL)
	{
		args = current->args;
		while (args != NULL)
		{
			i++;
			args = args->next;
		}
		return (i);
	}
	return (ERROR);
}
static int	check_args_cd(t_commande *cmd_lst)
{
	t_commande	*current;
	int			i;

	current = cmd_lst;
	i = 0;
	if (current != NULL)// avant if
	{
		i = count_args_cd(cmd_lst);
		printf("\n\nvaleur de nombre d'arguments %i\n", i);
		if (i > 1)
		{
			g_status= 1;
			//exit? ou pourrait arreter depuis ici
			printf("\ntrop d'argumetns\n");
			return (ERROR); // ou -1
		}
		if (i == 1)
			is_one_arg(i, cmd_lst);
		//		else if (i == 1)
		//		{
		//			if (ft_strcmp(cmd_lst->args->arg, "..") == 0)
		//			{
		//				printf("on recule de 1 dossier \n");
		//				return(2);
		//			}
		//			printf("\n bien un seul argument\n");
		//			return (10);
		//		}
		//		current = temp;
		ticket_going_home(cmd_lst);
	//		if (current->args == NULL )// a voir si on place plus haut avant la boucle de current..pas nesoin temp
	//		{
	//			printf("il n'y a aucuuuun arguments, ok");
	//			return (0);
	//		}
	//		if (ft_strcmp(current->args->arg, "~") == 0)//&& current->args->arg[1] == '\0')
	//		{
	//			printf("il y a le tild, ok");
	//			return (0);
	//		}
		// .. a voir si celui au dessus suffit
//		if (ft_strcmp(current->args->arg, "..") == 0)
//		{
//			// remonter d'un répertoire
//			//ft-cd? faut que ca upDATE
//			printf("\n je suis bien chez ..\n");
//			if (chdir("..") != 0)
//			{
//				printf("cd: Failed to change directory");
//				return (ERROR);
//			}
//			else
//			{
//				printf("\n je suis recul´´d'un cran normalement, reste a upload la nouvel position\n");
//				return (6);
//			}
	}
	return (ERROR);
}

int	ft_cd(t_environment *env_copy, char *path, int path_back)
{
	//gerer les ..
	if (check_path(path) == ERROR)
	{
		printf("error path\n");
		return (ERROR);
	}
	if (path_back == 1)
	{
		path = go_back_directories(path);
	}
	update_pwd_oldpwd(env_copy, path);
	if (check_is_in_env(env_copy, "PWD") == ERROR)
		printf("Adding PWD to env_copy\n");
//		add_node_at_end(env_copy, "PWD", "");
	if (check_is_in_env(env_copy, "OLDPWD") == ERROR)
		printf("Adding OLDPWD to env_copy\n");
//		add_node_at_end(env_copy, "OLDPWD", "");
	if (chdir(path) != 0)//capibara
	{
		printf("cd: Failed to change directory");
		return (ERROR);
	}
	return (SUCCESS);
}

int is_one_arg(int nb_args, t_commande *cmd_lst)
{
	if (nb_args == 1)
	{
		if (ft_strcmp(cmd_lst->args->arg, "..") == 0)
		{
			printf("on recule de 1 dossier \n");
			return(2);
		}
		printf("\n bien un seul argument\n");
		return (3);

	}
	else
		return(ERROR);//sure?
}


char *go_back_directories(char *path)
{
	char *last_slash;
	char *result;
	int len;

	last_slash = ft_strrchr(path, '/');
	if (last_slash != NULL)
	{
		len = last_slash - path;
		result = ft_substr(path, 0, len);
		return (result);
	}
	else
	{
		return ft_strdup(path);
	}
}

int	ticket_going_home(t_commande *cmd_lst)
{
	t_commande *current;
	current = cmd_lst;

	if (current->args == NULL )
	{
		printf("il n'y a aucuuuun arguments, ok\n");
		return (1);
	}
	else if (ft_strcmp(current->args->arg, "~") == 0)//&& current->args->arg[1] == '\0')
	{
		printf("il y a le tild, ok");
		return (1);
	}
	else
		return (ERROR);
}
 /*
  * == 0 ERROR
  * > 1 erreurs trop d'arguments. -> sortie
  * == 1 , aucun argument ou tild, retour a Home
  * == 2 , ".." on recule de 1 repertoire
  * == 3, bien un seul argument ->execute
  */



int	builtin_cd(t_commande *cmd_lst, t_environment *env_copy)
{
	char	*home;
	int		arg_check;
	int path_back;

	arg_check = 0;
	home = NULL;
	path_back = 0;
	//t_environment *current = env_copy;

	arg_check = check_args_cd(cmd_lst);// check les arguments

	printf("\n nombre d;argument %d\n", arg_check);
	// a voir si dans check_arg pas sortir de suite ou pas
	if (arg_check == ERROR)
	{
		printf("cd: too many arguments\n");
		//free home?
		return (ERROR);
	}

		//leaks peut pas aller vers go home
	home = get_home(env_copy);//check ici
	if (home == NULL)
	{
		printf("cd: Home not set\n");
		return (ERROR);
	}
	if (arg_check == 1)
		if (go_home(env_copy, home) == ERROR) // ici probleme 2e cd
		{
			printf("\n can't go home\n");
			//free(home);
			return (ERROR);//g_status
		}
	if (arg_check == 2 )
	{
		path_back= 1;
	}
	 if (ft_cd(env_copy, cmd_lst->args->arg, path_back) == ERROR)
		{
			printf("path to file doesn't exist");
			free(home);
			home = NULL;
			return (ERROR);
		}

	//ft_cd(env_copy, cmd_lst->args->arg, path_back);// iciiii prend pas en compte si cd sans argument...va pas au bonne nedroit
	return (SUCCESS);
}
