/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:52:44 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/31 00:11:07 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_next_main_exec(int *x)
{
	if (*x == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g_dep.content[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_dep.exit_status = UNKNOWN_COMMAND;
		exit(g_dep.exit_status);
	}
}

void	ft_main_execution(int i)
{
	int	x;

	x = 0;
	while (g_dep.staar[i++])
	{
		g_dep.staar[i] = ft_join_free(g_dep.staar[i], "/");
		g_dep.staar[i] = ft_join_free(g_dep.staar[i], g_dep.content[0]);
	}
	i = 1;
	while (g_dep.staar[i++])
	{
		if (access(g_dep.staar[i], X_OK) == 0)
		{
			if (g_dep.content[0][0] == '/')
			{
				x++;
				ft_putstr_fd(g_dep.content[0], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				g_dep.exit_status = ERROR;
				exit(g_dep.exit_status);
			}
			if (execve(g_dep.staar[i], g_dep.content, g_dep.env_copy) == -1)
			{
				g_dep.exit_status = ERROR;
				exit(g_dep.exit_status);
			}
		}
	}
	ft_next_main_exec(&x);
}

void	do_exec(t_list *list)
{
	if (access(list->args[0], X_OK) == 0)
		execve(list->args[0], list->args, g_dep.env_copy);
	if (access(list->args[1], X_OK) == 0)
		execve(list->args[1], list->args + 1, g_dep.env_copy);
}

void	main_execution(t_list *list)
{
	int	i;

	g_dep.str = get_arg();
	g_dep.content = ft_split(list->args[0], ' ');
	i = 1;
	if (list->args)
	{
		while (list->args[i])
		{
			g_dep.content = ft_realloc(g_dep.content, list->args[i]);
			i++;
		}
		i = 0;
	}
	if (g_dep.str == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(list->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_dep.exit_status = ERROR;
		exit(g_dep.exit_status);
	}
	g_dep.staar = ft_split(g_dep.str + 5, ':');
	do_exec(list);
	ft_main_execution(i);
}
