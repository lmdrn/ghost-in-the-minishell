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

//Recoit le node apres "echo", navigue dans la liste entiere qui touche echo
int	echo(t_commande *cmd_lst, t_environment *env_copy)
{
	int 		option;
	t_commande	*current;

	option = 0;
	if (cmd_lst->args == NULL && !option)
	{
		printf("\n");
		return (0);
	}
	if (cmd_lst != NULL && cmd_lst->args != NULL && cmd_lst->args->arg != NULL)
		option = check_option_n(cmd_lst->args->arg);
	while (cmd_lst->args != NULL && check_option_n(cmd_lst->args->arg) == 1)
			cmd_lst->args = cmd_lst->args->next;
	if (cmd_lst->args == NULL)
		return (0);
	current = cmd_lst; // temp pour paroucrir, on a un new head. on a checker option c'est bon

	//peut etre pas necessaire
	while (current != NULL && current->args != NULL && current->args->arg != NULL)// check si delimiter qui bloque comme pipe
	{
		//si le node aectuel est un delimieur '|'...mais que le suivant n'est pas une commande valide. stop
		// '' '>' et le suivant pas une commande. cree le file
		if (ft_strncmp(current->args->arg, "|", 1) == 0
			|| (ft_strncmp(current->args->arg, ">", 1) == 0)) //(current->type != delimiter)
		{
			printf("bash: erreur de syntaxe, utilisation de delimiteur: `%s'\n", current->args->arg);
			return (1);
		}
		else
			current = current->next;//va aunprochain node
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
	{
		printf("\n");
	}
	return (0);
}

void	ft_echo(char *str, t_environment *env_copy)//ajouter env_copy
{
	int	i;
	char	*value_env;

	i = 0;
	while (str[i])
	{
		/* Valeur de retour de l'action précédente "$?"
		 Check - imprime le retour - continue d'imprimer */
		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("print derrniere error"); // , g_status
			i++;
		}
		/* Interprète une variable d'environnement, par exemple, "$USER" */
		else if (str[i] == '$' && isalnum(str[i + 1]) && str[i + 1] != '\0')
		{
			//char *str_env = &str[i+1];
			if (check_is_in_env(env_copy, str) == ERROR)
				exit(1);
				// de toute facon retour NULL si existe pas
			else
			{
				value_env = get_env_value(env_copy, &str[i + 1]);
				printf("%s", value_env);
			}
		}
		else
		{
			// Afficher le caractère tel quel
			printf("%c", str[i]);
		}
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
