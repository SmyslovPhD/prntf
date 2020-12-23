/*TODO 42H */

#include "libft.h"

char	*ft_ctos(char c)
{
	char	*s;

	s = (char*)malloc(2 * sizeof(char));
	*s = c;
	s[1] = '\0';
	return (s);
}
