/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:54:02 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 18:20:41 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_args_pwd(t_commande *cmd_lst)
{
	t_commande *current;

	current = cmd_lst;
	if (cmd_lst != NULL && cmd_lst->next == NULL)
	{
		if (cmd_lst->args == NULL ) //|| (current->args->next == NULL && current->args->arg[0] == '\0')
		{
			while (current->args != NULL && ((current->args->arg[0] == ' ')
					|| (current->args->arg[0] == '\t')))
			{
				current->args = current->args->next;
			}
			if (current->args == NULL)
				return (SUCCESS);
			else
				return (ERROR);
		}
		else
		{
			printf("Erreur : La commande 'pwd' ne doit pas avoir d'options ou d'arguments.\n");
			return (ERROR);
		}
	}
	printf("Erreur : La commande 'pwd' ne doit pas être suivie d'autres commandes.\n");
	return (ERROR);
}

/* print direct depuis getcwd ou lire la liste..?*/

int	builtin_pwd( t_commande *cmd_lst)
{
	char	*actual_pwd;

	actual_pwd = getcwd(NULL, 0);
	if (actual_pwd != NULL)
	{
		if (check_args_pwd(cmd_lst) == SUCCESS)
		{
			printf("vous êtes ici : %s\n", actual_pwd);
			return (SUCCESS);
		}
		else
		{
			printf("error ici de pwd, trop de arg");
			return (ERROR);
		}
		//perror
		free (actual_pwd);
	}
	else
	{
		printf("error pas acces a pwd");
		return (ERROR);
	}
}

void	update_pwd_oldpwd(t_environment *env_copy, char *change_pwd)
{
	char	*current_pwd;
	char	*old_pwd;
	t_environment *current;

	current = env_copy;
	old_pwd = NULL;
	current_pwd = NULL;
	current_pwd = getcwd(NULL, 0);
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			old_pwd = ft_strdup(current->value);
			free(current->value); // Libérer l'ancienne valeur
			current->value = ft_strdup(change_pwd); // Mettre à jour la valeur (ignorer le premier caractère)
			break ;
		}
		current = current->next;
	}
	current = env_copy;
	while (current->key != NULL)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
		{
			free(current->value); // Libérer l'ancienne valeur
			current->value = ft_strdup(old_pwd); // Mettre à jour la valeur
			break ;
		}
		current = current->next;
	}
	// Libérer la mémoire allouée par getcwd, strjoin
	free(current_pwd);
	//free (old_pwd);
}
