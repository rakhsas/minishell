/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:50:47 by aankote           #+#    #+#             */
/*   Updated: 2023/03/23 15:53:09 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	list_init(t_list *list)
{
	list->args = NULL;
	// list->args[0] = NULL;
	list->cmd = NULL;
	list->infile = 0;
	list->outfile = 1;
	list->append_in = 1;
	list->perror = 1;
	list->next = NULL;
}

void	get_cmd(t_list **list, t_token **token)
{
	t_token	*tmp;
	t_list	*tmp_list;
	
	tmp = *token;
	tmp_list = (t_list *)malloc(sizeof(t_list));
	list_init(tmp_list);
	open_her(token, dep.env);
	while (tmp)
	{
		type_arg(tmp);
		//  if (tmp->type == CMD)
		//  	tmp_list->args[0] = tmp->val;
		if (tmp->type == ARG || tmp->type == CMD)
			tmp_list->args = ft_realloc(tmp_list->args, tmp->val);
		else if (tmp->type == INFILE)
			get_infile(tmp_list, tmp->val);
		else if (tmp->type == OUTFILE)
			get_outfile(tmp_list, tmp->val, OUTFILE);
		else if (tmp->type == APPEND)
			get_outfile(tmp_list, tmp->next->val, APPOUT);
		else if (tmp->type == HERDOC)
			get_infile(tmp_list, tmp->next->val);
		if ((tmp->next && tmp->next->type == PIPE) || !tmp->next)
			add_command(list, &tmp_list);
		tmp = tmp->next;
	}
}

void	type_arg(t_token *token)
{
	if (ft_strcmp(token->val, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->val, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->val, "<<") == 0)
		token->type = HERDOC;
	else if (ft_strcmp(token->val, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->val, "|") == 0)
		token->type = PIPE;
	else if (token->prev && token->prev->type == INPUT)
		token->type = INFILE;
	else if (token->prev && token->prev->type == APPEND)
		token->type = APPOUT;
	else if (token->prev && token->prev->type == TRUNC)
		token->type = OUTFILE;
	else if (token->prev && token->prev->type == HERDOC)
		token->type = LIMITER;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
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
//leaks visited : done
void	get_token(char *line, t_token **token)
{
	int		i;
	char	*p;

	*token = NULL;
	i = -1;
	while (line[++i])
	{
		p = ft_calloc(1, 1);
		if (line[i] && !ignore_sep(line[i], line, i))
			ft_add_str(line, token, p, &i);
		else
		{
			if (line[i] && ignore_sep(line[i], line, i))
				ft_add_opr(line, token, p, &i);
		}
	}
}
