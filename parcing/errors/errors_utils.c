/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:47:14 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 03:45:10 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_error_char(char c)
{
	if (c == '*' || c == ';' || c == '\\')
		return (1);
	if (c == '(' || c == ')')
		return (1);
	return (0);
}

int	is_opr(int type)
{
	if (type == TRUNC || type == APPEND)
		return (1);
	if (type == INPUT || type == HERDOC)
		return (1);
	return (0);
}

int	check_cmd_syntax(char *str)
{
	// if (!ft_error_char(str))
	// 	return (0);
	if (!check_quotes(str))
		return (0);
	return (1);
}

int	check_token_syntax(t_token **token)
{
	if (!pipe_errors(token))
		return (g_dep.exit_status = SYNTAX_ERROR, 0);
	if (!check_oper(token))
		return (g_dep.exit_status = SYNTAX_ERROR, 0);
	if (!check_herdoc(token))
		return (g_dep.exit_status = ERROR2, 0);
	return (1);
}
//function closedir  automaticlly will free dr

int	is_dir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}
