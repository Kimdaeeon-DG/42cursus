/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:40:31 by daeekim           #+#    #+#             */
/*   Updated: 2025/02/19 16:40:32 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_forbidden(char *s, int n)
{
	int	i;

	i = -1;
	while (s[++i] && i < n)
		if (ft_isset(s[i], CHARSET) || ft_isset(s[i], QUOTE_SET))
			return (YES);
	if (s[0] <= '9' && s[0] >= '0')
		return (YES);
	return (NO);
}

int	first_cmd_valid(t_shell *msh)
{
	if (msh->cmds[0][0] == '>' || msh->cmds[0][0] == '<') // 맨 처음 값이 >, < 면?
	{
		if (have_only_redirections(msh->cmds[0], -1) // redirections만 있는지 확인
			|| (msh->cmds[0][0] == '<' && msh->cmds[0][1] != '<' // "<<" 아님?
			&& !msh->cmds[1])) // 값 없음?
			// 즉 '<' 하나만 있으면?
		{
			print_error(ERROR_REDIR, NULL, 1); 
			return (NO);
		}
	}
	if (msh->parse.q != UNLOCK) // 열린 상태가 아니면?
	{
		print_error(ERROR_QUOTE, NULL, 2);
		return (NO);
	}
	if (msh->unsupport) // 미지원 문자가 사용 중인지 확인 하는 flag가 켜져 있음?
	{
		printf("minishell: no support for operator `%c'\n", msh->unsupport);
		g_exit = 2;
		return (NO);
	}
	return (YES);
}

int	split_input_in_cmds(t_shell *msh, char *s, int i)
{
	if (s[i] == '|' || s[i] == '<' || s[i] == '>') // pip나 redirection이면
	{
		if (s[i] == '|' && msh->parse.q == UNLOCK) // pip고 열린 상태면?
			msh->parse.pipes++; // 파이프 갯수 증가
		if (msh->parse.q == UNLOCK && msh->parse.size > 0 // 열린 상태고 사이즈가 0보다 크고 
			&& ((s[i] == '|' && i > 0) || (s[i] != '|' && i > 1))) // pip는 처음에 오면 안 되니까 i > 0
			// redirection은 앞에 최소 하나가 있어야 하니까 i > 1
		{
			msh->cmds[msh->parse.id++] = ft_substr(s, // pip나 redirection 만나기 전까지의 명령어를 cmd에 담음
					msh->parse.start, msh->parse.size);
			msh->parse.start = i;
			msh->parse.size = 0;
			if (s[i] == '>')
				msh->is_last_redirection = YES;
			else
				msh->is_last_redirection = NO;
			if (s[i] == s[i + 1])
			{
				i++;
				msh->parse.size = 1;
			}
		}
	}
	
	//남은 명렁어 모두 담기
	else if (ft_isset(s[i], N_HANDLE) && !msh->parse.q && !msh->unsupport) 
		msh->unsupport = s[i];
	return (i);
}

void	start_parse_values(t_shell *msh)
{
	msh->parse.id = 0;
	msh->parse.start = 0;
	msh->parse.size = 0;
	msh->parse.pipes = 0;
	msh->parse.q = UNLOCK;
	msh->unsupport = NO;
	msh->is_last_redirection = NO;
}

void	parse_input(t_shell *msh, char *s, int i)
{
	start_parse_values(msh); // 시작하기 위해 기본 값 초기화
	s = ft_strtrim(s, SPC); // 공백 제거
	while (++i < (int)ft_strlen(s))
	{
		// 현재 상태가 따옴표로 감싸져 있지 않고 && s[i]가 쌍따옴표나 따옴표면?
		if (msh->parse.q == UNLOCK && (s[i] == D_QUOTE || s[i] == QUOTE))
			msh->parse.q = s[i]; // 따옴표 flag를 s[i]로 바꿔줌
		else
		{
			if (msh->parse.q == s[i]) // 현재 상태가 감싸진 상태인데 (쌍)따옴표를 만났다?
				msh->parse.q = UNLOCK; // 현재 상태를 풀어진 상태로 변경
			else
				i = split_input_in_cmds(msh, s, i); // cmds에다가 명령어를 넣음
		}
		msh->parse.size++;
	}
	if (ft_strlen(s) > 0)
		msh->cmds[msh->parse.id++] = ft_substr(s, msh->parse.start, i);
	free (s);
	msh->cmds[msh->parse.id] = NULL;
}
