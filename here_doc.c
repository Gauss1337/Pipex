/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:00:37 by ahakam            #+#    #+#             */
/*   Updated: 2022/04/01 22:41:45 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_bonus(int *file1, int file2, int file3)
{
	close(*file1);
	close(file2);
	close(file3);
}

void	ft_child(char **av1, char **envp, int *fd, int file1)
{
	close(fd[0]);
	dup2(file1, 0);
	if (dup2(file1, 0) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(file1);
	dup2(fd[1], 1);
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

void	ft_child2(char **av2, char **envp, int *fd, int file2)
{
	close(fd[1]);
	dup2(fd[0], 0);
	if (dup2(fd[0], 0) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(fd[0]);
	dup2(file2, 1);
	if (dup2(file2, 1) == -1)
	{
		perror("duplication failed !");
		exit(1);
	}
	close(file2);
	execve(av2[0], av2, envp);
	perror("execve failed");
	exit(1);
}

void	ft_fork(t_fd *list, char **envp, char **argv, int argc)
{
	if (argc == 6)
	{
		list->cmd = comd(envp, argv[3]);
		list->cmd2 = comd(envp, argv[4]);
		pipe(list->fd);
		list->id = fork();
		if (list->id == -1)
			perror("fork failed");
		if (list->id == 0)
			ft_child(list->cmd, envp, list->fd, list->file1);
		list->id = fork();
		if (list->id == -1)
			perror("fork failed");
		if (list->id == 0)
			ft_child2(list->cmd2, envp, list->fd, list->file2);
		ft_close_bonus(list->fd, list->file1, list->file2);
	}
	else
		perror("to many  or few arguments !");
	unlink(argv[1]);
}

void	here_doc(int argc, char **argv, char **envp)
{
	t_fd	list;

	(void) argc;
	list.delimiter = argv[2];
	list.file1 = open(argv[1], O_CREAT | O_RDWR, 0644);
	list.temp = get_next_line(0);
	if (!list.temp)
		exit(1);
	list.line = ft_substr(list.temp, 0, ft_strlen(list.temp) - 1);
	free(list.temp);
	while (ft_strcmp_bonus(list.line, list.delimiter) != 0)
	{
		write(list.file1, list.line, ft_strlen(list.line));
		write(list.file1, "\n", 1);
		list.temp = get_next_line(0);
		free(list.line);
		list.line = ft_substr(list.temp, 0, ft_strlen(list.temp) - 1);
		free(list.temp);
	}
	free(list.line);
	close(list.file1);
	list.file1 = open(argv[1], O_CREAT | O_RDWR, 0644);
	list.file2 = open(argv[5], O_WRONLY | O_APPEND | O_CREAT, 0644);
	ft_fork(&list, envp, argv, argc);
}
