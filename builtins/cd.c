/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:34:21 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/26 14:54:01 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_pwd(char *path)
{
	int	i;

	i = 0;
	while (dep.env[i])
	{
		if (ft_strnstr(dep.env[i], "PWD=", ft_strlen("PWD=")))
		{
			dep.env[i] = ft_strjoin("PWD=", path);
			dep.pwd = path;
		}
		i++;
	}
}

void	update_old_pwd(void)
{
	int	i;

	i = 0;
	while (dep.env[i])
	{
		if (ft_strnstr(dep.env[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			dep.env[i] = ft_strjoin("OLDPWD=", dep.pwd);
			printf("%s\n", dep.env[i]);
			return ;
		}
		i++;
	}
}

char	*get_pwd(char *str)
{
	char	*path;
	int		i;

	i = 0;
	while (dep.env[i])
	{
		if (ft_strnstr(dep.env[i], str, ft_strlen(str)))
			path = dep.env[i] + ft_strlen(str);
		i++;
	}
	if (!path || ft_strlen(path) == 0)
		path = getenv(str);
	return (path);
}

void	ft_cd(t_list *list)
{
	char	*path;
	int		i;
	i = 1;
	path = NULL;
	if (!list->args[1])
	{
		path = get_pwd("HOME=");
		chdir(path);
	}
	else if (list->args[1][0] == 0)
		return ;
	else if (list->args[1][0] == '~' && ft_strlen(list->args[1]) >= 1)
		path = get_pwd("HOME=");
	else
		path = list->args[i];
	if (list->args && path && chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", list->args[1]);
		dep.exit_status = 1;
	}
	update_old_pwd();
	path = getcwd(NULL, 0);
	dep.pwd = ft_strdup(getcwd(NULL, 0));
	if (path)
		update_pwd(path);
}
