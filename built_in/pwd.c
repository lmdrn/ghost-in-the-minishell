#include "../minishell.h"
//censé pouvoir donner pwd si on unset...pwd?


// Déclarations des prototypes de fonction
void free_env_list(t_environment *head);
void free_cmd_list(t_commande *head);
int check_args_pwd(t_commande *cmd_lst);
int builtin_pwd( t_commande *cmd_lst);
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


int check_args_pwd(t_commande *cmd_lst)
{
	t_commande *current = cmd_lst;

	if (cmd_lst != NULL && cmd_lst->next == NULL)
	{
		if (cmd_lst->args == NULL ) //|| (current->args->next == NULL && current->args->arg[0] == '\0')
		{
			while (current->args != NULL && ((current->args->arg[0] == ' ') || (current->args->arg[0] == '\t')))
			{
				current->args = current->args->next;
			}
			if (current->args == NULL)
				return SUCCESS;
			else
				return (ERROR);
		}
		else
		{
			printf("Erreur : La commande 'pwd' ne doit pas avoir d'options ou d'arguments.\n");
			return ERROR;
		}
	}
	printf("Erreur : La commande 'pwd' ne doit pas être suivie d'autres commandes.\n");
	return ERROR;

}

/* print direct depuis getcwd ou lire la liste..?*/

int	builtin_pwd( t_commande *cmd_lst)
{
	char *actual_pwd;

	actual_pwd = getcwd(NULL, 0);
	if (actual_pwd != NULL)
	{
		if (check_args_pwd(cmd_lst) == SUCCESS)
		{
			printf("vous êtes ici : %s\n", actual_pwd);
			return(SUCCESS);
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//int main() {
//	// Créer un environnement de test avec une valeur bidon
//	t_environment *env_copy = malloc(sizeof(t_environment));
//	env_copy->key = "TEST_ENV";
//	env_copy->value = "test_value";
//	env_copy->next = NULL;
//
//	// Créer une commande avec des arguments valides
//	t_commande *cmd_lst_valid = malloc(sizeof(t_commande));
//	cmd_lst_valid->args = malloc(sizeof(t_args));
//	cmd_lst_valid->args->arg = "";
//	cmd_lst_valid->args->next = NULL;
//
//	// Tester la fonction builtin_pwd avec des arguments valides
//	printf("Testing pwd with valid arguments:\n");
//	builtin_pwd(env_copy, cmd_lst_valid);
//
//	// Créer une commande avec des arguments invalides
//	t_commande *cmd_lst_invalid = malloc(sizeof(t_commande));
//	cmd_lst_invalid->args = malloc(sizeof(t_args));
//	cmd_lst_invalid->args->arg = "invalid_argument";
//	cmd_lst_invalid->args->next = NULL;
//
//	// Tester la fonction builtin_pwd avec des arguments invalides
//	printf("\nTesting pwd with invalid arguments:\n");
//	builtin_pwd(env_copy, cmd_lst_invalid);
//
//	// Libérer la mémoire allouée
//	free_env_list(env_copy);
//	free_cmd_list(cmd_lst_valid);
//	free_cmd_list(cmd_lst_invalid);
//
//	return 0;
//}
