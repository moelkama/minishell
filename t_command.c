/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akatfi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:13:38 by akatfi            #+#    #+#             */
/*   Updated: 2023/06/15 14:34:36 by akatfi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_duplicate_fd(t_pipe *ptr, int *p)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (ptr->in == -2)
		exit (1);
	else if (ptr->in != -1)
		dup2(ptr->in, 0);
	if (ptr->out == -2)
		exit (1);
	else if (ptr->out != -1)
		dup2(ptr->out, 1);
	else if (ptr->next != NULL)
	{
		dup2(p[1], 1);
		close(p[1]);
		close(p[0]);
	}
}

void	ft_env(char *cmd, t_list **linked_env, char **env, t_pipe *ptr)
{
	if (!ft_strcmp(cmd, "env"))
	{
		if (ptr->cmd->cmd[1])
		{
			write(2, "env with no options or arguments\n", 34);
			exit(127);
		}
		ft_get_env(env, linked_env, 1);
	}
}

void	ft_exec_command(char *cmd, t_pipe *ptr, t_list **linked_env, char **env)
{
	ft_puterror(cmd, ptr->cmd->cmd[0]);
	if (ft_check_builtin(cmd, ptr->cmd->cmd[0]))
	{
		ft_env(cmd, linked_env, env, ptr);
		if (!ft_strcmp("exit", ptr->cmd->cmd[0]))
			ft_exit(ptr->cmd->cmd, 0);
		else if (!ft_strcmp(cmd, "echo"))
			ft_echo(ptr->cmd->cmd, ptr->cmd->cmd[1]);
		else if (!ft_strcmp(cmd, "pwd"))
			get_pwd();
		else if (!ft_strcmp(ptr->cmd->cmd[0], "unset"))
			ft_unset(ptr->cmd->cmd, linked_env, 1);
		else if (!ft_strcmp(ptr->cmd->cmd[0], "cd"))
			ft_cd(ptr->cmd->cmd[1], linked_env, 1);
		else if (!ft_strcmp(ptr->cmd->cmd[0], "export"))
			ft_export(ptr->cmd->cmd, linked_env, 1);
	}
	else if (ptr->cmd->path && ptr->cmd->cmd[0])
		execve(ptr->cmd->path, ptr->cmd->cmd, env);
	else if (ptr->cmd->cmd[0] && !ptr->cmd->path)
		ft_cmd_error(*linked_env, ptr);
	exit (0);
}

void	ft_mainprocess(int len, t_list **linked_env, t_pipe *ptr, int *p)
{
	if (len == 1)
	{
		if (!ft_strcmp("exit", ptr->cmd->cmd[0]))
			ft_exit(ptr->cmd->cmd, 1);
		if (!ft_strcmp(ptr->cmd->cmd[0], "cd"))
			ft_cd(ptr->cmd->cmd[1], linked_env, 0);
		else if (!ft_strcmp(ptr->cmd->cmd[0], "unset"))
			ft_unset(ptr->cmd->cmd, linked_env, 0);
		else if (!ft_strcmp(ptr->cmd->cmd[0], "export"))
			ft_export(ptr->cmd->cmd, linked_env, 0);
	}
	dup2(p[0], 0);
	close(p[1]);
	close(p[0]);
	if (ptr->out >= 3)
		close(ptr->out);
	if (ptr->in >= 3)
		close(ptr->in);
}

void	ft_multiple_cmd(t_pipe *ptr, char **env, t_list **linked_env)
{
	int		p[2];
	char	*cmd;
	int		std[4];
	int		len;

	std[0] = dup(0);
	std[1] = dup(1);
	g_status[1] = 1;
	len = ft_lstsize_pipe(ptr);
	while (ptr)
	{
		pipe(p);
		cmd = to_lowor(ptr->cmd->cmd[0]);
		std[2] = fork();
		if (std[2] == 0)
		{
			ft_duplicate_fd(ptr, p);
			ft_exec_command(cmd, ptr, linked_env, env);
		}
		ft_mainprocess(len, linked_env, ptr, p);
		if (cmd)
			free(cmd);
		ptr = ptr->next;
	}
	wait_checksignal(std);
}
