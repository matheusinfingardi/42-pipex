/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minfinga <minfinga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:34:46 by minfinga          #+#    #+#             */
/*   Updated: 2024/10/01 13:55:06 by minfinga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libs/ft_printf/include/ft_printf.h"
# include "../libs/libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>  
# include <stdlib.h>

int		main(int argc, char **argv, char **envp);
void	parent(char **argv, int *pipefd, char **envp);
void	child(char **argv, int *pipefd, char **envp);
void	exec(char *cmd, char **envp);

void	error_exit(int n_exit);
int		open_file(char *file, int in_or_out);
void	ft_free_tab(char **tab);
char	*ft_getenv(char *name, char **envp);
char	*get_path(char *cmd, char **envp);

int		create_child(char **argv, char **envp, int *pipefd);
int		create_parent(char **argv, char **envp, int *pipefd);

#endif