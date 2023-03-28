/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:13:46 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/28 12:32:46 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expaned_arg(char **env, char *arg)
{
	char	*p;

	p = ft_expand(env, arg);
	printf("%s", p);
	free(p);
}

void	check_args(t_list *list, int *i, int *n)
{
	char	*targ;

	while (list->args[*i + 1])
	{
		targ = ft_trim(list->args[*i + 1]);
		if ((!ft_strncmp(targ, "-n", 2)) || (!ft_strncmp(targ, "-e", 2)))
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
			printf("\n");
		return ;
	}
	check_args(list, &i, &n);
	while (list->args[++ i])
	{
		ft_putstr_fd(list->args[i], list->outfile);
		if (list->args[i + 1])
			printf(" ");
	}
	if (!n)
		ft_putstr_fd("\n", list->outfile);
}
