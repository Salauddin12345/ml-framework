#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>

char *DATASET_FILE_NAME=NULL;
char *RESULTS_FILE_NAME=NULL;

void test_it()
{
FILE *results_file;

mlfw_mat_double *dataset;

mlfw_mat_double *I;

mlfw_column_vec_double *m;

mlfw_column_vec_double *P;

index_t i,j;

dimension_t  dataset_rows, dataset_columns;
dimension_t I_rows, I_columns;

dataset=mlfw_mat_double_from_csv(DATASET_FILE_NAME);
if(dataset==NULL) 
{
	printf("Unable to load dataset\n");
	return;
}
mlfw_mat_double_get_dimensions(dataset, &dataset_rows, &dataset_columns);

I_rows=dataset_rows;
I_columns=dataset_columns-1+1;
I=mlfw_mat_double_create_new(I_rows, I_columns);
if(I==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	return;
}

mlfw_mat_double_copy(I, dataset, 0, 1, 0, 0, dataset_rows-1, 0);
mlfw_mat_double_fill(I, 0, 0, I_rows-1, 0, 1);

m=mlfw_column_vec_double_create_new_filled(I_columns,0);
if(m==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_mat_double_destroy(I);
	return;
}

mlfw_column_vec_double_set(m, 0, -32.912388);  // setting c at m[0]
mlfw_column_vec_double_set(m, 1, 1.182613); // setting m at m[1] 

P=mlfw_multiply_double_matrix_with_column_vector(I, m);
if(P==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_mat_double_destroy(I);
	mlfw_column_vec_double_destroy(m);
	return;
}

// store dataset & predicted values in results file
results_file=fopen(RESULTS_FILE_NAME, "w");
fprintf(results_file, "Input(1) | actual output | predicted output\n");

for(i=0;i<dataset_rows;i++)
{
	for(j=0;j<dataset_columns;j++)
	{
		fprintf(results_file, "%lf,", mlfw_mat_double_get(dataset, i, j));
	}
	fprintf(results_file,"%lf\n", mlfw_column_vec_double_get(P, i));
}

fclose(results_file);

// releasing memory
mlfw_mat_double_destroy(dataset);
mlfw_mat_double_destroy(I);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
}

int main(int argc, char *argv[])
{
if(argc!=3)
{
printf("[ Usage: test_it.out dataset_file_name resultS_file_name) ]\n");
return 0;
}
DATASET_FILE_NAME=argv[1];
RESULTS_FILE_NAME=argv[2];

printf("DATASET_FILE_NAME = %s\n", DATASET_FILE_NAME ? DATASET_FILE_NAME : "NULL");
printf("RESULTS_FILE_NAME = %s\n", RESULTS_FILE_NAME ? RESULTS_FILE_NAME : "NULL");

test_it();

return 0;
}
