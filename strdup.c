#include "libft.h"

char	*ft_strdup(const char *string)
{
	int		len;
	int		i;
	char	*new_string;

	len = 0;
	while (*(string + len))
		len++;
	new_string = (char *)malloc(sizeof(char) * (len + 1));
	if (new_string == NULL)
		return (NULL);
	i = 0;
	while (string[i])
	{
		new_string[i] = string[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}   
