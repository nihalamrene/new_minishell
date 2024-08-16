#include "../../includes/parse.h"

void	trim_quotes(t_token *token)
{
	char	*tmp;

	while (token)
	{
		tmp = token->content;
		if (!*tmp)
		{
			free(tmp);
			token->content = ft_strdup("");
			return ;
		}
		if (token->type == DOUBLE)
		{
			token->content = ft_strtrim(token->content, "\"");
			free(tmp);
		}
		if (token->type == SINGLE)
		{
			token->content = ft_strtrim(token->content, "\'");
			free(tmp);
		}
		token = token->next;
	}
}

char	*get_value_of_exp(t_envi *env, char *key)
{

	while (env && ft_strcmp(env->key, key) != 0)
		env = env->next;
	if (env && ft_strcmp(env->key, key) == 0)
	{
		free(key);
		return (ft_strdup(env->value));
	}
	free(key);
	return (NULL);
}

void	hyphen_exp(t_token *tok, t_envi *env)
{
	char	*tmp;

	if (tok)
	{
		tmp = tok->content;
		tok->content = get_value_of_exp(env, ft_strdup("HOME"));
		free(tmp);
	}
}

int	must_expand(int next)
{
	if (!ft_isalnum(next) && next != '_')
		return (1);
	return (0);
}
