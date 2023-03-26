/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 08:55:13 by aankote           #+#    #+#             */
/*   Updated: 2023/03/13 00:17:28 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_quotes_util(char *str, int *check, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\'' && *check == 1)
			*check = 0;
		else if (str[*i] == '\'' && *check == 0)
		{
			*check = 1;
			return ;
		}
		(*i)++;
	}
}

int	check_single_quotes(char *str)
{
	int	i;
	int	check;

	i = -1;
	check = 1;
	while (str[++i])
	{
		if (str[i] == '\"' && check == 1)
			check = 0;
		else if (str[i] == '\"' && check == 0)
			check = 1;
		else if (str[i] == '\'' && check == 1)
			check_quotes_util(str, &check, &i);
	}
	return (check);
}
