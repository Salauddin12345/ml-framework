#include<stdio.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>

int main()
{
mlfw_mat_double *dataset;

mlfw_mat_double *I;

mlfw_column_vec_double *A;

mlfw_column_vec_double *m;

mlfw_column_vec_double *P;

mlfw_column_vec_double *E; 

mlfw_row_vec_double *ET;

mlfw_column_vec_double *ETE;

double sum_of_squared_error_values;
double final_error_value;

dimension_t  dataset_rows, dataset_columns;
dimension_t I_rows, I_columns;

dataset=mlfw_mat_double_from_csv("IceCreamSales.csv");
if(dataset==NULL) 
{
	printf("Unable to load dataset\n");
	return 0;
}
mlfw_mat_double_get_dimensions(dataset, &dataset_rows, &dataset_columns);
A=mlfw_mat_double_create_column_vec(dataset, dataset_columns-1);
if(A==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	return 0;
}
I_rows=dataset_rows;
I_columns=dataset_columns-1+1;
I=mlfw_mat_double_create_new(I_rows, I_columns);
if(I==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	return 0;
}

mlfw_mat_double_copy(I, dataset, 0, I_columns-1, 0, dataset_columns-1, dataset_rows-1, dataset_columns);
mlfw_mat_double_fill(I, 0, 0, I_rows-1, 0, 1);

m=mlfw_column_vec_double_create_new_filled(I_columns,0);
if(m==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_column_vec_double_destroy(m);
	return 0;
}

P=mlfw_multiply_double_matrix_with_column_vector(I, m);
if(P==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	return 0;
}

E=mlfw_subtract_double_column_vector(P, A);
if(E==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(E);
	return 0;
}

ET=mlfw_column_vec_double_transpose(E);
if(ET==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(E);
	mlfw_row_vec_double_destroy(ET);
	return 0;
}

ETE=mlfw_multiply_double_row_vector_with_column_vector(ET, E);
if(ETE==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(E);
	mlfw_row_vec_double_destroy(ET);
	mlfw_column_vec_double_destroy(ETE);
	return 0;
}

sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/I_rows;

printf("sum of squared error values: %41.15lf\n", sum_of_squared_error_values);
printf("final error value: %41.15lf\n", final_error_value);

// releasing memory
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_mat_double_destroy(I);
mlfw_column_vec_double_destroy(m);
mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);

return 0;
}
