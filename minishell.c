/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:56:34 by aankote           #+#    #+#             */
/*   Updated: 2023/03/29 13:46:43 by rakhsas          ###   ########.fr       */
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
int	tokens(char *line, t_token **token)
{
	t_token	*tmp;

	get_token(line, token);

	tmp = *token;
	while (tmp)
	{
		type_arg(tmp);
		if(tmp->type == INFILE || tmp->type == OUTFILE)
			tmp->val = ft_expand(dep.env, tmp->val);
		tmp = tmp->next;
	}
	// if(!pipe_errors(token))
	// 	return (0);
	return(1);
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
				tmp->args[i] = ft_expand(env, tmp->args[i]);
		}
		i = -1;
		tmp = tmp->next;
	}
}

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
		printf("%d", tmp->infile);
		if(tmp->infile == -1)
		{
			printf("error");
			return;
		}
		tmp = tmp->next;
	}
}


void	ft_next(char *line, t_token *data, t_list *list)
{
	if(!tokens(line, &data))
		return;
	// if(!check_oper(&data))
	// {
	// 	return;
	// }
	get_cmd(&list, &data);
	expand_list(dep.env, &list);
	if (list)
		ft_exec(list);
	free (line);
	// system("leaks minishell");
}

void handle_signal1(int s)
{
	s = 0;
	ft_putstr_fd("", 2);
	rl_replace_line("\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void handle_signal2(int s)
{
	(void) s;
	exit(0);
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
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_signal1);
		line = readline("\x1b[1m\x1b[33mminishell$ \033[0m");
		if (!line)
			break ;
		if (!check_cmd_syntax(line))
		{
			dep.exit_status = ERROR;
			add_history(line);
			free(line);
			continue ;
		}
		add_history(line);
		ft_next(line, data, list);
		// dep.exit_status = SUCCESS;
	}
}
