/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:52:16 by aankote           #+#    #+#             */
/*   Updated: 2023/03/23 23:20:31 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int is_std(char *val, t_list *list)
{
    if(!ft_strcmp("/dev/stdin", val) || !ft_strcmp("/dev/stdin/", val))
        return (1);
    if(!ft_strcmp("/dev/stdout", val) || !ft_strcmp("/dev/stdout/", val))
    {
        list->infile = 1;
        return (1);
    }

    if(!ft_strcmp("/dev/stderr", val) || !ft_strcmp("/dev/stderr/", val))
    {
        list->infile = 2;
        return (1);
    }
    return (0);
}

void get_infile(t_list *list, char *val)
{
    if(is_std(val,list))
        return;
    if(list->infile != -1)
    {
        list->infile = open(val, O_RDONLY);
        if(list->infile == -1 )
        {
            perror(val);
            list->perror = -1;
        }
    }
}

void get_outfile(t_list *list, char *val, int type)
{
     if(is_std(val, list))
        return;
    if(list->perror != -1)
    {
        if (type == OUTFILE)
            list->outfile = open(val, O_CREAT | O_TRUNC | O_RDWR, 0777);
        else
            list->outfile = open(val, O_CREAT | O_RDWR, 0777);
        if(list->outfile == -1)
        {
            perror(val);
            list->perror = -1;
        }
    }
}

void add_command(t_list **list, t_list **new)
{
    add_list(list, *new);
    *new = (t_list *)malloc(sizeof(t_list));
    list_init(*new);
}

void ft_add_str(char *ln, t_token **token,char *p, int *i)
{
    while (ln[*i] && !ignore_sep(ln[*i], ln, *i))
    {
        // while((ln[*i] == '\"' && (!quotes(ln, *i) || quotes(ln, *i) == 1))
        //     || ((ln[*i] == '\'' && (!quotes(ln, *i) || quotes(ln, *i) == 2))))
        //     (*i)++;
        p = ft_charjoin(p, ln[*i]);
        if((ln[*i + 1] && ignore_sep(ln[*i + 1], ln, *i)
            && !quotes(ln, *i + 1)) || !ln[*i + 1]
                || (ln[*i + 1] == ' ' && (!quotes(ln, *i + 1))))
        {
            ft_lstadd_back(token, ft_lstnew(CMD, p));
            break;
        }
        (*i) ++;
    }
}

void ft_add_opr(char *ln, t_token **token, char *p, int *i)
{
    while (ln[*i] && ignore_sep(ln[*i], ln, *i) && ln[*i] != ' ')
    {
        p = ft_charjoin(p, ln[*i]);
        if((ft_strcmp(p, "<") && ft_strcmp(p, ">")) || !ln[*i + 1])
        {
            ft_lstadd_back(token, ft_lstnew(CMD, p));
            break;
        }
        if ((!ft_strcmp(p, "<") && ln[*i + 1] != '<')
            || (!ft_strcmp(p, ">") && ln[*i + 1] != '>'))
        {
            ft_lstadd_back(token, ft_lstnew(CMD, p));
            break;
        }
        (*i) ++;
    }
}