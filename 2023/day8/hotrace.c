#include "../libft/libft.h"

size_t	get_hash(char *keyvalue)
{
	size_t	hash;
	size_t	counter;
	size_t	hash2;
	size_t	hashsize;
    size_t  a;

	if (keyvalue == NULL)
		return (0);
	hashsize = 1000000;
	hash = 0;
	counter = 0;
	hash2 = 0;
	while (keyvalue[counter])
	{
        a = (size_t)keyvalue[counter];
		__asm__ ("movq $31, %%rdx;"
			"mulq %%rdx;"
			"addq %%rbx, %%rax;"
			"divq %%rcx;"
			: "=d" (hash2)
			: "a" (hash), "b" (a), "c" (hashsize)
			:
			);
		hash = hash2;
		counter++;
	}
	return (hash);
}