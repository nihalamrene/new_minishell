#include "../../includes/parse.h"
 void	error_cmd(char *cmd, char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(err_msg, 2);
	exit(1);
}

// static void	sp_free(char **env)
// {
// 	int	i;

// 	i = -1;
// 	while (env && env[++i])
// 		free(env[i]);
// }

char    **get_env(t_envi *envi)
{
    char    **env;

    while (envi)
    {
        if (ft_strcmp(envi->key, "PATH") == 0)
            break ;
        envi = envi->next;
    }
    env = NULL;
    if (envi)
        env = ft_split(envi->value, ':');
    return (env);
}
char    *get_path_cmd(char *cmd, char **env)
{
    char	*path;
    int		i;

	if (!access(cmd, F_OK))
        return (cmd);
	i = -1;
    while (env && env[++i])
	{
		path = ft_strjoin(ft_strjoin(env[i], "/"), cmd);
		if (!access(path, F_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

void    exe_cmd(char **cmd, t_envi *envi)
{
    char    **env;
    char    *path;

    env = get_env(envi);
	if (!env)
		error_cmd(*cmd, ": No such file or directory\n");
    path = get_path_cmd(*cmd, env);
	if (!path)
	{
		free(env);
		error_cmd(*cmd, ": command not found\n");
	}
	execve(path, cmd, env);
	free(path);
	// sp_free(env);
	free(env);
}
