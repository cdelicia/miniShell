/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:43:19 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/12 05:21:04 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_executing(t_main *data, char **cur_cmds, t_cmd_list *tmp)
{
	int ret;

	ret = ft_check_command(cur_cmds[0]);
	if (ret == 2)
		cd(cur_cmds, &(data->env));
	else if (ret == 6 && cur_cmds[1] != NULL)
		export(cur_cmds, &(data->env), 1);
	else if (ret == 7)
		unset(cur_cmds, &(data->env));
	else if (ret == 4)
	{
		free_all_array_elements(cur_cmds, array_len(cur_cmds));
		exit(0);
	}
	else
		execute_command(&(data->env), cur_cmds, data, tmp);
}

char	**put_command_to_array(t_cmd_list *tmp)
{
	char	**cur_cmds;

	cur_cmds = NULL;
	if (ft_strncmp("echo", tmp->content, 4) == 0)
	{
		if (tmp->content[4] != '\0' && (tmp->content + 5))
		{
			cur_cmds = (char **)malloc(3);
			cur_cmds[0] = ft_strdup("echo");
			cur_cmds[1] = ft_strdup(tmp->content + 5);
			cur_cmds[2] = NULL;
		}
	}
	else if (!(cur_cmds = ft_split(tmp->content, ' ')))
		return (NULL);
	return (cur_cmds);
}

void	print_all_list_values(t_cmd_list *tmp, int *i)
{
	t_cmd_list *tmp2;

	tmp2 = tmp;
	if (*i == 0)
	{
		ft_putstr_fd("\033[33m", 1);
		while (tmp2)
		{
			printf("list №%d: [%s]", tmp2->number, tmp2->content);
			if (tmp2->pipe == 1)
				printf(", | ");
			if (tmp2->redir_l == 1)
				printf(", < ");
			if (tmp2->redir_r == 1)
				printf(", > ");
			if (tmp2->rr_redir == 1)
				printf(", >> ");
			printf("\n");
			tmp2 = tmp2->next;
		}
		ft_putstr_fd("\033[0m", 1);
	}
	*i = 1;
}

int		read_line(char *line, t_main *data)
{
	char		**cur_cmds;
	t_cmd_list	*tmp;
	int 		i = 0;

	split_line_to_list(data, line);
	tmp = data->list;
	while (tmp)
	{
		if (ft_check_strong_quotes(tmp->content) == 0)
			fix_content(tmp, data->env);
		fix_all_quotes(tmp);
		print_all_list_values(tmp, &i);
		while (tmp != NULL)
		{
			if (!(cur_cmds = put_command_to_array(tmp)))
				return (-1);
			start_executing(data, cur_cmds, tmp);
			if (tmp->pipe != 1 && tmp->prev && tmp->prev->pipe == 1)
			{
				data->fd_0[0] = data->save_0;
				data->fd_0[1] = data->save_1;
				dup2(data->fd_0[0], 0);
				dup2(data->fd_0[1], 1);
			}
			tmp = tmp->next;
		}
		free_all_array_elements(cur_cmds, array_len(cur_cmds));
	}
	return (0);
}

int		ft_parcing(t_main *data)
{
	char	*line;
	int		ret;

	if (!(line = getcwd(NULL, 0)))
		return (-1);
	print_input_calling(line);
	if ((ret = get_next_line(0, &line)) == 0 && !(ft_strlen(line)))
		exit(0);
	else if (ret == -1)
		exit(1);
	else
		read_line(line, data);
	free(line);
	return (0);
}
