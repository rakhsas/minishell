/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:56:54 by aankote           #+#    #+#             */
/*   Updated: 2023/04/01 12:36:15 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_token(t_token **list)
{
	t_token	*tmp;

	while (*list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

void	ft_free_list(t_list *list)
{
	if (list->args[0])
		free(list->args[0]);
	if (list->args)
		free_double(list->args);
	list = NULL;
}

void	handle_signal1(int s)
{
	(void)s;
}

void	handle_signal2(int s)
{
	s = 0;
	rl_replace_line("\n", 0);
	rl_on_new_line();
	rl_redisplay();
}


void	print_error(char *str1, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
}

// void	free_list(t_list *head)
// {
// 	t_list	*current;
// 	t_list	*next;
// 	int		i;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		next = current->next;
// 		if (current->cmd)
// 			free(current->cmd);
// 		i = 0;
// 		if (current->args)
// 		{
// 			while (current->args[i] != NULL)
// 			{
// 				free(current->args[i]);
// 				i++;
// 			}
// 		}
// 		free(current->args);
// 		free(current);
// 		current = next;
// 	}
// }