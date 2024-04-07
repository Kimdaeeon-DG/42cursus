/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:28:28 by daeekim           #+#    #+#             */
/*   Updated: 2024/03/31 17:28:30 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>

int main() {
    char c = 'A';
    char *str = "Hello";
    int num = 42;
    unsigned int u_num = 100;
    int hex_num = 255;

    printf("%c\n", c);       // 문자 'A' 출력
    printf("%s\n", str);     // 문자열 "Hello" 출력
    printf("%p\n", &str);    // 포인터 str의 메모리 주소 출력
	printf("%p\n", NULL);    // NULL일 경우 nil 출력
    printf("%d\n", num);     // 정수 42 출력
    printf("%i\n", num);     // 정수 42 출력
    printf("%u\n", u_num);   // 부호 없는 정수 100 출력
    printf("%x\n", hex_num); // 16진수로 255 출력
    printf("%X\n", hex_num); // 16진수로 대문자로 255 출력
    printf("%%\n\n");          // % 출력
    
    ft_printf("%c\n", c);       // 문자 'A' 출력
    ft_printf("%s\n", str);     // 문자열 "Hello" 출력
    ft_printf("%p\n", &str);    // 포인터 str의 메모리 주소 출력
	ft_printf("%p\n", NULL);    // NULL일 경우 nil 출력
    ft_printf("%d\n", num);     // 정수 42 출력
    ft_printf("%i\n", num);     // 정수 42 출력
    ft_printf("%u\n", u_num);   // 부호 없는 정수 100 출력
    ft_printf("%x\n", hex_num); // 16진수로 255 출력
    ft_printf("%X\n", hex_num); // 16진수로 대문자로 255 출력
    ft_printf("%%\n");          // % 출력
    
    return 0;
}
