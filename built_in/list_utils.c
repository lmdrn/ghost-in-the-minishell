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
//int find_index(t_node *head, int target_index)
//{
//	int i = 0;
//	t_node *current = head;
//
//	while (current != NULL)
//	{
//		if (current->index == target_index)
//			return i;  // Index trouvé, renvoie le nombre de nœuds parcourus
//		current = current->next;
//		i++;
//	}
//
//	return -1; // Index non trouvé dans la liste
//}

void add_node(t_environment **env_copy, char *key, char *value)
{
	t_environment *new_node;

	new_node = (t_environment *)malloc(sizeof(t_environment));
	if (new_node == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire pour le nouveau nœud\n");
		exit(EXIT_FAILURE);
	}
	new_node->key = strdup(key);
	new_node->value = strdup(value);
	if (new_node->key == NULL || new_node->value == NULL)
	{
		fprintf(stderr, "Erreur d'allocation mémoire pour les champs key ou value\n");
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	if (*env_copy == NULL)
		*env_copy = new_node;
	else
		last_node(*env_copy)->next = new_node;
}

void fill_node(t_environment *env_copy)
{

//	new_node->key = strdup(key);
//	new_node->value = strdup(value);
//
//
//	if (new_node->key == NULL || new_node->value == NULL)
//	{
//		fprintf(stderr, "Erreur d'allocation mémoire pour les champs key ou value\n");
//		exit(EXIT_FAILURE);
//	}
}


void    print_nodes(t_environment **node, char c)// print la liste, t_pushswap *ps
//imprime mm les node(0)
{
	//int i;
	t_node *current_node;

	current_node = *node;
	//i = 0;
	printf("Liste %c\n",c);
	if (current_node == NULL)
		ft_printf("c'est vide\n");
	while (current_node!= NULL)//ici changer , avant current_node ->next
	{

		printf("node(%d)->data = %d\n",current_node->index , current_node->data);
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