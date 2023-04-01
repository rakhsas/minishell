/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:21:32 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/01 17:17:12 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_builtin(t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(list->args[0], "echo"))
		echo(list);
	else if (!ft_strcmp(list->args[0], "pwd"))
		ft_putendl_fd(g_dep.pwd, list->outfile);
	else if (!ft_strcmp(list->args[0], "exit"))
		ft_exit(list);
	else if (!ft_strcmp(list->args[0], "cd"))
		ft_cd(list);
	else if (!ft_strcmp(list->args[0], "env"))
		ft_env(list->outfile);
	else if (!ft_strcmp(list->args[0], "unset"))
		ft_unset(list);
	else if (!ft_strcmp(list->args[0], "export"))
		ft_export(list);
	else
		i++;
	return (i);
}

char	*get_arg(void)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_dep.env[i])
	{
		if (g_dep.env[i][j] == 'P' && g_dep.env[i][j + 4] == '=')
		{
			str = g_dep.env[i];
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	ft_child_process(int pid, t_list *list, int *stdin, int *fd)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (list->infile == -1)
		{
			close(fd[0]);
			close(fd[1]);
			// exit(127);
		}
		if (list->infile == 1)
		{
			dup2(*stdin, STDIN_FILENO);
			close(*stdin);
		}
		close(fd[0]);
		if (list->outfile != 1)
		{
			dup2(list->outfile, 1);
		}
		else if (list->next)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		close(fd[1]);
		str_tolower(list->args[0]);
		if (check_if_builtin(list) == 1)
			main_execution(list);
		exit(g_dep.exit_status);
	}
}

void	ft_loop(t_list *list, int *fd, int *stdin, int *pid)
{

	if (list->infile == -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (list->infile != 0)
		dup2(list->infile, 0);
	if (pipe(fd) == -1)
	{
		perror("pipe");
		g_dep.exit_status = ERROR;
		exit(g_dep.exit_status);
	}
	*pid = fork();
	ft_child_process(*pid, list, stdin, fd);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

void	ft_next_exec(t_list *list)
{
	int	stdin;
	int	fd[2];
	int pid;

	stdin = dup(0);
	while (list)
	{
		ft_loop(list, fd, &stdin, &pid);
		list = list->next;
	}
	// close(fd[0])
	waitpid(pid, &g_dep.exit_status, 0);
	g_dep.exit_status = WEXITSTATUS(g_dep.exit_status);
	// printf("%d\n", g_dep.exit_status);
	close(0);
	dup2(stdin, 0);
	close(stdin);
	while (wait(NULL) != -1)
		;
}

void	ft_exec(t_list *list)
{
	int pid;
	if (ft_listsize(list) == 1)
	{
		if (!list->args)
			return ;
		str_tolower(list->args[0]);
		if (check_if_builtin(list) == 1)
		{
			pid = fork();
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (list->infile == -1 || list->outfile == -1)
				{
					if (access(list->args[0], R_OK) == -1)
					{
						ft_putstr_fd("minishell: ", 2);
						ft_putstr_fd(list->args[0], 2);
						ft_putstr_fd(": No such file or directory\n", 2);
						g_dep.exit_status = UNKNOWN_COMMAND;
						exit(g_dep.exit_status);
					}
					else
						execve(list->args[0], list->args, g_dep.env);
					exit(1);
				}
				if (list->outfile != 0)
					dup2(list->outfile, 1);
				if (list->infile != 0)
					dup2(list->infile, 0);
				main_execution(list);
			}
			waitpid(pid, &g_dep.exit_status, 0);
			if (g_dep.exit_status == 2)
				g_dep.exit_status = 130;
			else
				g_dep.exit_status = WEXITSTATUS(g_dep.exit_status);
			while (wait(NULL) != -1)
				;
		}
	}
	else
		ft_next_exec(list);
}
