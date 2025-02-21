/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:33 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:34 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_current_tokens(t_shell *msh, t_token *token) // 토큰 상태 저장하기
{
	token->new = ft_substr(msh->tmp_cmd, token->start, token->size);
	token->end = ft_strjoin(token->end, token->new);
	token->position = search_position(token->end, SPC, NULL, -1); // 위치 찾기
	msh->token.print = ft_strtrim(&(token->end)[token->position], SPC);
	msh->token.quote = UNLOCK;
	msh->has_flag_n = NO;
	fix_quotes_to_print(msh, msh->token.print, 0, 0); // -n, 따옴표 처리하고 최종 문자열 생성
	if (token->end && token->end[0] != 0)
		msh->tokens = split_tokens(token->end, 0, 0, NULL);
	free_tokens(token);
	free(msh->tmp_cmd);
	msh->tmp_cmd = NULL;
}

void	get_dollar_sign(t_shell *msh, t_token *token)
{
	char	*content;
	char	*key;

	token->new = ft_substr(msh->tmp_cmd, token->start, token->size - 1);
	token->end = ft_strjoin(token->end, token->new);
	free(token->new);
	token->position = search_position(msh->tmp_cmd + \
		token->i + 1, CHARSET, token, -1);
	key = ft_substr(msh->tmp_cmd, token->i + 1, token->position);
	if (msh->tmp_cmd[token->i + 1] != '?'
		&& get_envinroment_content(msh, key, -1))
		content = ft_strdup(get_envinroment_content(msh, key, -1));
	else if (msh->tmp_cmd[token->i + 1] == '?')
		content = ft_itoa(g_exit);
	else
		content = NULL;
	if (content)
		token->end = ft_strjoin(token->end, content);
	free(content);
	token->i += ft_strlen(key) + 1;
	free(key);
	token->size = 1;
	token->start = token->i;
}

void	get_home_sign(t_shell *msh, t_token *token)
{
	token->new = ft_substr(msh->tmp_cmd, token->start, token->size - 1);
	token->end = ft_strjoin(token->end, token->new);
	free(token->new);
	token->end = ft_strjoin(token->end, msh->home);
	token->i++;
	token->size = 1;
	token->start = token->i;
}

void	check_quotes(t_shell *msh, t_token *token)
{
	if (msh->token.quote == UNLOCK && (msh->tmp_cmd[token->i] == QUOTE
			|| msh->tmp_cmd[token->i] == D_QUOTE))
	{
		msh->token.quote = msh->tmp_cmd[token->i];
		token->lock = token->i;
	}
	else
	{
		if (msh->token.quote == msh->tmp_cmd[token->i])
			msh->token.quote = UNLOCK;
		if (msh->tmp_cmd[token->i] == '~' && msh->token.quote == UNLOCK
			&& msh->tmp_cmd[token->i - 1] == ' '
			&& (msh->tmp_cmd[token->i + 1] == ' '
				|| msh->tmp_cmd[token->i + 1] == '\0'
				|| msh->tmp_cmd[token->i + 1] == '/'))
			get_home_sign(msh, token);
		else if (msh->tmp_cmd[token->i] == '$' && msh->tmp_cmd[token->i + 1]
			&& (msh->token.quote == UNLOCK || msh->token.quote == D_QUOTE))
			get_dollar_sign(msh, token);
	}
}

void	get_tokens(t_shell *msh) // 명령어를 토큰으로 분리하는 역할
// 따옴표나 환경변수($VAR) 등을 처리하여 토큰을 생성함.
{
	t_token	*token;

	token = create_token(msh); // 토큰 생성 후 초기화
	token->end = ft_strdup(""); // 빈 문자열 설정
	if (msh->tmp_cmd)
	{
		while ((int)ft_strlen(msh->tmp_cmd) > token->i)
		{
			check_quotes(msh, token);
			if (msh->token.quote == msh->tmp_cmd[token->i] // token에 저장된 따옴표와 현재 문자가 같으면? 따옴표 닫힘
				&& token->lock != token->i) // 이전 위치와 다르면 정상적임 닫힘
				msh->token.quote = UNLOCK;
			if (!token->dollar_remain) // 현재 문자가 $면
			{
				token->i++;
				token->size++;
			}
			token->dollar_remain = 0;
		}
		close_current_tokens(msh, token); // 현재까지 분석한 토큰을 마무리하고 저장
	}
}
