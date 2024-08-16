#include "../../includes/parse.h"

void	_process(char **cmd, int fd_in, int fd_out, t_envi *envi)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("error dup\n");
		return ;
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("error dup2\n");
		return ;
	}
	exe_cmd(cmd, envi);
}

int	exe_first_cmd(t_cmd *cmd, t_envi *envi)
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];

	if (pipe(fd_pipe))
	{
		perror("pipe err\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("error fork\n");
		return (-1);
	}
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_in = STDIN_FILENO;
		fd_out = fd_pipe[1];
		if (!cmd->next)
			fd_out = STDOUT_FILENO;
		handel_red(cmd, &fd_in, &fd_out);
		_process(cmd->cmd, fd_in, fd_out, envi);
	}
	if (!cmd->next)
		return (close(fd_pipe[1]), close(fd_pipe[0]), -1);
	return (close(fd_pipe[1]), fd_pipe[0]);
}

int	cmd_med(t_cmd *cmd, t_envi *envi, int fd_in)
{
    int     fd_out;
    int     fd_pipe[2];
    pid_t   pid;

	if (pipe(fd_pipe))
	{
		perror("pipe err\n");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("error fork\n");
		return (-1);
	}
	if (pid == 0)
	{
		close(fd_pipe[0]);
		fd_out = fd_pipe[1];
		//redi handle
		handel_red(cmd, &fd_in, &fd_out);
		_process(cmd->cmd, fd_in, fd_out, envi);
	}
	return (close(fd_pipe[1]), close(fd_in), fd_pipe[0]);
}

void	last_cmd(t_cmd *cmd, t_envi *envi, int fd_in)
{
	pid_t	pid;
	int		fd_out;

	pid = fork();
	if (pid == -1)
	{
		perror("error pipe\n");
		return ;
	}
	if (pid == 0)
	{
		fd_out = STDOUT_FILENO;
		//handel redi
		handel_red(cmd, &fd_in, &fd_out);
		_process(cmd->cmd, fd_in, fd_out, envi);
		// write(2, "in\n", 3);
	}
	close(fd_in);
}
int	count_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
void	_exec(t_cmd *cmd, t_envi **envi)
{
	int	fd;
	int	nbr_cmd;

	nbr_cmd = count_cmd(cmd);
	fd = exe_first_cmd(cmd, *envi);
	cmd = cmd->next;
	while (cmd && cmd->next )
	{
		fd = cmd_med(cmd, *envi, fd);
		cmd = cmd->next;
	}
	if (cmd)
		last_cmd(cmd, *envi, fd);
	while (nbr_cmd--)
		wait(NULL);
}
