/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:56:54 by aankote           #+#    #+#             */
/*   Updated: 2023/03/30 23:23:10 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_token(t_token **list)
{
	t_token *tmp;

	while(*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void ft_free_list(t_list *list)
{
	if(list->args[0])
		free(list->args[0]);
	if(list->args)
		free_double(list->args);
	list = NULL;
}

void ft_ck(t_list **lst)
{
	t_list *tmp;
	 tmp = *lst;
	while(tmp)
	{
		if(tmp->infile == -1)
		{
			printf("error");
			return;
		}
		tmp = tmp->next;
	}
}

void handle_signal1(int s)
{
	s = 0;
	rl_replace_line("\n", 0);
	rl_redisplay();
	rl_on_new_line();
}

void handle_signal2(int s)
{
	(void) s;
	exit(0);
}

void	print_error(char *str1, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}