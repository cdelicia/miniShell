/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 14:16:51 by kcedra            #+#    #+#             */
/*   Updated: 2019/11/13 17:39:41 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exec_binaries(int ret, t_env **env, char **cur_cmds)
{
	t_path *path;
	char	**envp;

	if (ret == 8)
		execute_binary(env, cur_cmds);
	else
	{
		path_init(&path, *env);
		envp = env_to_char(*env);
		check_and_exec(path, cur_cmds, envp);
		envp_array_clear(envp);
	}
}

void		exec_my_functions(int ret, char **cur_cmds, t_env **env)
{
	if (ret == 1)
		echo(cur_cmds);
	if (ret == 3)
		pwd();
	if (ret == 5)
		env_print(*env);
	if (ret == 6)
		export(cur_cmds, env, 1);
}

void		check_and_exec(t_path *path, char **cur_cmds, char **envp)
{
	int		result;
	char	*command;

	result = -1;
	while (path != NULL)
	{
		command = ft_strdup(path->path);
		ft_strlcat(command, "/", ft_strlen(command) + 2);
		ft_strlcat(command, cur_cmds[0], ft_strlen(command) +
		ft_strlen(cur_cmds[0]) + 1);
		result = execve(command, cur_cmds, envp);
		if (result != -1)
			break ;
		path = path->next;
	}
	if (result == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(cur_cmds[0], 1);
		ft_putendl_fd(": command not found", 1);
	}
}
