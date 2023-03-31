/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:53:31 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:14:39 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*env[i][len] == '=' for handel if you put var 
like (US) th result will be "aankoteER=aankote"*/
char	*get_value(char **env, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var);
	while (env[++i] && var[0])
	{
		if (!ft_strncmp(env[i], var, len) && env[i][len + 1]
			&& env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (ft_strdup(""));
}

char	*ft_get_arg(char **env, char *str, int *i)
{
	char	*p;
	char	*val;

	p = ft_strdup("");
	if (!ft_isalnum(str[*i + 1]) && str[(*i + 1)] != '?' && !quotes(str, *i
			+ 2))
	{
		while (str[*i] && str[*i] != '$')
			p = ft_charjoin(p, str[*i++]);
		if (str[*i] == '$')
			p = ft_charjoin(p, str[*i++]);
		return (p);
	}
	if (str[(*i + 1)] == '?')
	{
		(*i)++;
		return (free(p), ft_itoa(g_dep.exit_status));
	}
	while (str[++(*i)] && ft_isalnum(str[*i]))
		p = ft_charjoin(p, str[*i]);
	(*i)--;
	val = get_value(env, p);
	return (free(p), val);
}

//leaks : visited
char	*ft_expand(char **env, char *str)
{
	int		i;
	char	*p;
	char	*value;

	i = -1;
	p = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$' && (quotes(str, i) == 0 || quotes(str, i) == 1))
		{
			value = ft_get_arg(env, str, (&i));
			p = ft_join_free(p, value);
		}
		else
		{
			if ((str[i] != '\'' && str[i] != '\"'))
				p = ft_charjoin(p, str[i]);
			if (str[i] == '\'' && quotes(str, i) == 1)
				p = ft_charjoin(p, str[i]);
			if (str[i] == '\"' && quotes(str, i) == 2)
				p = ft_charjoin(p, str[i]);
		}
	}
	free(str);
	return (p);
}

char	*ft_herd_exp(char **env, char *str)
{
	int		i;
	char	*p;
	char	*value;

	i = -1;
	p = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$')
		{
			value = ft_get_arg(env, str, (&i));
			p = ft_join_free(p, value);
		}
		else
			p = ft_charjoin(p, str[i]);
	}
	free(str);
	return (p);
}
