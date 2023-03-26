/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:24:14 by aankote           #+#    #+#             */
/*   Updated: 2023/03/21 20:46:34 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void unlink_files(char **files)
{
	int i;

	i = 0;
	if(files)
	{
		while(files[i])
		{
			unlink(files[i]);
			//free(files[i]);
			i++;
		}
	}
}

void handle_signal(int sg)
{
	(void)sg;
	exit(1);
}

int do_exp_inp(char *limiter)
{
	int i;

	i = -1;
	while(limiter[++i])
	{
		if(limiter[i] == '\'' || limiter[i] == '\"')
			return (0);
	}
	return (1);
}
