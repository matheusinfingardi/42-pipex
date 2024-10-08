/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minfinga <minfinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:46:03 by minfinga          #+#    #+#             */
/*   Updated: 2024/10/07 17:13:38 by minfinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	error_exit(int exit_nbr)
{
	if (exit_nbr == 1)
		ft_putstr_fd("Error: ./pipex infile cmd cmd outfile\n", 2);
	exit(EXIT_FAILURE);
}

int	open_file(char *file, int in_or_out)
{
	int	return_fd;

	if (in_or_out == STDIN_FILENO)
		return_fd = open(file, O_RDONLY, 0777);
	if (in_or_out == STDOUT_FILENO)
		return_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (return_fd == -1)
		exit(EXIT_FAILURE);
	return (return_fd);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_env(char *name, char **envp)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		sub = ft_substr(envp[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (envp[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*exec_path;
	char	**all_path;
	char	*part_path;
	char	**split_cmd;

	i = -1;
	all_path = ft_split(get_env("PATH", envp), ':');
	split_cmd = ft_split(cmd, ' ');
	while (all_path[++i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		exec_path = ft_strjoin(part_path, split_cmd[0]);
		free(part_path);
		if (access(exec_path, F_OK | X_OK) == 0)
		{
			free_tab(split_cmd);
			return (exec_path);
		}
		free(exec_path);
	}
	free_tab(all_path);
	free_tab(split_cmd);
	return (cmd);
}
