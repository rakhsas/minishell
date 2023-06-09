/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:56:34 by aankote           #+#    #+#             */
/*   Updated: 2023/04/02 13:40:22 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct s_g_dependences g_dep;

// void	ft(int c)
// {
// 	if (c == CMD)
// 		printf("CMD ");
// 	if (c == ARG)
// 		printf("ARG ");
// 	if (c == TRUNC)
// 		printf("TRUNC ");
// 	if (c == APPEND)
// 		printf("APPEND ");
// 	if (c == INPUT)
// 		printf("INPUT ");
// 	if (c == PIPE)
// 		printf("PIPE ");
// 	if (c == INFILE)
// 		printf("INFILE ");
// 	if (c == OUTFILE)
// 		printf("OUTFILE ");
// 	if (c == HERDOC)
// 		printf("HERDOC ");
// 	if (c == LIMITER)
// 		printf("LIMITER ");
// }

//leaks checked : done
void	expand_list(char **env, t_list **list)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = *list;
	while (tmp)
	{
		if (tmp->cmd)
			tmp->cmd = ft_expand(env, tmp->cmd);
		if (tmp->args)
		{
			while (tmp->args[++i])
			{
				tmp->args[i] = ft_expand(env, tmp->args[i]);
				if (!check_command(tmp->args[0]))
				{
					tmp->infile = -1;
				}
			}
		}
		i = -1;
		tmp = tmp->next;
	}
}

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*next;
	int		i;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->cmd)
			free(current->cmd);
		i = 0;
		if (current->args)
		{
			while (current->args[i] != NULL)
			{
				free(current->args[i]);
				i++;
			}
		}
		free(current->args);
		free(current);
		current = next;
	}
}

void	ft_lstclear(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->val);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	ft_next(char *line, t_token *data, t_list *list)
{
	if (tokens(line, &data) == 258)
	{
		ft_lstclear(&data);
		return;
		free(line);
		return ;
	}
	get_cmd(&list, &data);
	ft_lstclear(&data);
	expand_list(g_dep.env, &list);
	if (list)
		ft_exec(list);
	free_list(list);
	free(line);
}

char	**ft_help_env(char **env, int n)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	if (n == 0)
		new_env = (char **)malloc(sizeof(char *) * (i + (n + 1) + 1));
	else
		new_env = (char **)malloc(sizeof(char *) * (i + n + 1));
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
	if (n == 0)
		new_env[i++] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	new_env[i] = NULL;
	return (new_env);
}

int	checker(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ftsearch(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_token	*data;
	t_list	*list;
	char	*line;

	data = malloc(sizeof(data));
	g_dep.env = ft_help_env(env, checker(env));
	g_dep.env_copy = ft_help_env(env, checker(env));

	g_dep.pwd = get_pwd("PWD=");
	list = NULL;
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_signal2);
		// line = readline("\x1b[1m\x1b[33mminishell$ \033[0m");
		line = readline("minishell$ ");
		if (!line)
		{
			g_dep.exit_status = 0;
			break ;
		}
		if (!check_cmd_syntax(line))
		{
			g_dep.exit_status = SYNTAX_ERROR;
			add_history(line);
			free(line);
			continue ;
		}
		if (ft_strlen(line))
			add_history(line);
		ft_next(line, data, list);
	}
}
