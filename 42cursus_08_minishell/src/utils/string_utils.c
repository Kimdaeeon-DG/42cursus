#include "../../includes/minishell.h"

char *ft_strdup(const char *s)
{
    char *dup;
    size_t len;
    size_t i;

    len = strlen(s);
    dup = (char *)malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *result;
    size_t i;
    size_t j;

    if (!s1 || !s2)
        return (NULL);
    
    result = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
    if (!result)
        return (NULL);
    
    i = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    
    j = 0;
    while (s2[j])
    {
        result[i + j] = s2[j];
        j++;
    }
    result[i + j] = '\0';
    return (result);
}
