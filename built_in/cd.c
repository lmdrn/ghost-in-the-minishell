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
	int	i;

	i = 0;
	if (env_copy == NULL)
		return (NULL);
	while (env_copy[i].key != NULL)
	{
		if (ft_strcmp(env_copy[i].key, "HOME") == 0)
			return (env_copy[i].value);
		i++;
	}
	return (NULL); // HOME n'est pas défini
}

static int	check_args_cd(t_commande *cmd_lst)
{
	t_commande	*current;
	t_commande	*temp;
	t_args		*args;
	int			i;

	current = cmd_lst;
	temp = cmd_lst;
	i = 0;
	if (current != NULL)
	{
		args = current->args;
		while (args != NULL)
		{
			i++;
			args = args->next;
		}
		if (i > 1)
		{
			printf("\ntrop d'argumetns\n");
			return (-1);
		}
		else if (i == 1)
		{
			printf("\n bien un seul argument\n");
			return (10);
		}
		current = temp;
		if (current->args == NULL )// a voir si on place plus haut avant la boucle de current..pas nesoin temp
		{
			printf("il n'y a aucuuuun arguments, ok");
			return (0);
		}
		if (ft_strcmp(current->args->arg, "~") == 0)//&& current->args->arg[1] == '\0')
		{
			printf("il y a le tild, ok");
			return (0);
		}
		if (ft_strcmp(current->args->arg, "..") == 0)
		{
			// remonter d'un répertoire
			//ft-cd? faut que ca upDATE
			printf("\n je suis bien chez ..\n");
			if (chdir("..") != 0)
			{
				printf("cd: Failed to change directory");
				return (ERROR);
			}
			else
			{
				printf("\n je suis recul´´d'un cran normalement, reste a upload la nouvel position\n");
				return (6);
			}
		}
		else
			return (9);
	}
	else
	{
		printf("current est NULL, ok");
		return (-1); // Ajout du return ici pour le cas où current est NULL
	}
}

int	ft_cd(t_environment *env_copy, char *path)
{
	//gerer les ..
	if (check_path(path) == ERROR)
		return (ERROR);
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

int	builtin_cd(t_commande *cmd_lst, t_environment *env_copy)
{
	char	*home;
	int		arg;

	arg = 0;
	home = NULL;
	//t_environment *current = env_copy;
	//trop d'arguments
	arg = check_args_cd(cmd_lst);
	printf("\n voici la valeur de arg avabt traitment %d\n", arg);
	//plus de 1 arguments
	if (arg == -1)
	{
		printf("cd: too many arguments\n");
		return (ERROR);
	}
	//pas acces à home
	home = get_home(env_copy);
	if (home == NULL)
	{
		printf("cd: Home not set\n");
//		free(home);
		return (ERROR);
	}
	//doit retourner a la racine
	if (arg == 0)
	{
		//leaks peut pas aller vers go home
		home = get_home(env_copy);//check ici
		if (home == NULL)
		{
			printf(" la maison c'est null \n");
			return (ERROR);
		}
		if (go_home(env_copy, home) == ERROR) // ici probleme 2e cd
		{
			printf("\n can't go home\n");
			//free(home);
			return (ERROR);
		}
		//free(home);
		return (SUCCESS);
	}
	if (arg == 1)
	{
		if (ft_cd(env_copy, cmd_lst->args->arg) == ERROR)
		{
			printf("path to file doesn't exist");
			free(home);
			home = NULL;
			return (ERROR);
		}
	}
	if (arg == -1)
	{
		printf("\n trop d'arguments ca marche po\n");
		free(home);
		return (ERROR);
	}
	ft_cd(env_copy, cmd_lst->args->arg);// iciiii prend pas en compte si cd sans argument...va pas au bonne nedroit
	return (SUCCESS);
}
