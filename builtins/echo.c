/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:13:46 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/01 23:12:04 by rakhsas          ###   ########.fr       */
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

int check_n(char *targ, int *n)
{
	int j;

	j = 0;
	while (targ[++j])
	{
		if(targ[j] != 'n')
		{
			*n = 0;
			return(0);
		}
	}
	return (1);
}

void	check_args(t_list *list, int *i, int *n)
{
	char	*targ;
	int j;

	j = 0;
	while (list->args[*i + 1])
	{
		targ = ft_trim(list->args[*i + 1]);
		if (!ft_strncmp(targ, "-n", 2))
		{
			*n = 1;
			if(!check_n(targ, n))
				break;
		}
		else
			break ;
		(*i)++;
	}
	free(targ);
}

void	echo(t_list *list)
{
	int		i;
	int		n;

	i = 0;
	n = 0;

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
	g_dep.exit_status = 0;
}
