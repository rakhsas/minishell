/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:52:44 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/25 16:58:36 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_next_main_exec(int *x)
{
	if (*x == 0)
	{
		printf("minishell: %s", dep.content[0]);
		printf(": command not found\n");
		dep.exit_status = UNKNOWN_COMMAND;
		exit(dep.exit_status);
	}
}

void	ft_main_execution(int i)
{
	int	x;

	x = 0;
	while (dep.staar[i++])
	{
		dep.staar[i] = ft_join_free(dep.staar[i], "/");
		dep.staar[i] = ft_join_free(dep.staar[i], dep.content[0]);
	}
	i = 1;
	while (dep.staar[i++])
	{
		if (access(dep.staar[i], X_OK) == 0)
		{
			if (dep.content[0][0] == '/')
			{
				x++;
				printf("%s", dep.content[0]);
				printf(": No such file or directory\n");
				exit(1);
			}
			if (execve(dep.staar[i], dep.content, dep.env_copy) == -1)
				exit(1);
		}
	}
	ft_next_main_exec(&x);
}

void	main_execution(t_list *list)
{
	int	i;

	dep.str = get_arg();
	dep.content = ft_split(list->args[0], ' ');
	i = 1;
	if (list->args)
	{
		while (list->args[i])
		{
			dep.content = ft_realloc(dep.content, list->args[i]);
			i++;
		}
		i = 0;
	}
	if (dep.str == NULL)
	{
		printf("minishell: %s", list->args[1]);
		printf(": No such file or directory\n");
		dep.exit_status = 127;
		exit(dep.exit_status);
	}
	dep.staar = ft_split(dep.str + 5, ':');
	if (access(list->args[0], X_OK) == 0)
		execve(list->args[0], list->args, dep.env_copy);
	if (access(list->args[1], X_OK) == 0)
		execve(list->args[1], list->args+1, dep.env_copy);
	ft_main_execution(i);
}
