/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:00:37 by ahakam            #+#    #+#             */
/*   Updated: 2022/03/29 18:25:27 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int *fd, int file1, int file2)
{
	if (file1 == -1)
	{
		perror("first file not found !");
		exit(1);
	}
	if (file2 == -1)
	{
		perror ("seconde file not found !");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
	close(file1);
	close(file2);
	wait(NULL);
	wait(NULL);
}

void	ft_child(char **av1, char **envp, int *fd, int *file1)
{		
	close(fd[0]);
	if (dup2(*file1, 0) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(*file1);
	if (dup2(fd[1], 1) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(fd[1]);
	execve(av1[0], av1, envp);
	perror("execve failed <3");
	exit(1);
}

void	ft_child2(char **av2, char **envp, int *fd, int *file2)
{
	close(fd[1]);
	if (dup2(fd[0], 0) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(fd[0]);
	if (dup2(*file2, 1) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(*file2);
	execve(av2[0], av2, envp);
	perror("execve failed");
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_fd	list;
	int		k;

	(void) argc;
	list.file1 = open(argv[1], O_RDONLY);
	list.file2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	list.cmd = comd(envp, argv[2]);
	list.cmd2 = comd(envp, argv[3]);
	if (argc == 5)
	{
		pipe(list.fd);
		list.id = fork();
		if (list.id == -1)
			perror("fork failed");
		if (list.id == 0)
			ft_child(list.cmd, envp, list.fd, &list.file1);
		k = fork();
		if (k == -1)
			perror("fork failed");
		if (k == 0)
			ft_child2(list.cmd2, envp, list.fd, &list.file2);
		ft_close(list.fd, list.file1, list.file2);
	}
	else
		perror("to many  or few arguments !");
}
