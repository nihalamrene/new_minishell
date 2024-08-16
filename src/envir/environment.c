#include "../../includes/parse.h"

int	get_idx_of(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

void	*parse_env(char **env, t_envi **dup_env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return (NULL);
	while (*env)
	{
		i = get_idx_of(*env, '=');
		ft_lstadd_back_env(dup_env,
			ft_lstnew_env(ft_substr(*env, 0, i),
				ft_substr(*env, i + 1, ft_strlen(*env) - i), 0));
		env++;
	}
	return (dup_env);
}
