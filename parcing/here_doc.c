/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:46:24 by aankote           #+#    #+#             */
/*   Updated: 2023/03/25 16:52:13 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char  *exp_limiter(char *limiter)
{
	int i;
	char *p;

	i = -1;
	p = ft_strdup("");
	while(limiter[++i])
	{
		if(!quotes(limiter, i) )
		{
			if(limiter[i] != '\'' && limiter[i] != '\"')
				p = ft_charjoin(p, limiter[i]);
		}
		else
			p = ft_charjoin(p, limiter[i]);
	}
	return (p);
}

char *check_name()
{
	int i;
	char *name;

	i = 0;
	name = ft_strjoin("/tmp/herdoc_",ft_itoa(i));
	while(!access(name, F_OK))
	{
		free(name);
		name = ft_strjoin("/tmp/herdoc_",ft_itoa(i++));
	}
	return(name);
}

void fill_file(int *fd, char *limiter, char **env)
{
	char *buffer;

	while(1 && *fd != -1)
	{
	
		buffer = get_next_line(0);
		if(!ft_strncmp(buffer, exp_limiter(limiter), ft_strlen(buffer) - 1) 
			&& ft_strlen(buffer) > 1)
		{
			free(buffer);
			exit(0) ;
		}
		if(do_exp_inp(limiter))
            buffer = ft_herd_exp(env, buffer);
		ft_putstr_fd(buffer, *fd);
	}
	exit(0);
}


char *here_doc(char *limiter, char **env)
{
    
	int fd;
	char *name;
	int pid;
	
	name = check_name();
	fd = open(name, O_TRUNC | O_CREAT |  O_RDWR, 0777);
	dep.files = ft_realloc(dep.files, name);
	pid = fork();
	if (!pid)
	{	
		signal(SIGINT, handle_signal);
		fill_file(&fd, limiter,env);
    	
	}
	waitpid(pid, NULL, 0);
	close (fd);
	return(name);
}

void open_her(t_token **token, char **env)
{
	t_token	*tmp;
	char *name;

	tmp = *token;
	while (tmp)
	{
		if (tmp->type == HERDOC)
		{
			name = here_doc(tmp->next->val, env);
			tmp->next->val = name;
		}
		tmp = tmp->next;
	}
}
