/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 09:53:48 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 18:18:47 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_commande *cmd_lst, t_environment *env_copy)
{
	int 		option;
	t_commande	*current;

	option = 0;
	if (cmd_lst != NULL && cmd_lst->args != NULL && cmd_lst->args->arg != NULL)
		option = check_option_n(cmd_lst->args->arg);
	else
		return (ERROR);
	while (check_option_n(cmd_lst->args->arg) == 1)
			cmd_lst->args = cmd_lst->args->next;
	current = cmd_lst; // temp pour paroucrir, on a un new head. on a checker option c'est bon

	//peut etre pas necessaire
	while (current != NULL && current->args != NULL && current->args->arg != NULL)// check si delimiter qui bloque comme pipe
	{
		if (ft_strncmp(current->args->arg, "|", 1) == 0
			|| (ft_strncmp(current->args->arg, ">", 1) == 0)) //(current->type != delimiter)
		{
			printf("bash: erreur de syntaxe, utilisation de delimiteur: `%s'\n", current->args->arg);
			return (1);
		}
		else
			current = current->next;
	}
	current = cmd_lst;
	while (current->args != NULL && current->args != NULL && current->args->arg != NULL)// on print
	{
		ft_echo(current->args->arg, env_copy);
		if (current->args->next != NULL)
			printf(" ");// si nbre de node non final
		cmd_lst->args = cmd_lst->args->next;//bouge
	}
	if (!option)
		printf("\n");
	return (0);
}

int	check_$_arg(char *str, t_environment *env_copy)
{
	int	i;
	char	*value_env;

	i = 0;
//	while (str[i])
//	{
		if (str[i] == '$' && str[i + 1] == '?') {
			printf("print derrniere error"); // , g_status
			i++;
		}
			/* Interprète une variable d'environnement, par exemple, "$USER" */
		else if (str[i] == '$' && isalnum(str[i + 1]) && str[i + 1] != '\0')
		{
			//char *str_env = &str[i+1];
			if (check_is_in_env(env_copy, str) == ERROR)
				return (ERROR);
				// de toute facon retour NULL si existe pas
			else {
				value_env = get_env_value(env_copy, &str[i + 1]);
				printf("%s", value_env);
			}
		}
		return (SUCCESS);

	}
//	return (ERROR);//? sur?
//}

void	ft_echo(char *str, t_environment *env_copy)//ajouter env_copy
{
	int	i;
	//char	*value_env;

	i = 0;

		/* Valeur de retour de l'action précédente "$?"
		 Check - imprime le retour - continue d'imprimer */
	while (str[i])
	{
		if (check_$_arg(str, env_copy) == ERROR)
			return;
//		if (str[i] == '$' && str[i + 1] == '?')
//		{
//			printf("print derrniere error"); // , g_status
//			i++;
//		}
//		/* Interprète une variable d'environnement, par exemple, "$USER" */
//		else if (str[i] == '$' && isalnum(str[i + 1]) && str[i + 1] != '\0')
//		{
//			//char *str_env = &str[i+1];
//			if (check_is_in_env(env_copy, str) == ERROR)
//				exit(1);
//				// de toute facon retour NULL si existe pas
//			else
//			{
//				value_env = get_env_value(env_copy, &str[i + 1]);
//				printf("%s", value_env);
//			}
//		}
		else
			printf("%c", str[i]);
		i++;
	}
}

int	check_option_n(char *str) // verifie si le node apres echo est une option
{
	int	i;

	i = 0;
	if (!str)
		return (ERROR);
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] == 'n')
		return (1);
	return (0);
}
