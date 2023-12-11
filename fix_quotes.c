/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 04:07:05 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/12 06:22:29 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_check_strong_quotes(char *content)
{
	int i;
	int count;
	int weak;

	i = 0;
	weak = 0;
	count = 0;
	while (content[i])
	{
		if (content[i] == '\"')
			weak = 1;
		if (content[i] == '\'' && weak == 0)
			break ;
		i++;
	}
	while (content[i] && weak == 0)
	{
		if (content[i] == '\'')
			count++;
		i++;
	}
	if (count >= 2)
		return (1);
	return (0);
}

char		*delete_quotes(char *line, char q)
{
	int i;

	if (line)
	{
		while (*line == q)
		{
			i = 0;
			while (line[i] != '\0')
			{
				line[i] = line[i + 1];
				i++;
			}
		}
	}
	return (line);
}

void			fix_all_quotes(t_cmd_list *tmp)
{
	int 		i;
	int 		strong;
	char		*new_content;

	i = 0;
	strong = 0;
	while (tmp->content[i] != '\0' && tmp->content[i] != '\'' && tmp->content[i] != '\"')
		i++;
	if (tmp->content[i] == '\'' && strong == 0)
		strong = 1;
	if (tmp->content[i] == '\"' && strong == 0)
		strong = -1;
	if (tmp->content[i] == '\'' && strong == 1)
	{
		new_content = ft_strtrim(tmp->content, "\'");
		free(tmp->content);
		tmp->content = new_content;
	}
	else if (tmp->content[i] == '\"' && strong == -1)
	{
		new_content = ft_strtrim(tmp->content, "\"");
		free(tmp->content);
		tmp->content = new_content;
	}
}
