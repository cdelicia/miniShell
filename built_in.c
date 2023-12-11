/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:27:34 by kcedra            #+#    #+#             */
/*   Updated: 2019/11/14 02:58:17 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo(char **cur_command)
{
	int	i;
	int	k;

	k = 1;
	while (cur_command[k] != NULL)
	{
		printf("%d: '%s'\n", k, cur_command[k]);
		i = 0;
		while (cur_command[k][i] != '\0')
		{
			ft_putchar_fd(cur_command[k][i++], 1);
		}
		k++;
	}
	write(1, "\n", 1);
}

static char *get_env_dir(char *cur_command, t_env *env)
{
	char	*path;
	char	*ret;
	int		flag;

	if (cur_command != NULL && cur_command[0] == '$')
	{
		flag = 0;
		ret = NULL;
		path = ft_substr(cur_command, 1, ft_strchrnum(&(cur_command[1]), '\0'));
		while (env != NULL)
		{
			if (ft_strncmp(path, env->key,
			ft_strchrnum(cur_command, '\0') + 1) == 0)
			{
				ret = ft_strdup(env->value);
				flag = 1;
				break;
			}
			env = env->next;
		}
		free(path);
		return((flag == 0) ? NULL : ret);
	}
	else
		return (cur_command);
}

void		pwd(void)
{
	char    *cur_dir;

	cur_dir = getcwd(NULL, 0);
	write(1, cur_dir, ft_strlen(cur_dir));
	write(1, "\n", 1);
	free(cur_dir);
}

void		put_info_dir(char **dir, t_env **head)
{
	(*head)->value = ft_realloc((*head)->value, ft_strlen(*dir) + 1);
	ft_strlcpy((*head)->value, *dir, ft_strlen(*dir) + 1);
	free(*dir);
}

void		cd(char **cur_command, t_env **env)
{
	int		flag;
	char	*curdir;
	char	*oldpwd;
	t_env	*head;
	t_env	*new;

	head = *env;
	oldpwd = getcwd(NULL, 0);
	curdir = get_env_dir(cur_command[1], *env);
	if (chdir(curdir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(curdir, 1);
		if (curdir != NULL)
			ft_putstr_fd(": ", 1);
		ft_putendl_fd(strerror(errno), 1);
		free(oldpwd);
	}
	else
	{
		flag = 0;
		if (cur_command[1][0] == '$')
			free(curdir);
		curdir = getcwd(NULL, 0);
		if (ft_strncmp((head->key), "PWD", 4) == 0)
			put_info_dir(&curdir, &head);
		if (ft_strncmp((head->key), "OLDPWD", 7) == 0)
		{
			flag = 1;
			put_info_dir(&oldpwd, &head);   
		}
		while (head->next != NULL)
		{
			head = head->next;
			if (ft_strncmp((head->key), "PWD", 4) == 0)
				put_info_dir(&curdir, &head);
			if (ft_strncmp((head->key), "OLDPWD", 7) == 0)
			{   
				flag = 1;
				put_info_dir(&oldpwd, &head);
			}
		}
		if (flag == 0)
		{
			new = ft_envnew("OLDPWD=new");
			head->next = new;
			head = head->next;
			put_info_dir(&oldpwd, &head);
		}
	}
}

void		export(char **cur_command, t_env **env, int i)
{
	int		flag;
	int		value_start;
	char	*key;
	char	*value;
	t_env	*head;

	flag = 0;
	export_print(*env, cur_command[i], 1);
	while (cur_command[i] != NULL)
	{
		head = *env;
		value_start = ft_strchrnum(cur_command[i], '=') + 1;
		key = ft_substr(cur_command[i], 0, value_start - 1);
		value = ft_strdup(&(cur_command[i][value_start]));
		if (ft_strncmp(head->key, key, ft_strlen(key) + 1) == 0)
		{
			reassign_value(&head, &flag, value);
		}
		searching_key_export(&head, &flag, value, key);
		if (cur_command[i][0] == '=')
			export_error_management(cur_command[i], &flag);
		if (flag == 0 && key[0] != '\0')
			create_new_elem(&head, key, value, value_start);
		free(key);
		free(value);
		i++;
	}
}

void		unset(char **cur_command, t_env **env)
{
	int		i;
	char	*key;
	t_env	*head;

	i = 1;
	while (cur_command[i] != NULL)
	{
		head = *env;
		key = ft_strdup(cur_command[i]);
		if (ft_strncmp(head->key, key, ft_strlen(key) + 1) == 0)
		{
			*env = head->next;
			free(head->key);
			free(head->value);
			free(head);
		}
		while (head->next != NULL)
			searching_key_unset(&head, key);
		unset_error_management(cur_command[i]);
		free(key);
		i++;
	}
}
