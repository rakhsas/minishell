/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:24:00 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/31 00:07:13 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

void	is_numeric(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (args[i] != NULL)
	{
		while (args[0][j])
		{
			if ((args[0][0] == '-' || args[0][0] == '+') && args[0][1] == '0'
			&& !ft_atoi(&args[0][1]))
				(printf("exit\n"), exit(0));
			if (args[0][j] != '0' && !ft_atoi(&args[0][j]))
			{
				write(2, "minishell: exit: ", 17);
				write(2, args[0], ft_strlen(args[0]));
				write(2, ": numeric argument required\n", 28);
				g_dep.exit_status = 255;
				exit(g_dep.exit_status);
			}
			j++;
		}
		i++;
	}
}

int	ft_exit(t_list *data)
{
	long long	len;

	len = count_args(data->args + 1);
	if (len == 1)
		(printf("exit\n"), g_dep.exit_status = 0, exit(g_dep.exit_status));
	if (data->args + 1)
	{
		is_numeric(data->args + 1);
		if (len > 2)
			write(2, "exit\nminishell: exit: too many arguments\n", 41);
		else if (len == 2)
		{
			len = ft_atoi(data->args[1]);
			if (data->args[1][0] != '-' && len < 0)
			{
				write(2, "minishell: exit: ", 17);
				write(2, data->args[1], ft_strlen(data->args[1]));
				write(2, ": numeric argument required\n", 28);
				g_dep.exit_status = 255;
				exit(g_dep.exit_status);
			}
			else
				(printf("exit\n"), g_dep.exit_status = ft_atoi(data->args[1]),
					exit(g_dep.exit_status));
		}
	}
	return (1);
}