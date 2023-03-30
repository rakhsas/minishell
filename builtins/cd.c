/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:34:21 by rakhsas           #+#    #+#             */
/*   Updated: 2023/03/30 23:13:36 by rakhsas          ###   ########.fr       */
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
			free(dep.env[i]);
			dep.env[i] = ft_strjoin("PWD=", path);
			dep.pwd = path;
		}
		i++;
	}
	// free(path);
}

void	update_old_pwd(void)
{
	int	i;

	i = 0;
	while (dep.env[i])
	{
		if (ft_strnstr(dep.env[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			free(dep.env[i]);
			dep.env[i] = ft_strjoin("OLDPWD=", dep.pwd);
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
		if (chdir(path) == -1)
		{
			print_error("minishell: ", list->args[1]);
			ft_putendl_fd(": HOME not set", 2);
			dep.exit_status = ERROR;
			return ;
		}
	}
	else if (list->args[1][0] == 0)
		return ;
	else if (list->args[1][0] == '-')
	{
		// printf("differ:%d\n\\'pwd: %s'\n\\'oldpwd: %s'\n", ft_strcmp(get_pwd("OLDPWD="),get_pwd("PWD=")), get_pwd("PWD="), get_pwd("OLDPWD="));
		if (ft_strcmp(get_pwd("OLDPWD="),get_pwd("PWD=")) == 0)
		{
			ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			dep.exit_status = ERROR;
		}
		else
		{
			chdir(get_pwd("OLDPWD="));
			printf("%s\n",get_pwd("OLDPWD="));
		}
	}
	else if (list->args[1][0] == '~' && ft_strlen(list->args[1]) >= 1)
		path = get_pwd("HOME=");
	else
		path = list->args[i];
	if (list->args && path && chdir(path) == -1)
	{
		print_error("cd: ", list->args[1]);
		ft_putendl_fd(": No such file or directory", 2);
		dep.exit_status = ERROR;
	}
	update_old_pwd();
	path = getcwd(NULL, 0);
	if (path)
	{
		update_pwd(path);
		free(path);
	}
}
