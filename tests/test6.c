#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

void	print(const char *s)
{
	write(1, s, strlen(s));
}

int		main(void)
{
	char	*addr;
	char	*wtf;

	addr = malloc(16);
	if ((wtf = realloc((void *)addr + 5, 10)) == NULL)
		print("Bonjours\n");
//	show_alloc_mem();
	return (0);
}
