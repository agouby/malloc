#include <stdlib.h>
#include <malloc.h>

int		main(void)
{
	int		i;
	char	*addr;

	i = 0;
	while (i < 1024)
	{
		addr = malloc(1024);
		addr[0] = 42;
		i++;
	}
	memory_dump();
	return (0);
}
