/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:13:46 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/29 02:22:44 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	expaned_arg(char **env, char *arg)
// {
// 	char	*p;

// 	p = ft_expand(env, arg);
// 	printf("%s", p);
// 	free(p);
// }

void	check_args(t_list *list, int *i, int *n)
{
	char	*targ;

	while (list->args[*i + 1])
	{
		targ = ft_trim(list->args[*i + 1]);
		if ((!ft_strcmp(targ, "-n") || (!ft_strcmp(targ, "-e"))))
		{
			(*i)++;
			if (!ft_strcmp(targ, "-n"))
				*n = 1;
			free(targ);
		}
		else
		{
			free(targ);
			break ;
		}
	}
}

void	echo(char **env, t_list *list)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	(void)env;
	if (!list->args || list->perror == -1)
	{
		if (!list->args)
		return ;
	}
	check_args(list, &i, &n);
	while (list->args[++ i])
	{
		ft_putstr_fd(list->args[i], list->outfile);
		if (list->args[i + 1])
			ft_putstr_fd(" ", list->outfile);
	}
	if (!n || !list->args[0])
		ft_putstr_fd("\n", list->outfile);
}
