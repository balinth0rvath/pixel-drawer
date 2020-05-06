#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const u_int8_t size = 3;

u_int8_t calc_position(u_int8_t x, u_int8_t y)
{
	return (y-1) * size + x - 1;
}

void init(u_int8_t** cell, u_int8_t** tmp, u_int8_t** vars, u_int8_t* missing_num)
{
	*cell = (u_int8_t*)malloc(size * size * sizeof(u_int8_t));
	*tmp = (u_int8_t*)malloc(size * size * sizeof(u_int8_t));
	
	*(*cell + calc_position(1,1)) = 1;	

	*(*cell + calc_position(1,1)) = 1;	
	*(*cell + calc_position(3,1)) = 2;	
	*(*cell + calc_position(1,2)) = 3;	
	*(*cell + calc_position(2,3)) = 1;	

	*missing_num = 0;
	for(u_int8_t i=0;i < size * size; i++)
		if (!(*(*cell + i)))
			(*missing_num)++;

	printf("missing num: %i\n", *missing_num);
	*vars = (u_int8_t*)malloc(*missing_num * sizeof(u_int8_t));
		
	int j=0;	
	for(u_int8_t i=0;i < size * size; i++)
		if (!(*(*cell + i)))
			*(*vars+(j++))=i;

	for(u_int8_t i=0;i<*missing_num;i++)
		printf("\n position: %i, value: %i", i, *(*vars+i));
}

void fill(u_int8_t** cell, u_int8_t** tmp, u_int8_t** vars, u_int8_t* missing_num)
{
	int run=1;
	printf("\n\n");
	for(u_int8_t i=0; i< size * size;i++)
	{
		printf("cell before %i\n", *(*cell+i));
		if (*(*cell+i)==0) *(*cell+i)=1;
	}
	 	
	for(u_int8_t i=0; i< size * size;i++)
		printf("cell base %i\n", *(*cell+i));

	u_int8_t act = *missing_num;
	while(run)
	{
		memcpy(*tmp, *cell, size * size);
		printf("pos: %i, val: %i \n",i,*(*vars+i-1));
		if (*(*tmp+*(*vars+i-1)) <= size)
			*(*tmp+*(*vars+i-1)) = *(*tmp+*(*vars+i-1))+1;
		else
		{
			*(*tmp+*(*vars+i-1)) = 1;
		}


		run=0;
	}

}
u_int8_t main()
{
	u_int8_t* cell;
	u_int8_t* tmp;
	u_int8_t* vars;
	u_int8_t missing_num;

	init(&cell, &tmp, &vars, &missing_num);
	fill(&cell, &tmp, &vars, &missing_num);
	free(cell);
	free(tmp);
	free(vars);
	return 0;
}
