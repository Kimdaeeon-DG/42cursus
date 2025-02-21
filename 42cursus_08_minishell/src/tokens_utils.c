/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:36 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:37 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_position(char *s, char *c, t_token *token, int i)
{
	while (s[++i])
	{
		if (s[i] == '?' && s[i - 1] == '$') // "$?(환경변수)"면?
			return (i + 1);
		if (ft_isset(s[i], c) || s[i] == '=' || s[i] == D_QUOTE
			|| s[i] == QUOTE || (s[i] == '$' && token))
		{
			if (token && (s[i + 1] == '$' || s[i] == '$')) // 환경변수 감지하면
				token->dollar_remain = 1; // flag 설정
			return (i); // 조건을 만족한 위치 반환
		}
	}
	return (i); // 마지막까지 못 찾으면 마지막 위치 반환
}

t_token	*create_token(t_shell *msh) // 
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->end = NULL;
	token->new = NULL;
	token->print = NULL;
	token->quote = '\0';
	token->i = 0;
	token->start = 0;
	token->position = 0;
	token->size = 1;
	token->lock = UNLOCK;
	token->dollar_remain = NO;
	msh->token.quote = UNLOCK;
	return (token);
}

int	quotes_handler(t_shell *msh, char c, char *tmp, int j) // 따옴표를 처리하는 역할
{
	if (msh->token.quote == UNLOCK && (c == D_QUOTE || c == QUOTE))
		msh->token.quote = c;
	else
	{
		if (msh->token.quote == c) // 앞에 따옴표가 나왔는데 한 번 더 똑같은게 나오면
			msh->token.quote = UNLOCK; // 따옴표 닫힌 상태로 변경
		else
		{
			if (c == '\t' && msh->token.quote == UNLOCK) // 따옴표 안에 있지 않은 상태에서 탭 나오면 공백으로 변경
				c = ' ';
			tmp[j] = c;
			j++;
		}
	}
	return (j);
}

int	verify_flag_n(t_shell *msh, char *s, int i)
{
	int	start;

	start = i; // -n이 유효한 flag가 아니면 돌아가기 위해서 설정
	while (s[i] == '-' && s[i + 1] == 'n') // -n 옵션이 있으면
	{
		msh->has_flag_n++; // flag 증가
		i += 2;
		while (s[i] == ' ' || s[i] == '\t' || s[i] == 'n') // 옵션 뒤에 공백이 있는지. -nnnn도 가능
			i++;
		if (s[i - 1] == 'n' && (s[i] != ' ' && s[i] != '\t'
				&& s[i] != 'n' && s[i] != '\0')) // -n 뒤에 이상한거 오면 flag 무효
		{
			if (msh->has_flag_n == 1)
				msh->has_flag_n = 0;
			return (start); // flag 무효화 됐으니 start로 돌아감
		}
	}
	return (i); // 정상이면 i 값 리턴
}

void	fix_quotes_to_print(t_shell *msh, char *s, int i, int j) 
// 명령어 정리, -n flag 확인, 따옴표 제거하여 최종 문자열 생성
{
	char	*tmp;

	tmp = ft_strtrim(s, SPC);
	i = verify_flag_n(msh, s, i); // -n 플래그 유효성 확인
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ' && msh->token.quote == UNLOCK)
		{
			i++;
			continue ;
		}
		j = quotes_handler(msh, s[i], tmp, j); // 따옴표 처리 함수
		i++;
	}
	tmp[j] = '\0';
	free(msh->token.print);
	msh->token.print = tmp;
}
