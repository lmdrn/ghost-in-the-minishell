#include "../minishell.h"

void ft_echo(char *str);
int check_option_n(char *str);
int echo(t_commande *cmd_lst);

int check_option_n(char *str) // verifie si le node apres echo est une option
{
	int i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i]== '-' && str[i+1] == 'n')
			return (1);
	return (0);
}

int echo(t_commande *cmd_lst) // recoit le node apres "echo", navigue dans la liste entiere qui touche echo
{
	int option;

	option = 0;
	if (cmd_lst->args == NULL)
	{
		printf("\n");
		return (SUCCESS);
	}
	option = check_option_n(cmd_lst->args->arg);

	//check tant que c'est une option

	while (cmd_lst->args != NULL && check_option_n(cmd_lst->args->arg) == 1)
		cmd_lst->args = cmd_lst->args->next;
	if (cmd_lst->args == NULL && option == 1)// pour si que -n mais marche po
	{
		printf("");
		return (SUCCESS);
	}

	t_commande *current = cmd_lst; // temp pour paroucrir, on a un new head. on a checker option c'est bon

	while (current != NULL)// check si delimiter qui bloque comme pipe
	{
		//si le node aectuel est un delimieur '|'...mais que le suivant n'est pas une commande valide. stop
		// '' '>' et le suivant pas une commande. cree le file
		if (ft_strncmp(current->args->arg, "|", 1) == 0 || (ft_strncmp(current->args->arg, ">", 1) == 0))//(current->type != delimiter)
		{
			printf("bash: erreur de syntaxe ,utilisation de delimiteur: `%s'\n", current->args->arg);
			return (ERROR);

		}
		else
			current = current->next;//va aunprochain node
	}
	current = cmd_lst;
	while (current->args != NULL)// on print
	{
		ft_echo(current->args->arg);
		if (current->args->next != NULL)
			printf(" ");// si nbre de node non final
		cmd_lst->args = cmd_lst->args->next;//bouge
	}
	if (!option)
	{
		printf("\n");
	}
	return (SUCCESS);
}

void ft_echo(char *str)
{
	int i = 0;
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
		else if (str[i] == '$' && isalnum(str[i + 1]) )
		{
			char *str_env = &str[i+1];
			char *check_env = getenv(str_env);
			// de toute facon retour NULL si existe pas

			if (check_env)
				printf("%s", str_env);
		}
		else
		{
			// Afficher le caractère tel quel
			printf("%c", str[i]);
		}
		i++;
	}
}



//int main() {
//	// Initialisation des structures
//	t_commande command1;
//	t_args arg1, arg2, arg3;
//
//	// Assignation des valeurs
//	command1.cmd = strdup("echo"); // Utilisez votre propre fonction de duplication si nécessaire
//	command1.next = NULL; // Pas d'autres commandes
//
//	arg1.arg = strdup("-nnnnnnn");
//	arg1.next = &arg2; // Pointe vers le prochain argument
//
//	arg2.arg = strdup("hello");
//	arg2.next = &arg3; // Pointe vers le prochain argument
//
//	arg3.arg = strdup("-n");
//	arg3.next = NULL; // Dernier argument
//
//	// Lier la liste d'arguments à la commande
//	command1.args = &arg1;
//
//	// Utilisation des structures
//	t_args *current_arg = command1.args;
//	int i = 0;
//	while (current_arg != NULL)
//	{
//
//		printf("node %d %s\n",i++, current_arg->arg);
//		current_arg = current_arg->next;
//	}
//	echo(&command1);
//	// Libération de la mémoire si nécessaire
//	// Assurez-vous de libérer la mémoire pour chaque strdup utilisé précédemment
//	free(command1.cmd);
//	free(arg1.arg);
//	free(arg2.arg);
//	free(arg3.arg);
//
//	return 0;
//}