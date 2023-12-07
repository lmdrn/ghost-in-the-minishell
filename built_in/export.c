#include "../minishell.h"
int check_is_in_env(t_environment *env_copy, char *var);
void add_node_at_end(t_environment *head, char *key, char *value);

int builtin_export(t_environment *env_copy, t_commande *cmd_lst)
{

}