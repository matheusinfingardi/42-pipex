/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minfinga <minfinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:36:05 by minfinga          #+#    #+#             */
/*   Updated: 2024/10/08 16:37:49 by minfinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exec(char *cmd, char **envp)
{
	char	**split_cmd;
	char	*path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], envp);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_tab(split_cmd);
		exit(127);
	}
	else if (execve(path, split_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: failed to execute: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		free_tab(split_cmd);
		exit(126);
	}
}

void	child(char **argv, int *pipefd, char **envp)
{
	int	fd_in;

	fd_in = open_file(argv[1], STDIN_FILENO);
	dup2(fd_in, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	exec(argv[2], envp);
}

void	parent(char **argv, int *pipefd, char **envp)
{
	int		fd_out;

	fd_out = open_file(argv[4], STDOUT_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (argc != 5 || argv[2][0] == '\0' || argv[3][0] == '\0')
		error_exit(1);
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child(argv, pipefd, envp);
	if (!ft_strncmp(argv[2], "sleep", 5) || !ft_strncmp(argv[2], "usleep", 6))
		waitpid(pid, &status, 0);
	parent(argv, pipefd, envp);
	return (0);
}
