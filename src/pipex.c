/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minfinga <minfinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:36:05 by minfinga          #+#    #+#             */
/*   Updated: 2024/10/01 14:53:33 by minfinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	exec(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], envp);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(127);
	}
	else if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("pipex: failed to execute: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(126);
	}
}

void	child(char **argv, int *pipefd, char **envp)
{
	int	fd;

	fd = open_file(argv[1], STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	exec(argv[2], envp);
}

void	parent(char **argv, int *pipefd, char **envp)
{
	int	fd;

	fd = open_file(argv[4], STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	exec(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (argc != 5 || argv[3][0] == '\0')
		error_exit(1);
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
		child(argv, pipefd, envp);
	else if (pid > 0)
	{
		if (!ft_strncmp(argv[2], "sleep", 5))
			waitpid(pid, &status, 0);
		parent(argv, pipefd, envp);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}
