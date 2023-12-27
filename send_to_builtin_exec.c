/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_to_builtin_exec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:38:58 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/20 10:12:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void    print_nodes_a(t_environment *node)// print la liste, t_pushswap *ps
{
	t_environment *current_node;

	current_node = node;
	printf("Liste \n");
	if (current_node == NULL)
		printf("c'est vide\n");
	while (current_node!= NULL)//ici changer , avant current_node ->next
	{

		printf("key (%s)->value = %s\n",current_node->key , current_node->value);
		//printf ("adresse du node %p\n", current_node->next);
		current_node = current_node->next;
		//i++;
	}
}
void free_cmd_lst(t_commande *cmd) {
	if (cmd == NULL) {
		return;
	}

	// Libérer la chaîne de commande
	if (cmd->cmd != NULL) {
		free(cmd->cmd);
	}

	// Libérer la liste des arguments
	t_args *current = cmd->args;
	while (current != NULL) {
		t_args *next = current->next;
		if (current->arg != NULL) {
			free(current->arg); // Libérer la chaîne de l'argument
		}
		free(current); // Libérer le nœud d'argument
		current = next;
	}

	// Finalement, libérer la structure de commande elle-même
	free(cmd);
}

t_commande *create_cmd_lst_node(const char *command, const char *argument) {
	t_commande *node = malloc(sizeof(t_commande));
	if (node == NULL) {
		// Gérer l'erreur d'allocation ici
		return NULL;
	}

	node->cmd = strdup(command);
	if (node->cmd == NULL) {
		// Gérer l'erreur d'allocation ici
		free(node);
		return NULL;
	}

	// Création du premier argument
	node->args = malloc(sizeof(t_args));
	if (node->args == NULL) {
		// Gérer l'erreur d'allocation ici
		free(node->cmd);
		free(node);
		return NULL;
	}

	node->args->arg = strdup(argument);
	if (node->args->arg == NULL) {
		// Gérer l'erreur d'allocation ici
		free(node->args);
		free(node->cmd);
		free(node);
		return NULL;
	}
	node->args->type = 0;  // Définir le type si nécessaire
	node->args->next = NULL;

	return node;
}

// N'oubliez pas de libérer la mémoire correctement


void	which_builtin(t_commande *cmd_lst, t_environment *env_copy)
{
	(void)cmd_lst;
	t_commande *cmd_lst_factice = create_cmd_lst_node("cd", "~");
	if (ft_strncmp(cmd_lst->cmd, "echo", 4) == 0)
		echo(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "pwd", 3) == 0)
		builtin_pwd(cmd_lst);
	else if (ft_strncmp(cmd_lst->cmd, "cd", 2) == 0)
	{
		//print_command_list(cmd_lst);
//		printf("la valeur de l'argument %s\n", cmd_lst_factice->args->arg);
		builtin_cd(cmd_lst_factice, env_copy);
	}
	else if (ft_strncmp(cmd_lst->cmd, "export", 6) == 0)
		export_main(cmd_lst, env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "unset", 5) == 0)
		printf("UNSET function should happen here\n");
	else if (ft_strncmp(cmd_lst->cmd, "env", 3) == 0)
		print_env_builtin(env_copy);
	else if (ft_strncmp(cmd_lst->cmd, "exit", 4) == 0)
		printf("EXIT function should happen here\n");
	else
		printf("error happened\n");
	free_cmd_lst(cmd_lst_factice);
}
