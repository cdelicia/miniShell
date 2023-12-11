/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:16:08 by kcedra            #+#    #+#             */
/*   Updated: 2019/11/11 00:16:33 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_path	*ft_pathnew(char *path)
{
	t_path	*new_path;
	char	*content;

	new_path = (t_path*)malloc(sizeof(t_path));
	if (new_path == NULL || path == NULL)
		return (NULL);
	content	= ft_strdup(path);
	new_path->path = content;
	new_path->next = NULL;
	return (new_path);
}

void			path_init(t_path **path, t_env *env)
{
	int		i;
	char	*content;
	char	**array;
	t_path	*head;

	content = NULL;
	while (env != NULL)
	{
		if (ft_strncmp("PATH", env->key, 5) == 0)
		{
			content = env->value;
			break ;
		}
		env = env->next;
	}
	if (content == NULL)
		*path = NULL;
	else
	{
		array = ft_split(content, ':');
		i = 0;
		head = ft_pathnew(array[i]);
		*path = head;
		i++;
		while (array[i] != NULL)
		{
			head->next = ft_pathnew(array[i]);
			head = head->next;
			i++;
		}
		i = -1;
		while (array[++i] != NULL)
			free(array[i]);
		free(array);
	}
}
