/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 11:21:32 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/26 17:49:32 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_builtin(t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(list->args[0], "echo"))
		echo(dep.env, list);
	else if (!ft_strcmp(list->args[0], "pwd"))
		printf("%s\n", dep.pwd);
	else if (!ft_strcmp(list->args[0], "exit"))
		ft_exit(list);
	else if (!ft_strcmp(list->args[0], "cd"))
		ft_cd(list);
	else if (!ft_strcmp(list->args[0], "env"))
		ft_env();
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
	while (dep.env[i])
	{
		if (dep.env[i][j] == 'P' && dep.env[i][j + 4] == '=')
		{
			str = dep.env[i];
			return (str);
		}
		i++;
	}
	return (NULL);
}

void	ft_next_exec(t_list *list, int *stdin)
{
	int	fd[2]	;
	*stdin = dup(0);
	while (list)
	{
		if (list->infile != 0)
			dup2(list->infile, 0);
		pipe(fd);
		if (fork() == 0)
		{
			if (list->infile == -1)
			{
				close(fd[0]);
				close(fd[1]);
				exit(1);
			}
			if (list->infile == 1)
				dup2(*stdin, STDIN_FILENO);
			close(fd[0]);
			if (list->outfile != 1)
			{
				dup2(list->outfile, 1);
			}
			else if (list->next)
				dup2(fd[1], 1);
			close(fd[1]);
			if (!check_command(list->args[0]))
				return ;
			str_tolower(list->args[0]);
			if (check_if_builtin(list) == 1)
				main_execution(list);
		}
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		list = list->next;
	}
	// close(fd[1]);
	// close(fd[0]);
	close(0);
	dup2(*stdin, 0);
	// close(stdin);
	while (wait(NULL) != -1)
	{
	}
}

void	ft_exec(t_list *list)
{
	int	stdin;

	if (ft_listsize(list) == 1)
	{
		if (!check_command(list->args[0]))
			return ;
		str_tolower(list->args[0]);
		if (check_if_builtin(list) == 1)
		{
			if (fork() == 0)
			{
				if (list->outfile != 0)
					dup2(list->outfile, 1);
				if (list->infile != 0)
					dup2(list->infile, 0);
				main_execution(list);
			}
			while (wait(NULL) != -1)
				;
		}
	}
	else
	{
		ft_next_exec(list, &stdin);
	}
}
