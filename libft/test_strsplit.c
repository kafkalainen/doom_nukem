#include "libft.h"

int	main(int argc, char **argv)
{
	
	if (argc == 3)
	{
		ft_putendl(ft_strsplit(argv[1], argv[2][0])[0]);
		return (0);
	}
	return (1);
}
