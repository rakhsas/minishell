/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:59:18 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:06:28 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_std(char *val, t_list *list)
{
	if (!ft_strcmp("/dev/stdin", val) || !ft_strcmp("/dev/stdin/", val))
		return (1);
	if (!ft_strcmp("/dev/stdout", val) || !ft_strcmp("/dev/stdout/", val))
	{
		list->infile = 1;
		return (1);
	}
	if (!ft_strcmp("/dev/stderr", val) || !ft_strcmp("/dev/stderr/", val))
	{
		list->infile = 2;
		return (1);
	}
	return (0);
}

int	ignore_sep(char c, char *line, int index)
{
	if (quotes(line, index))
		return (0);
	if (c && c == '|')
		return (1);
	else if (c && c == '>')
		return (1);
	else if (c && c == ' ')
		return (1);
	else if (c && c == '<')
		return (1);
	return (0);
}

void	list_init(t_list *list)
{
	list->args = NULL;
	list->cmd = NULL;
	list->infile = 0;
	list->outfile = 1;
	list->append_in = 1;
	list->perror = 1;
	list->next = NULL;
}
