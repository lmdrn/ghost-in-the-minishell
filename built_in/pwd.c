#include "../minishell.h"

int check_args_pwd(t_commande *cmd_lst);
int builtin_pwd( t_commande *cmd_lst);



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
