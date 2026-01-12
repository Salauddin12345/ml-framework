#include<mlfw_matrix.h>
#include<stdio.h>

int main()
{
mlfw_mat_string *dataset;
dimension_t dataset_rows, dataset_columns;
char *ptr;
dataset=mlfw_mat_string_from_csv("insurance.csv");
if(dataset==NULL)
{
printf("unable to load dataset\n");
return 0;
}
mlfw_mat_string_get_dimensions(dataset, &dataset_rows, &dataset_columns);
for(index_t i=0;i<dataset_rows;i++)
{
	for(index_t j=0;j<dataset_columns;j++)
	{
		mlfw_mat_string_get(dataset, i, j, &ptr);
		printf("%s  ", ptr);
	}
	printf("\n");
}

return 0;
}
