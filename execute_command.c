/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 19:00:23 by kcedra            #+#    #+#             */
/*   Updated: 2019/11/07 18:17:42 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		check_redirect(t_cmd_list *lst)
{
	int fd;

	if (lst->redir_r == 1 || lst->rr_redir == 1)
	{
		fd = create_file_for_redirect(lst);
		dup2(fd, 1);
		close(fd);
	}
	if (lst->redir_l == 1)
	{
		fd = open_file_for_read(lst);
		dup2(fd, 0);
		close(fd);
	}
}

static void	sighandler(int sig)
{
	sig = 0;
	write(1, "\n", 1);
}

void		execute_command(t_env **env, char **cur_cmds, t_main *data, t_cmd_list *lst)
{
	pid_t	pid;
	int		ret;
	int		status;

	if (lst->pipe == 1)
		execute_command_pipe(env, cur_cmds, data);
	else
	{
		pid = fork();
		signal(SIGINT, sighandler);
		if (pid < 0)
			return ;
		if (pid == 0)
		{
			check_redirect(lst);
			ret = ft_check_command(cur_cmds[0]);
			if (ret == 1 || ret == 3 || ret == 5 || ret == 6)
				exec_my_functions(ret, cur_cmds, env);
			else
				exec_binaries(ret, env, cur_cmds);
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, &status, 0);
	}
}

void		execute_command_pipe(t_env **env, char **cur_cmds, t_main *data)
{
	pid_t	pid;
	int		ret;
	int		status;

	pipe(data->fd_0);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		close(data->fd_0[0]);
		dup2(data->fd_0[1], 1);
		close(data->fd_0[1]);
		ret = ft_check_command(cur_cmds[0]);
		if (ret == 1 || ret == 3 || ret == 5 || ret == 6)
			exec_my_functions(ret, cur_cmds, env);
		else
			exec_binaries(ret, env, cur_cmds);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(data->fd_0[1]);
		dup2(data->fd_0[0], 0);
		close(data->fd_0[0]);
		waitpid(pid, &status, 0);
	}
}
