/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:09:51 by aankote           #+#    #+#             */
/*   Updated: 2023/03/29 17:50:44 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int pipe_errors(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    while(tmp)
    {
        if(tmp->type == PIPE)
        {
            if(!tmp->next || !tmp->prev)
            {
                printf("bash: syntax error near unexpected token '|'\n");
                dep.exit_status = SYNTAX_ERROR;
                return (0);
            }
            else if (tmp->next && tmp->next->type == PIPE)
            {
                printf("bash: syntax error near unexpected token '||'\n");
                dep.exit_status = SYNTAX_ERROR;
                return(0);
            }
        }
        tmp = tmp->next;
    }
    return (1);
}

int check_oper(t_token **token)
{
    t_token *tmp;

    tmp = *token;
    while(tmp)
    {
        if(is_opr(tmp->type) && tmp->next && is_opr(tmp->next->type))
        {
            printf("syntax error near unexpected token %s\n", tmp->next->val);
            dep.exit_status = SYNTAX_ERROR;
            return (0);
        }
        if(is_opr(tmp->type) && !tmp->next)
        {
             printf("syntax error near unexpected token 'newline'\n");
             dep.exit_status = SYNTAX_ERROR;
            return (0);
        }
         if(is_opr(tmp->type) && tmp->next->type == PIPE)
        {
             printf("syntax error near unexpected token %s\n", tmp->next->val);
             dep.exit_status = SYNTAX_ERROR;
            return (0);
        }
        tmp = tmp->next;
    }
    return(1);
}

//we have to use this function befor do exoanting!!.

int  ft_error_char(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(is_error_char(str[i]) && (!quotes(str,  i)
            || quotes(str, i) == 1))
        {
            printf("SYNTAX ERROR!\n");
            dep.exit_status = SYNTAX_ERROR;
            return (0);
        }
        i++;
    }
    return (1);
}
//function closedir  automaticlly will free dr
int is_dir(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '/')
            return (0);
        i++;
    }
    return(1);
}
int check_command(char *str)
{
    DIR *dr;
    if(str && !is_dir(str))
    {
        if(!str[1])
            printf("bash: %s :is a directory\n", str);
        else
        {
            dr = opendir(str);
            if(opendir(str))
                printf("bash: %s :is a directory\n", str);
            else
                printf("bash: %s: No such file or directory\n", str);
            if(dr)
                closedir(dr);
        }
        dep.exit_status = IS_DIRECTORY;
        return (0);
    }
    return (1);
}