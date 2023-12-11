/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <kcedra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:10:40 by cdelicia          #+#    #+#             */
/*   Updated: 2019/11/13 17:39:35 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

typedef struct					s_cmd_list
{
	int							number;
	char						*content;
	int							redir_l;
	int							redir_r;
	int							theend;
	int							rr_redir;
	int							pipe;
	struct s_cmd_list			*next;
	struct s_cmd_list			*prev;
}								t_cmd_list;

typedef struct					s_env
{
	int							visible;
	char						*key;
	char						*value;
	struct s_env				*next;
}								t_env;

typedef struct					s_path
{
	char			*path;
	struct s_path	*next;
}								t_path;

typedef struct					s_main
{
	int							save_0;
	int							save_1;
	int							fd_0[2];
	int							fd_1[2];
	char						separator[4];
	t_cmd_list					*list;
	t_env						*env;
}								t_main;

t_main							*g_main_ptr;
char							**g_line;
int								g_num;

void							echo(char **cur_command);
void							pwd(void);
void							input_calling(char *s);
void							env_print(t_env *env);
char							*skip_whitespaces(char *line);
int								read_line(char *line, t_main *data);
char							*delete_whitespaces(char *line);
void							clear_parced_env_list(t_main *main);
int								put_cmds_to_list(char *line, t_main *data);
void							free_all_array_elements(char **arr, int i);
int								array_len(char **cur_commands);
int								ft_parcing(t_main *data);
void							split_line_to_list(t_main *data, char *line);
int								ft_check_command(char *s);
void							initialization_all(t_main *main);
void							env_init(char **envp, t_env **env);
void							clear_parced_cmd_list(t_main *main);
void							ft_cmd_lstadd_back(t_cmd_list **lst, t_cmd_list *new);
void							ft_lstclear_cmd(t_cmd_list **lst, void (*del)(void*));
t_env							*ft_envnew(char *content);
t_cmd_list						*ft_cmd_lstnew(void);
void							check_redir_pipe(t_cmd_list *list, char *start, char *s);
void							cd(char **cur_command, t_env **env);
void							export(char **cur_command, t_env **env, int i);
void							unset(char **cur_command, t_env **env);
void							create_new_elem(t_env **head, char *key, char *value, int value_start);
void							reassign_value(t_env **head, int *flag, char *value);
void							searching_key_export(t_env **head, int *flag, char *value, char *key);
void							export_error_management(char *cur_command, int *flag);
void							searching_key_unset(t_env **head, char *key);
void							unset_error_management(char *cur_command);
void							execute_command(t_env **env, char **cur_cmds, t_main *data, t_cmd_list *lst);
char							**env_to_char(t_env *env);
void							export_print(t_env *env, char *cur_command, int fd);
void							envp_array_clear(char **envp);
void							path_init(t_path **path, t_env *env);
void							check_and_exec(t_path *path, char **cur_cmds, char **envp);
void  							fix_content(t_cmd_list *lst, t_env *env);
void							execute_binary(t_env **env, char **cur_cmds);
void							change_return_env_var(int error, t_main *data);
void							exec_my_functions(int ret, char **cur_cmds, t_env **env);
int								create_file_for_redirect(t_cmd_list *lst);
int								open_file_for_read(t_cmd_list *lst);
void							exec_binaries(int ret, t_env **env, char **cur_cmds);
void							execute_command_pipe(t_env **env, char **cur_cmds, t_main *data);
void							command_not_found(t_main *data);
void							syntax_error(t_main *data);
void							no_such_file(t_main *data);
void							permission_denied(t_main *data);
void							print_input_calling(char *s);
void							fix_all_quotes(t_cmd_list *tmp);
int								ft_check_strong_quotes(char *content);

#endif
