/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:53:18 by aankote           #+#    #+#             */
/*   Updated: 2023/03/31 01:12:14 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define EMPTY 0
# define CMD 1
# define INFILE 3
# define OUTFILE 4
# define APPOUT 5
# define ARG 6
# define LIMITER 7
# define TRUNC 8
# define APPEND 9
# define INPUT 10
# define PIPE 11
# define HERDOC 12

/********exit status*******/

# define ERROR 1
# define ERROR2 2
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127
# define SYNTAX_ERROR 258

/************************/

typedef struct s_token
{
	int				type;
	char			*val;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_g_dependences
{
	int				exit_status;
	char			**files;
	char			**env;
	char			**env_copy;
	char			*pwd;
	char			*str;
	char			**content;
	char			**staar;
}					t_dependences;

typedef struct s_list
{
	char			*cmd;
	char			**args;
	int				infile;
	int				outfile;
	int				append_in;
	int				perror;
	struct s_list	*next;
}					t_list;

void				ft_skip_spaces(char *str, int *i);
void				ft_lstadd_back(t_token **lst, t_token *new);
t_token				*ft_lstnew(int type, char *val);
int					check_operators(char c);
int					ft_handel_quotes(char *line);
int					check_single_quotes(char *str);
char				*fill_str(char *str);
void				type_arg(t_token *token);
void				get_token(char *line, t_token **token);
char				*get_value(char **env, char *var);
void				get_cmd(t_list **list, t_token **token);
void				add_list(t_list **lst, t_list *new);
void				add_command(t_list **list, t_list **new);
void				list_init(t_list *list);
char				**ft_realloc(char **p, char *str);
void				free_double(char **p);
int					ft_strcmp(const char *s1, const char *s2);

/*******UTILS********/

char				*ft_charjoin(char *s, char c);
char				*ft_trim(char *arg);
char				*ft_join_free(char *s1, char *s2);
/*******lexer*******/

void				get_infile(t_list *list, char *val);
void				get_outfile(t_list *list, char *val, int type);
int					quotes(char *line, int index);
void				ft_add_str(char *ln, t_token **token, int *i);
void				ft_add_opr(char *ln, t_token **token, int *i);
int					ignore_sep(char c, char *line, int index);
int					is_std(char *val, t_list *list);
void				get_token(char *line, t_token **token);
int					tokens(char *line, t_token **token);

/**** expanding ********/
char				*ft_get_arg(char **env, char *str, int *i);
char				*ft_expand(char **env, char *str);
/******* Builtins ********/
void				echo(t_list *list);
// void		expaned_arg(char **env, char *arg);
int					ft_exit(t_list *data);

/***********HERE-DOC************/
// int here_doc(char *limiter, char **env, t_file **f);
char				*here_doc(char *limiter, char **env);
// int   		here_doc(char *limiter, char **env, t_file **f);
void				unlink_files(char **files);
char				*ft_herd_exp(char **env, char *str);
void				handle_signal(int sg);
int					do_exp_inp(char *limiter);
void				open_her(t_token **token, char **env);
int					ft_listsize(t_list *list);
/************ EXECUTION ************/
void				ft_env(int inf);
void				ft_unset(t_list *lst);
void				ft_cd(t_list *list);
char				*get_pwd(char *str);
void				ft_export(t_list *list);
char				*ft_search(char *str, char c);
void				ft_exec(t_list *list);
char				*get_arg(void);
void				main_execution(t_list *list);

/**SYNTAX ERROR**/
int					is_error_char(char c);
int					pipe_errors(t_token **token);
int					is_opr(int type);
int					check_oper(t_token **token);
int					ft_error_char(char *str);
int					check_command(char *str);
int					check_token_syntax(t_token **token);
int					check_quotes(char *str);
int					check_cmd_syntax(char *str);
int					check_herdoc(t_token **token);
int					is_dir(char *str);

/************MAIN UTILS****************/

void				ft_free_token(t_token **list);
void				free_list(t_list *list);
void				ft_ck(t_list **lst);
void				handle_signal1(int s);
void				handle_signal2(int s);
void				ft(int c);
/************* Globale struct **************/
t_dependences		g_dep;
#endif
// echo 'dhfhygnfhgynf'