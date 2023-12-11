/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 00:37:55 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/11 00:43:14 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_return_env_var(int error, t_main *data)
{
	t_env	*tmp;

	tmp = data->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "?", 1) == 0 &&
		ft_strncmp(tmp->key, "?", ft_strlen(tmp->key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_itoa(error);
			return ;
		}
		tmp = tmp->next;
	}
}

void	command_not_found(t_main *data)
{
	ft_putstr_fd("Command_not_found\n", 2);
	change_return_env_var(127, data);
}

void	syntax_error(t_main *data)
{
	ft_putstr_fd("Syntax error\n", 2);
	change_return_env_var(258, data);
}

void	no_such_file(t_main *data)
{
	ft_putstr_fd("No such file or directory\n", 2);
	change_return_env_var(127, data);
}

void	permission_denied(t_main *data)
{
	ft_putstr_fd("Permission denied\n", 2);
	change_return_env_var(126, data);
}
