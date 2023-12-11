/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:07:47 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/12 04:26:29 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen_key(char *s)
{
	int i;

	i = 1;
	if (s)
	{
		while (*s)
		{
			if (*s == ' ' || *s == '$' || *s == ';')
				return (i);
			s++;
			i++;
		}
	}
	return (i);
}

void	put_on_new_content(t_cmd_list *tmp, char *value, int d)
{
	int		i;
	int		j;
	char	*new_content;
	int		content_len;
	int		key_len;

	i = 0;
	j = 0;
	content_len = ft_strlen(tmp->content);
	key_len = ft_strlen_key(&tmp->content[d + 1]);
	new_content = (char *)malloc(content_len - key_len + ft_strlen(value) + 1);
	while (tmp->content[j])
	{
		if (tmp->content[j] == '$')
		{
			if (tmp->content[j + 1] != ' ')
			{
				while (*value != '\0')
				{
					new_content[i] = *value;
					value++;
					i++;
				}
				j += key_len;
				if (tmp->content[j - 1] == '\"' || tmp->content[j - 1] == '\'')
					j -= 1;
				key_len = 0;
			}
		}
		new_content[i] = tmp->content[j];
		i++;
		j++;
	}
	free(tmp->content);
	new_content[i] = '\0';
	tmp->content = new_content;
}

void	fix_content(t_cmd_list *tmp, t_env *env)
{
	char		*key;
	t_env		*tmp_env;
	int			i;

	i = 0;
	tmp_env = env;
	key = NULL;
	while (tmp->content[i])
	{
		if (tmp->content[i] == '$' && tmp->content[i + 1] != ' ')
		{
			key = (char *)malloc(ft_strlen_key(&tmp->content[i + 1]));
			ft_strlcpy(key, &tmp->content[i + 1],
			ft_strlen_key(&tmp->content[i + 1]));
			while (tmp_env)
			{
				if (ft_strncmp(key, tmp_env->key,
				ft_strlen(tmp_env->key)) == 0)
					put_on_new_content(tmp, tmp_env->value, i);
				tmp_env = tmp_env->next;
			}
			free(key);
			tmp_env = env;
		}
		i++;
	}
}
