/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:40:17 by daeekim           #+#    #+#             */
/*   Updated: 2025/02/19 16:40:19 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_only_redirections(char *s, int i)
{
	while (s[++i])
		if (s[i] != '>' && s[i] != '<')
			if (s[i] != ' ' && s[i] != '\t')
				return (NO);
	return (YES);
}

int	have_only_spaces(char *s, int i)
{
	while (s[++i])
		if (s[i] != ' ' && s[i] != '\t')
			return (NO);
	return (YES);
}

int	redirections_are_valid(t_shell *msh, int i)
{
	while (msh->cmds[++i])
	{
		if (have_only_redirections(msh->cmds[i], -1)) // redirections만 있음?
		{
			print_error(NULL, msh->cmds[i], 1);
			return (NO);
		}
	}
	return (YES);
}

int	is_valid_input(char *s, int end)
{
	s = ft_strtrim(s, SPC);
	if (!s[0] || s[0] == '|')
	{
		if (s[0] == '|')
			print_error(ERROR_PIPE, NULL, 1);
		free(s);
		return (NO);
	}
	end = ft_strlen(s) - 1;
	if (s[end] == '|' || s[end] == '>' || s[end] == '<')
	{
		if (s[end] == '|')
			print_error(ERROR_PROMPT, NULL, 2);
		else if (s[end] == '>' || s[end] == '<')
			print_error(ERROR_REDIR, NULL, 2);
		free(s);
		return (NO);
	}
	free(s);
	return (YES);
}

void	get_user_input(t_shell *msh, char *prompt)
{
	prompt = getcwd(prompt, 2000); // 버퍼 2000만큼 현재 작업 디렉터리를 가져와 prompt에 저장
	prompt = ft_strjoin(prompt, ":$ "); // 출력 부분처럼 만들어주기
	set_signal(STOP_RESTORE, NULL);
	msh->user_input = readline(prompt); // 사용자로부터 입력을 받아 user-input에 저장
	if (msh->user_input && !have_only_spaces(msh->user_input, -1))
		add_history(msh->user_input); // 사용자가 저장한 것을 히스토리에 저장함. 방향키로 전 명렁어 가져오는 느낌
	free(prompt);
}
