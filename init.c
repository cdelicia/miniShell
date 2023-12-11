/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 01:06:44 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/02 03:48:17 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		initialization_all(t_main *main)
{
	g_main_ptr = main;
	g_num = 1;
	ft_bzero(main, sizeof(*main));
	ft_bzero(main->separator, 4);
	main->save_0 = dup(0);
	main->save_1 = dup(1);
}

t_cmd_list	*ft_cmd_lstnew(void)
{
	t_cmd_list *tmp;

	tmp = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	tmp->number = g_num++;
	tmp->pipe = 0;
	tmp->redir_r = 0;
	tmp->rr_redir = 0;
	tmp->redir_l = 0;
	tmp->theend = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}
