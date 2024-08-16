#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../minishell.h"
# define BLUE "\e[1;36m"
# define GREEN "\e[0;92m"
# define RED "\e[0;31m"
# define RESET "\e[0m"

# define TRUE 1
# define FALSE 0

enum
{
	heredoc,
	in,
	out,
	append,
};

typedef struct s_help
{
	int				i;
	int				j;
	char			*prev;
	char			*str;
	char			*str1;
	char			*last_str;
	char			*join;
	char			*check_str;
}					t_help;

typedef struct s_redi
{
	int				type;
	char			*file;
	int				must_exp;
	struct s_redi	*next;
}					t_redi;

typedef struct s_token
{
	int				type;
	char			*content;
	int				expand;
	int				check;
	struct s_token	*next;
}					t_token;

typedef struct s_envi
{
	char			*key;
	char			*value;
	int				is_min;
	struct s_envi	*next;
}					t_envi;

typedef struct s_cmd
{
	char			**cmd;
	int				pipe;
	int				err;
	int				type;
	t_redi			*in;
	t_redi			*out;
	struct s_cmd	*next;
}					t_cmd;

enum
{
	WORD,
	PIPE,
	DOUBLE,
	SINGLE,
	OPERATOR,
	HYPHEN,
	SPACEE,
	SINGLE_EXP,
};

//*----------LEXER----------*//
int					is_all_spaces(char *str);
int					token_line(char *line, t_token **token);
int					take_separator(char *line, t_token **token);
int					whish_separator(char *line);
void				check_args(int ac, char **av, t_envi **dup_env, char **env);
int					with_quotes(char *line, t_token **token, int c, int *flag);
int					take_word(char *line, t_token **token, int *flag);
int					type_token(char *content);

//*---------lst_func--------*//
t_token				*ft_lstnew_m(char *content);
t_token				*ft_lstlast_m(t_token *lst);
void				ft_lstadd_back_m(t_token **lst, t_token *new);
void				ft_lstdelone_t(t_token *lst);
void				ft_lstclear_t(t_token **lst);
t_envi				*ft_lstnew_env(char *key, char *value, int val);
t_envi				*ft_lstlast_env(t_envi *lst);
void				ft_lstadd_back_env(t_envi **lst, t_envi *new);
void				ft_lstclear(t_token **lst);
void				ft_lstdelone(t_token *lst);
t_cmd				*ft_lstnew_cmd(void);
t_cmd				*ft_lstlast_cmd(t_cmd *lst);
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void				clear_cmds(t_cmd **cmd);
int					ft_strchr_2(const char *str, int c);
void				ft_lstadd_back_redi(t_redi **lst, t_redi *new);
t_redi				*ft_lstnew_redi(char *out, int type);
t_redi				*ft_lstlast_redi(t_redi *lst);
void				ft_lstclear_2(t_redi **lst);

//*---------env--------*//
void				*parse_env(char **env, t_envi **dup_env);
int					get_idx_of(char *str, int c);

//*---------expand--------*//
void				ft_minishell(t_envi **env, t_token **token, t_cmd **cmd);
void				handler_expand(t_token **token, t_envi *env, t_token *tok);
void				trim_quotes(t_token *token);
void				check_exp(t_token *tok, t_envi *env);
void				hyphen_exp(t_token *tok, t_envi *env);
char				*get_value_of_exp(t_envi *env, char *key);
int					must_expand(int next);
int					exp_here(int curr, int next);
int					count(char *str);
void				expand_var(t_envi *env, char **content);
void				here_doc_exp(t_token *token);
int					join_str(t_token **token, t_token *tmp);
void				ft_free(char **str);
void				set_type(t_token *tok);
void				ft_free_2(char *str1, char *str2, char *str3);
void	ft_free_tab2(char **arr);

//*---------checks_syntax--------*//
void				remove_spaces(t_token **token, t_token *tok);
void				ft_remove(t_token *tmp, t_token **curr, t_token **token);
int					check_syntax(t_token *token);
int					ft_putendl_fd_2(char *s, char *str, int fd);
int					find_error(t_token *token, t_token *tmp);
int					error_format(t_token *token, t_token *tmp, int i);

//*---------parsing--------*//
void				parse_cmd(t_token **token, t_cmd **cmd);
void				init_cmd(t_token **token, t_cmd **cmd);
void				rub_operator(t_cmd *cmd, t_token *token, t_token **tok);
void				is_operator(t_token *token, t_cmd *cmd);
int					check_redir(t_token *token);
void				set_oper(t_token *token, t_redi **redir, int type);
void				set_cmd(t_cmd *cmd);
void				init_args(t_token *token, t_cmd *cmd);
void				fill_cmd(t_cmd *cmd, t_token *token, int *i);

/*------exec------*/
void    exe_cmd(char **cmd, t_envi *envi);
void	handel_red(t_cmd *cmd, int *fd_in, int *fd_out);
void    _exec(t_cmd *cmd, t_envi **envi);
#endif
