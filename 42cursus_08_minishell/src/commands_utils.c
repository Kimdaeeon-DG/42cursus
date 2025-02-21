/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:22 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:23 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_options(t_shell *msh, int i)
{
	while (msh->tokens[++i])
	{
		if (msh->tokens[i][0] == '-')
		{
			print_error(ERROR_OPTIONS, msh->tokens[0], 2);
			return (YES);
		}
	}
	return (NO);
}

void	check_if_is_builtin(t_shell *msh, char *cmd)
{
	int	size;

	size = ft_strlen(cmd);
	if ((!ft_strncmp(cmd, "echo", 4) && size == 4)
		|| (!ft_strncmp(cmd, "cd", 2) && size == 2)
		|| (!ft_strncmp(cmd, "pwd", 3) && size == 3)
		|| (!ft_strncmp(cmd, "export", 6) && size == 6)
		|| (!ft_strncmp(cmd, "unset", 5) && size == 5)
		|| (!ft_strncmp(cmd, "env", 3) && size == 3)
		|| (!ft_strncmp(cmd, "exit", 4) && size == 4))
		msh->is_builtin = YES;
	else
		msh->is_builtin = NO;
}

void	implicit_cat(t_shell *msh, int i)
{
	char	*tmp[50];

	tmp[0] = ft_strdup("cat"); // tmp에 맨 앞에 cat 넣음
	while (msh->cmds[++i])
		tmp[i + 1] = ft_strdup(msh->cmds[i]); // 복제해서 tmp에 담음 (깊은 복제)
	tmp[i + 1] = NULL;
	i = -1;
	free_split(msh->cmds, NO); // 있는거 싹 지우고
	while (tmp[++i]) // tmp 있는걸 다시 담음
		msh->cmds[i] = tmp[i];
	msh->cmds[i] = NULL; // 다 썼으니 NULL
}

void	check_first_cmd(t_shell *msh)
{
	if ((msh->cmds[0][0] == '>' && !msh->cmds[1]) // 처음이 '>'고 뒤에 값이 없거나
		|| (!ft_strncmp(msh->cmds[0], "<< ", 3) && msh->cmds[0][3] != '\0') // "<< "이고 뒤에 값이 있거나
		|| (!ft_strncmp(msh->cmds[0], "<<", 2) && msh->cmds[0][2] != '\0')) // "<<"이고 뒤에 값이 있으면?
	{
		implicit_cat(msh, -1); //  cat이 없지만 cat 작업을 수행 해야 하니까 cat을 cmds에 넣어줌
		msh->parse.id++; // 처리 중인 명령어 id 증가
		msh->control = COMMON; // 일반적인 경우임
	}
	else if (msh->cmds[0][0] == '>' && msh->cmds[1] && msh->cmds[1][0] == '|') // > 다음 |가 나오면
		msh->control = SPECIAL; // 특별한 경우임. 사실 에러인데 나중에 처리함
	else if (msh->cmds[0][0] != '>')
		msh->control = COMMON; // 일반적임
}

void	print_error_if_command_fail(t_shell *msh)
{
	g_exit = 127;
	if (msh->tokens[0][0] == '.' && msh->tokens[0][1] == '/')
		print_error(ERROR_DIR, msh->tokens[0], 126);
	else if (msh->tokens[0][0] != '|' && msh->tokens[0][0] != '<')
		print_error(ERROR_CMD, msh->tokens[0], 127);
	else if (msh->tokens[1] && msh->tokens[0][0] != '<')
		print_error(ERROR_CMD, msh->tokens[0], 127);
}
