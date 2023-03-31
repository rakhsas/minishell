/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:09:51 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 00:55:22 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipe_errors(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next || !tmp->prev)
			{
				printf("bash: syntax error near unexpected token '|'\n");
				g_dep.exit_status = SYNTAX_ERROR;
				return (0);
			}
			else if (tmp->next && tmp->next->type == PIPE)
			{
				printf("bash: syntax error near unexpected token '||'\n");
				g_dep.exit_status = SYNTAX_ERROR;
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_oper(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (is_opr(tmp->type) && tmp->next && is_opr(tmp->next->type))
		{
			printf("syntax error near unexpected token %s\n", tmp->next->val);
			return (0);
		}
		if (is_opr(tmp->type) && !tmp->next)
		{
			printf("syntax error near unexpected token 'newline'\n");
			return (0);
		}
		if (is_opr(tmp->type) && tmp->next->type == PIPE)
		{
			printf("syntax error near unexpected token %s\n", tmp->next->val);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	ft_error_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_error_char(str[i]) && (!quotes(str, i) || quotes(str, i) == 1))
		{
			printf("SYNTAX ERROR!\n");
			g_dep.exit_status = SYNTAX_ERROR;
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_command(char *str)
{
	DIR	*dr;

	if (str && !is_dir(str))
	{
		g_dep.exit_status = IS_DIRECTORY;
		if (!str[1])
			printf("bash: %s :is a directory\n", str);
		else
		{
			dr = opendir(str);
			if (opendir(str))
				printf("bash: %s :is a directory\n", str);
			else
			{
				g_dep.exit_status = UNKNOWN_COMMAND;
				printf("bash: %s: No such file or directory\n", str);
			}
			if (dr)
				closedir(dr);
		}
		return (0);
	}
	return (1);
}

int	check_herdoc(t_token **token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *token;
	while (tmp)
	{
		if (tmp->type == HERDOC)
			i++;
		tmp = tmp->next;
	}
	if (i > 16)
	{
		printf("bash: maximum here-document count exceeded\n");
		return (0);
	}
	return (1);
}
