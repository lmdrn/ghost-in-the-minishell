#include "../minishell.h"

int    list_size(t_environment *node) // op -push
{
	int i;

	i = 0;
	while(node != NULL)
	{
		i++;
		node = node->next;
	}
	return(i);

}

void add_node(t_environment **env_copy, char *key, char *value)
{
	t_environment *new_node = (t_environment *)malloc(sizeof(t_environment));
	if (new_node == NULL) {
		fprintf(stderr, "Erreur d'allocation mémoire pour le nouveau nœud\n");
		exit(EXIT_FAILURE);
	}

	new_node->key = strdup(key);
	new_node->value = NULL;//init
	int value_switch = 0;
	if (value != NULL)
	{
		new_node->value = strdup(value);
		value_switch = 1;
	}


	// Gestion d'erreur si l'une des allocations échoue
	if (value_switch == 0)
		free(new_node->value); // Libérer value si elle a été allouée
	if (new_node->key == NULL && new_node->value == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire pour les champs key ou value\n");
		free(new_node->key); // Libérer key si elle a été allouée
//		if (value_switch == 1)
//			free(new_node->value); // Libérer value si elle a été allouée
		free(new_node); // Libérer le nœud lui-même
		exit(EXIT_FAILURE);
	}

	new_node->next = NULL;

	if (*env_copy == NULL) {
		*env_copy = new_node;
	} else {
		t_environment *last = last_node(*env_copy);
		last->next = new_node;
	}
}

void printCommandList(t_commande *cmdList)
{
	t_commande *current = cmdList;

	while (current != NULL) {
		printf("Command: %s\n", current->cmd);

		// Imprimer les arguments
		t_args *args = current->args;
		while (args != NULL) {
			printf("  Arg: %s\n", args->arg);
			args = args->next;
		}


		printf("\n");

		// Passer à la commande suivante dans la liste
		current = current->next;
	}
}

void    print_nodes(t_environment **node, char c)// print la liste, t_pushswap *ps
//imprime mm les node(0)
{
	//int i;
	t_environment *current_node;

	current_node = *node;
	//i = 0;
	printf("Liste %c\n",c);
	if (current_node == NULL)
		printf("c'est vide\n");
	while (current_node!= NULL)//ici changer , avant current_node ->next
	{

		printf("node(%s)->data = %s\n",current_node->key , current_node->value);
		//printf ("adresse du node %p\n", current_node->next);
		current_node = current_node->next;
		//i++;
	}
}

t_environment 	*last_node(t_environment *head)
{
	if (!head)//secu si existe pas
		return (NULL);
	while (head->next != NULL) // tant que le pointeur du prochain n'est pas null, donc pas fin
		head = head->next; // passe au prochain
	return (head); //retourne l'adresse du node et pas du pointeur
}