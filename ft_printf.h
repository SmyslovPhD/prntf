#ifndef FT_PRINTF_H
#define FT_PRINTF_H
# include <stdarg.h>
# include "libft/libft.h"

typedef struct	s_prntf_data
{
	int			width;
	int			prec;
	int			nul_flag;
	int			len;
}				t_ftprintf_data;

int	ft_printf(const char *format, ...);

#endif
