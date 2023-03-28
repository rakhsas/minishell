/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:56:34 by aankote           #+#    #+#             */
/*   Updated: 2023/03/28 17:41:49 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft(int c)
{
	if (c == CMD)
		printf("CMD ");
	if (c == ARG)
		printf("ARG ");
	if (c == TRUNC)
		printf("TRUNC ");
	if (c == APPEND)
		printf("APPEND ");
	if (c == INPUT)
		printf("INPUT ");
	if (c == PIPE)
		printf("PIPE ");
	if (c == INFILE)
		printf("INFILE ");
	if (c == OUTFILE)
		printf("OUTFILE ");
	if (c == HERDOC)
		printf("HERDOC ");
	if (c == LIMITER)
		printf("LIMITER ");
}

//lesks checked : done
void expand_list(char **env, t_list **list)
{
	t_list *tmp;
	int i;
	i = -1;
	tmp = *list;
	while(tmp)
	{
		if(tmp->cmd)
			tmp->cmd = ft_expand(env, tmp->cmd);
		if(tmp->args)
		{
			
			while(tmp->args[++i])
			{
				tmp->args[i] = ft_expand(env, tmp->args[i]);
				if(!check_command(tmp->args[i]))
					tmp->infile = -1;
			}
				
		}
		i = -1;
		tmp = tmp->next;
	}
}


void	ft_next(char *line, t_token *data, t_list *list)
{
	if(tokens(line, &data) == 258)
		return;
	get_cmd(&list, &data);
	expand_list(dep.env, &list);
	if (list)
		ft_exec(list);
	free (line);
	// system("leaks minishell");
}

char **ft_help_env(char **env)
{
	char	**new_env;
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		j = 0;
		new_env[i] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		while (env[i][j])
		{
			new_env[i][j] = env[i][j];
			j++;
		}
		new_env[i][j] = 0;
		i++;
	}
	new_env[i++] = ft_strdup("OLDPWD=");
	new_env[i] = NULL;
	return (new_env);
}

int	main(int ac, char **av, char **env)
{
	t_token	*data;
	t_list	*list;
	char	*line;

	data = malloc(sizeof(data));
	dep.env = ft_help_env(env);
	dep.env_copy = ft_help_env(env);
	dep.pwd = get_pwd("PWD=");
	list = NULL;
	(void)ac;
	(void)av;
	signal(SIGINT, handle_signal1);
	signal(SIGKILL, handle_signal2);
	while (1)
	{
		line = readline("\x1b[1m\x1b[33mminishell$ \033[0m");
		if (!line)
			break ;
		if(!check_cmd_syntax(line))
		{
			dep.exit_status = SYNTAX_ERROR;
			add_history(line);
			free(line);
			continue ;
		}
		add_history(line);
		ft_next(line, data, list);
	}
}
