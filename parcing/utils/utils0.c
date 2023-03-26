/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:51:50 by aankote           #+#    #+#             */
/*   Updated: 2023/03/23 15:37:36 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_skip_white_spaces(char *str, int *i)
{
    while (str[*i] == ' ')
    	(*i) ++;
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		if(!temp->next)
		{
			temp->next = new;
			new->prev = temp;
			return;
		}
		while (temp->next)
			temp = temp->next;
		new->prev = temp;
		temp->next = new;
	}
}

int	ft_listsize(t_list *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

void ft_free(char **p)
{
	int i;

	i = 0;
	while(p[i])
		free(p[i++]);
	free(p);
}

t_token	*ft_lstnew(int type, char *val)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
    new->type = type;
    new->val = val;
	new->next = NULL;
	return (new);
}              

void	add_list(t_list **lst, t_list *new)
{
	t_list	*temp;
    
	temp = *lst;
	if (temp == NULL)
		*lst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	new->next = NULL;
}

