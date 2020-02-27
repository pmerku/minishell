/* ************************************************************************** */
/*                                                                            */
/*   Project: minishell                                   ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include <string.h>
#include <stddef.h>
#include <libft.h>
#include <limits.h>
#include <time.h>
#include <stdio.h>

static void test_strlen(char *str)
{
    size_t a = strlen(str);
    size_t b = ft_strlen(str);

    if (a != b)
    {
        ft_printf("&c&lKO &r%s %lu %lu\n", str, a, b);
    }
}

static void test_strcpy(char *str)
{
    char a[125];
    char b[125];

    bzero(a, 125);
    bzero(b, 125);

    strcpy(a, str);
    ft_strcpy(b, str);

    if (memcmp(a, b, 125) == 0)
    {
//        ft_printf("&a&lOK&r\n");
    }
    else
    {
        if (strcmp(a, b) == 0)
        {
            ft_printf("&e&lOk?? ");
        }
        ft_printf("&c&lKO &r%s %s\n", str, b);
    }
}

int		main(void)
{
    double time_spent = 0.0;
    char	s[50001];
    char	d[50001];
    clock_t	begin = clock();
    bzero(s, 50001);
    bzero(d, 50001);
    for (unsigned int i = 0; i < 50000; i++)
    {
        s[i] = 'a';
        for (int j = 0; j < 5; j++) {
            ft_strcpy(d, s);
        }
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    ft_printf("&b&lTEST &r| strlen\n");
    test_strlen("a");
    test_strlen("ab");
    test_strlen("abc");
    test_strlen("abcd");
    test_strlen("abcde");
    test_strlen("abcdef");
    test_strlen("abcdefg");
    test_strlen("abcdefgh");
    test_strlen("abcdefghi");
    test_strlen("abcdefghij");
    test_strlen("abcdefghijk");
    test_strlen("abcdefghijkl");
    test_strlen("abcdefghijklm");
    test_strlen("abcdefghijklmn");
    test_strlen("abcdefghijklmno");
    test_strlen("abcdefghijklmnop");
    test_strlen("abcdefghijklmnopq");
    test_strlen("abcdefghijklmnopqr");
    test_strlen("abcdefghijklmnopqrs");
    test_strlen("abcdefghijklmnopqrst");
    test_strlen("abcdefghijklmnopqrstu");
    test_strlen("abcdefghijklmnopqrstuv");
    test_strlen("abcdefghijklmnopqrstuvw");
    test_strlen("abcdefghijklmnopqrstuvwx");
    test_strlen("abcdefghijklmnopqrstuvwxy");
    test_strlen("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
    ft_printf("&b&lTEST &r| end strlen\n");

    ft_printf("&b&lTEST &r| strcpy\n");
    test_strcpy("a");
    test_strcpy("ab");
    test_strcpy("abc");
    test_strcpy("abcd");
    test_strcpy("abcde");
    test_strcpy("abcdef");
    test_strcpy("abcdefg");
    test_strcpy("abcdefgh");
    test_strcpy("abcdefghi");
    test_strcpy("abcdefghij");
    test_strcpy("abcdefghijk");
    test_strcpy("abcdefghijkl");
    test_strcpy("abcdefghijklm");
    test_strcpy("abcdefghijklmn");
    test_strcpy("abcdefghijklmno");
    test_strcpy("abcdefghijklmnop");
    test_strcpy("abcdefghijklmnopq");
    test_strcpy("abcdefghijklmnopqr");
    test_strcpy("abcdefghijklmnopqrs");
    test_strcpy("abcdefghijklmnopqrst");
    test_strcpy("abcdefghijklmnopqrstu");
    test_strcpy("abcdefghijklmnopqrstuv");
    test_strcpy("abcdefghijklmnopqrstuvw");
    test_strcpy("abcdefghijklmnopqrstuvwx");
    test_strcpy("abcdefghijklmnopqrstuvwxy");
    test_strcpy("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
    ft_printf("&b&lTEST &r| end strcpy\n");

    return (0);
}

//int main(void)
//{
//    test_strlen("a");
//    test_strlen("ab");
//    test_strlen("abc");
//    test_strlen("abcd");
//    test_strlen("abcde");
//    test_strlen("abcdef");
//    test_strlen("abcdefg");
//    test_strlen("abcdefgh");
//    test_strlen("abcdefghi");
//    test_strlen("abcdefghij");
//    test_strlen("abcdefghijk");
//    test_strlen("abcdefghijkl");
//    test_strlen("abcdefghijklm");
//    test_strlen("abcdefghijklmn");
//    test_strlen("abcdefghijklmno");
//    test_strlen("abcdefghijklmnop");
//    test_strlen("abcdefghijklmnopq");
//    test_strlen("abcdefghijklmnopqr");
//    test_strlen("abcdefghijklmnopqrs");
//    test_strlen("abcdefghijklmnopqrst");
//    test_strlen("abcdefghijklmnopqrstu");
//    test_strlen("abcdefghijklmnopqrstuv");
//    test_strlen("abcdefghijklmnopqrstuvw");
//    test_strlen("abcdefghijklmnopqrstuvwx");
//    test_strlen("abcdefghijklmnopqrstuvwxy");
//    test_strlen("abcdefghijklmnopqrstuvwxyz");
//    return (0);
//}