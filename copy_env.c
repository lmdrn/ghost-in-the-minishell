/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:49:26 by lmedrano          #+#    #+#             */
/*   Updated: 2023/12/29 13:01:21 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_count_array(char **envp)
{
	int		env_count;

	env_count = 0;
	while (envp[env_count] != NULL)
		env_count++;
	return (env_count);
}

int	env_count_lst(t_environment *env)
{
	int				count;
	t_environment	*current;

	current = env;
	count = 0;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**allocate_mem_x_env_array(int count)
{
	char	**envp;

	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
	{
		perror("Mem alloc failed\n");
		return (NULL);
	}
	return (envp);
}

void	copy_to_buffer(char *dest, const char *key, const char *value)
{
	while (*key != '\0')
	{
		*dest = *key;
		dest++;
		key++;
	}	
	*dest = '=';
	dest++;
	while (*value != '\0')
	{
		*dest = *value;
		dest++;
		value++;
	}
	*dest = '\0';
}

void	copy_key_value_pair(t_environment *env, int count, char **envp)
{
	t_environment	*curr;
	int				i;
	int				len;

	i = 0;
	curr = env;
	while (i < count)
	{
		len = ft_strlen(curr->key) + ft_strlen(curr->value) + 2;
		envp[i] = (char *)malloc(len);
		if (envp[i] == NULL)
		{
			perror("Mem alloc failed\n");
			exit(EXIT_FAILURE);
		}
		copy_to_buffer(envp[i], curr->key, curr->value);
		curr = curr->next;
		i++;
	}
}

/* void	print_envp(char **envp) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	while (envp[i] != NULL) */
/* 	{ */
/* 		printf("K/V is %s\n", envp[i]); */
/* 		i++; */
/* 	} */
/* } */

char	**env_list_to_array(t_environment *env)
{
	int				count;
	char			**envp;	

	count = env_count_lst(env);
	envp = allocate_mem_x_env_array(count);
	copy_key_value_pair(env, count, envp);
	envp[count] = NULL;
	/* print_envp(envp); */
	return (envp);
}
