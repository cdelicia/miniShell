/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 00:07:59 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/11 19:54:27 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sighandler(int sig)
{
	char *line;

	if (sig == SIGINT)
	{
		if (!(line = getcwd(NULL, 0)))
			return;
		ft_putchar_fd('\n', 1);
		print_input_calling(line);
	}
	if (sig == SIGQUIT)
	{
		ft_putchar_fd('\n', 1);
		//exit(0);
	}
	sig = 0;
}

void	print_input_calling(char *s)
{
	ft_putstr_fd("\033[32m", 1);
	ft_putstr_fd("minishell:", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(">$", 1);
	ft_putstr_fd("\033[0m", 1);
	ft_putstr_fd(" ", 1);
	free(s);
	//my_signals();
		//signal(SIGINT, my_func);
		//signal(SIGQUIT, my_func);
		//signal(15, SIG_IGN);
}

int		main(int argc, char **argv, char **envp)
{
	t_main	main;

	if (argc != 1 && argv[0])
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (1);
	}
	initialization_all(&main);
	env_init(envp, &main.env);
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		ft_parcing(&main);
		clear_parced_cmd_list(&main);
	}
	clear_parced_env_list(&main);
	return (0);
}
