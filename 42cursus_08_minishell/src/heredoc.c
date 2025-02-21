/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:25 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:26 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_expand(char *line, int i)
{
	while (line[++i])
		if (line[i] == '$' && line[i + 1] != '\0')
			return (YES);
	return (NO);
}

int	search_variable_end(char *s, char *c, int i) //유효한 종료 문자를 찾음
{
	while (s[++i])
	{
		if (s[i] == '?' && s[i - 1] == '$') // $?(이전 명령어의 종료 상태값)을 만나면 종료
			return (i + 1);
		if (ft_isset(s[i], c) || ft_isset(s[i], QUOTE_SET) || s[i] == '$')
		// 변수 끝을 나타내는 문자 찾으면 종료
			return (i);
	}
	return (i);
}

void	get_expand_variable(char *line, t_shell *msh, t_token *exp) // 환경 변수를 확장하는 역할
{
	char	*key;
	char	*content;

	exp->position = search_variable_end(line + exp->i + 1, CHARSET, -1); // 변수의 끝위치 찾음
	key = ft_substr(line, exp->i + 1, exp->position); // ex) $VAR에서 VAR부분만 추출
	exp->new = ft_substr(line, exp->start, exp->i - exp->start); // &VAR에서 VAR 부분만 잘라서 저장
	exp->end = ft_strjoin(exp->end, exp->new); // 변수 앞부분을 끝 부분에 추가
	if (line[exp->i + 1] != '?' && get_envinroment_content(msh, key, -1))
		content = ft_strdup(get_envinroment_content(msh, key, -1));
	else if (line[exp->i + 1] == '?') // "$?"라면? -> 이전 명령어의 종료 상태값 반환
		content = ft_itoa(g_exit);
	else
		content = NULL;
	if (content)
		exp->end = ft_strjoin(exp->end, content); // 환경 변수 값을 기존 문자열에 추가
	exp->i += exp->position;
	exp->start = exp->i + 1;
	free(exp->new);
	free(content);
	free(key);
}

char	*expand_line(char *line, t_shell *msh, t_token *exp, char *tail) // 환경 변수를 확장하는 역할
// ex) echo $HOME 실행하면 $HOME을 실제 경로(/home/user)로 바꾸는 기능 수행
{
	exp = create_token(msh); // 환경 변수 확장을 추적하기 위해 토근 생성 후 초기화
	exp->end = ft_strdup("");
	while (line[exp->i])
	{
		if (line[exp->i] == '$' && line[exp->i + 1] != '\0')
			get_expand_variable(line, msh, exp); // 환경 변수 확장
		exp->i++;
	}
	tail = ft_substr(line, exp->start, exp->i - exp->start);
	exp->end = ft_strjoin(exp->end, tail);
	free(tail);
	free(line);
	line = ft_strdup(exp->end);
	free(exp->end);
	free(exp);
	return (line);
}

void	start_heredoc(char *end, t_shell *msh)
{
	char	*line;
	int		fd;

	line = ft_strdup("");
	fd = open(end, O_WRONLY | O_CREAT | O_TRUNC, 0777); // 오픈함
	while ((ft_strncmp(line, end, ft_strlen(end)) 
			|| ft_strlen(line) != ft_strlen(end))) // 사용자의 입력이 종료 문자열과 일치하지 않으면 계속함
	{
		free(line);
		line = readline("> "); // '>' 표시 후 입력 대기
		if (!line) // ctrl+d(EOF) 감지
		{
			printf("bash: warning: here-document at line");
			printf(" delimited by end-of-file (wanted `%s')\n", end);
			break ;
		}
		if (ft_strcmp(line, end)) // 입력이 end와 같다면
		{
			if (has_expand(line, -1))
				line = expand_line(line, msh, NULL, NULL); // 환경 변수 확장
			ft_putendl_fd(line, fd);
		}
	}
	close(fd);
	free(line);
}
