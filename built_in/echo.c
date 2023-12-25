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
int handle_option_n_and_advance_args(t_commande **cmd_lst)
{
	int option = 0;

	if (*cmd_lst != NULL && (*cmd_lst)->args != NULL && (*cmd_lst)->args->arg != NULL)
		option = check_option_n((*cmd_lst)->args->arg);

	while ((*cmd_lst)->args != NULL && check_option_n((*cmd_lst)->args->arg) == 1)
		(*cmd_lst)->args = (*cmd_lst)->args->next;

	return option;
}

int print_args_and_check_syntax(t_commande *cmd_lst, t_environment *env_copy, int option)
{
	t_commande *current = cmd_lst;
	while (current != NULL && current->args != NULL && current->args->arg != NULL) {
		if (ft_strncmp(current->args->arg, "|", 1) == 0 ||
			ft_strncmp(current->args->arg, ">", 1) == 0) {
			printf("bash: erreur de syntaxe `%s'\n", current->args->arg);
			return (1);
		}
		else
			current = current->next;
	}

	return print_echo_arguments(cmd_lst, env_copy, option);
}

int print_echo_arguments(t_commande *cmd_lst, t_environment *env_copy, int option)
{
	while (cmd_lst->args != NULL && cmd_lst->args->arg != NULL)
	{
		ft_echo(cmd_lst->args->arg, env_copy);
		if (cmd_lst->args->next != NULL)
			printf(" ");
		cmd_lst->args = cmd_lst->args->next;
	}

	if (!option) {
		printf("\n");
	}
	return (0);
}

int echo(t_commande *cmd_lst, t_environment *env_copy) {
	int option = handle_option_n_and_advance_args(&cmd_lst);

	if (cmd_lst->args == NULL && !option) {
		printf("\n");
		return (0);
	}

	return (print_args_and_check_syntax(cmd_lst, env_copy, option));
}



//int	echo(t_commande *cmd_lst, t_environment *env_copy)
//{
//	int			option;
//	t_commande	*current;
//
//	option = 0;
//	if (cmd_lst->args == NULL && !option)
//	{
//		printf("\n");
//		return (0);
//	}
//	if (cmd_lst != NULL && cmd_lst->args != NULL && cmd_lst->args->arg != NULL)
//		option = check_option_n(cmd_lst->args->arg);
//	while (cmd_lst->args != NULL && check_option_n(cmd_lst->args->arg) == 1)
//		cmd_lst->args = cmd_lst->args->next;
//	if (cmd_lst->args == NULL)
//		return (0);
//	current = cmd_lst;
//	while (current != NULL && current->args != NULL \
//	&& current->args->arg != NULL)
//	{
//		if (ft_strncmp(current->args->arg, "|", 1) == 0
//			|| (ft_strncmp(current->args->arg, ">", 1) == 0))
//		{
//			printf("bash: erreur de syntaxe `%s'\n", current->args->arg);
//			return (1);
//		}
//		else
//			current = current->next;
//	}
//	current = cmd_lst;
//	while (current->args != NULL && current->args != NULL \
//	&& current->args->arg != NULL)
//	{
//		ft_echo(current->args->arg, env_copy);
//		if (current->args->next != NULL)
//			printf(" ");
//		cmd_lst->args = cmd_lst->args->next;
//	}
//	if (!option)
//	{
//		printf("\n");
//	}
//	return (0);
//}

void	ft_echo(char *str, t_environment *env_copy)
{
	int		i;
	char	*value_env;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			printf("print derrniere error");
			i++;
		}
		else if (str[i] == '$' && isalnum(str[i + 1]) && str[i + 1] != '\0')
		{
			if (check_is_in_env(env_copy, str) == ERROR)
				exit(1);
			else
			{
				value_env = get_env_value(env_copy, &str[i + 1]);
				printf("%s", value_env);
			}
		}
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
