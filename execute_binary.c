/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:14:54 by kcedra            #+#    #+#             */
/*   Updated: 2019/11/11 00:31:13 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_binary(t_env **env, char **cur_cmds)
{
	char	**envp;
	int		result;

	envp = env_to_char(*env);
	result = execve(cur_cmds[0], cur_cmds, envp);
	if (result == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cur_cmds[0], 1);
		ft_putstr_fd(": ", 1);
		ft_putendl_fd(strerror(errno), 1);
	}
	envp_array_clear(envp);
}
