/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:20 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:21 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_redirections(t_shell *msh)
{
	if (msh->parse.id > 1 && msh->cmds[msh->id][0] != '<'
		&& msh->cmds[msh->id][0] != '>')
		msh->id++;
	msh->file_name = NULL;
	msh->file_error = NULL;
	while (msh->cmds[msh->id] && msh->cmds[msh->id][0] != '|')
	{
		redirect_out(msh, msh->id, NULL); // ">"나 ">>" 일 때 실행
		redirect_in(msh, msh->id, NULL, NULL); // '<'나 "<<" 일 때 실행
		if (msh->file_error)
		{
			msh->error_flag = YES;
			print_error(ERROR_DIR, msh->file_error, 1);
			msh->fdin = STDIN_FILENO;
			free(msh->file_error);
			free(msh->tmp_cmd);
			msh->tmp_cmd = NULL;
			break ;
		}
		msh->id++;
	}
}

void	command_handler(t_shell *msh)
{
	msh->tmp_cmd = ft_strdup(msh->cmds[msh->id]);
	check_redirections(msh); // redirections 처리
	if (!msh->error_flag && !msh->ctrlc
		&& (msh->control == COMMON || msh->control == SPECIAL))
	{
		if (msh->is_first_time && msh->control == SPECIAL)
		{
			msh->is_first_time = NO;
			free (msh->tmp_cmd);
			msh->tmp_cmd = NULL;
			return ;
		}
		get_tokens(msh); //
		if (msh->tokens && msh->tokens[0])
		{
			check_if_is_builtin(msh, msh->tokens[0]);
			if (msh->fdin != -1 && msh->tokens && msh->tokens[0])
				create_child_process(msh, msh->fdin, msh->fdout);
			free_split(msh->tokens, YES);
			msh->tokens = NULL;
		}
		free(msh->token.print);
	}
	clean_handler(msh);
}

void	init_control_flags(t_shell *msh, int i)
{
	msh->id = 0;
	msh->cat_case = NO;
	msh->is_last_redirection = NO;
	msh->ctrlc = NO;
	msh->control = NO_START;
	msh->is_first_time = YES;
	check_first_cmd(msh); // 처음에 redirection이 오는 경우 처리
	while (msh->cmds[++i] && (!ft_strcmp(msh->cmds[msh->id], "cat ")
			|| !ft_strcmp(msh->cmds[msh->id], "| cat ")) // "cat"과 "| cat" 다음에 파이프가 오는 경우만 수행
		&& msh->cmds[msh->id + 1] && msh->cmds[msh->id + 1][0] == '|')
	{
		msh->id++;
		msh->parse.pipes--;
		msh->cat_case = YES;
	}
}

void	close_control_flags(t_shell *msh)
{
	if (msh->fdin != STDIN_FILENO)
		close(msh->fdin);
	if (msh->fdout != STDOUT_FILENO)
		close(msh->fdout);
	if (msh->tmp_cmd)
	{
		free(msh->tmp_cmd);
		msh->tmp_cmd = NULL;
	}
	if (msh->cat_case)
	{
		msh->tokens = ft_split2("cat", SPC);
		create_child_process(msh, msh->fdin, msh->fdout);
		free_split(msh->tokens, YES);
	}
	msh->error_flag = NO;
	msh->control = NO_START;
	msh->is_first_time = NO;
	msh->cat_case = NO;
}

void	commands_manager(t_shell *msh, int i)
{
	int	fd[2];

	init_control_flags(msh, -1); // redirection과 pipe의 특별한 경우 처리. 처음 오는 경우, cat
	while (++i < msh->parse.pipes)
	{
		if (pipe(fd) < 0) // 파이프 생성이 실패했으면? (성공하면 0, 실패하면 -1)
			print_error(ERROR_PID, NULL, 127);
		msh->fdout = fd[1]; // 표준 출력을 fd[1](파이프 출력)로 변경하는 것
		command_handler(msh);
		close(msh->fdout);
		if (msh->fdin != 0)
			close(msh->fdin);
		msh->fdin = fd[0];
	}
	command_handler(msh);
	close_control_flags(msh);
}
