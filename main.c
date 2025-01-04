#include "get_next_line.h"

int	main(void)
{
	char	*line;
	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
