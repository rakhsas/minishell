/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:13:46 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/25 16:51:24 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expaned_arg(char **env, char *arg)
{
	char *p;

	p = ft_expand(env, arg);
	printf("%s", p);
	free(p);
}

void check_args(t_list *list, int *i, int *n)
{
	char *targ;
	while(list->args[*i + 1])
	{
		targ = ft_trim(list->args[*i + 1]);
		if( (!ft_strncmp(targ, "-n", 2)) || (!ft_strncmp(targ, "-e", 2)))
		{
			(*i)++;
			if (!ft_strcmp(targ, "-n"))
				*n = 1;
			free(targ);
		}
		else
		{
			free(targ);
			break;
		}
	}
}

void echo(char **env, t_list *list)
{
	int		i;
	int		n;
	(void)env;

	i = 0;
	n = 0;

	if (!list->args || list->perror == -1)
	{
		if (!list->args)
			printf("\n");
		return ;
	}
	// while(list->args[i + 1])
	// {
	// 	targ = ft_trim(list->args[i + 1]);
	// 	if( (!ft_strcmp(targ, "-n")) || (!ft_strcmp(targ, "-e")))
	// 	{
	// 		i++;
	// 		if (!ft_strcmp(targ, "-n"))
	// 			n = 1;
	// 		free(targ);
	// 	}
	// 	else
	// 	{
	// 		free(targ);
	// 		break;
	// 	}
	// }
	check_args(list, &i, &n);
	while (list->args[++ i])
	{
		printf("%s", list->args[i]);
		if (list->args[i + 1])
			printf(" ");
	}
	if (!n)
		printf("\n");
}
