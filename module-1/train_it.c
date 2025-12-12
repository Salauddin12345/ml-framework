#include<stdio.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>

uint64_t NUMBER_OF_ITERATIONS=2000000;

int main()
{
uint64_t k; // for looping

mlfw_mat_double *dataset;

mlfw_mat_double *I;

mlfw_column_vec_double *A;

mlfw_column_vec_double *m;

mlfw_column_vec_double *P;

mlfw_column_vec_double *E; 

mlfw_row_vec_double *ET;

mlfw_column_vec_double *ETE;

mlfw_mat_double *IT;

mlfw_column_vec_double *ITE;

mlfw_column_vec_double *TMP;

mlfw_column_vec_double *UM;

double sum_of_squared_error_values;
double final_error_value;

dimension_t  dataset_rows, dataset_columns;
dimension_t I_rows, I_columns;

dataset=mlfw_mat_double_from_csv("train_data.csv");
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

mlfw_mat_double_copy(I, dataset, 0, 1, 0, 0, dataset_rows-1, 0);
mlfw_mat_double_fill(I, 0, 0, I_rows-1, 0, 1);

IT=mlfw_mat_double_transpose(I);
if(IT==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	return 0;
	
}

m=mlfw_column_vec_double_create_new_filled(I_columns,0);
if(m==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
	mlfw_column_vec_double_destroy(m);
	return 0;
}

// Operation start
k=1;
while(k<=NUMBER_OF_ITERATIONS)
{
P=mlfw_multiply_double_matrix_with_column_vector(I, m);
if(P==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
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
	mlfw_mat_double_destroy(IT);
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
	mlfw_mat_double_destroy(IT);
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
	mlfw_mat_double_destroy(IT);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(E);
	mlfw_row_vec_double_destroy(ET);
	mlfw_column_vec_double_destroy(ETE);
	return 0;
}

sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/(2*I_rows);

printf("Iteration Number %" PRIu64 ", Error : %41.15lf\n", k, final_error_value);

ITE=mlfw_multiply_double_matrix_with_column_vector(IT,E);
if(ITE==NULL) 
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(E);
	mlfw_row_vec_double_destroy(ET);
	mlfw_column_vec_double_destroy(ETE);
	return 0;
}

TMP=mlfw_multiply_double_scalar_with_column_vector((0.0001*(1.0/I_rows)), ITE);
if(TMP==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(E);
	mlfw_row_vec_double_destroy(ET);
	mlfw_column_vec_double_destroy(ETE);
	mlfw_column_vec_double_destroy(ITE);
	return 0;
}


UM=mlfw_subtract_double_column_vector(m, TMP);
if(UM==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
	mlfw_column_vec_double_destroy(m);
	mlfw_column_vec_double_destroy(P);
	mlfw_column_vec_double_destroy(E);
	mlfw_row_vec_double_destroy(ET);
	mlfw_column_vec_double_destroy(ETE);
	mlfw_column_vec_double_destroy(ITE);
	mlfw_column_vec_double_destroy(TMP);
	return 0;
}


mlfw_column_vec_double_destroy(m); // releasing old m vector
m=UM; // now m is pointing to newly created vector with updated values


mlfw_column_vec_double_destroy(P);
mlfw_column_vec_double_destroy(E);
mlfw_row_vec_double_destroy(ET);
mlfw_column_vec_double_destroy(ETE);
mlfw_column_vec_double_destroy(ITE);
mlfw_column_vec_double_destroy(TMP);

k++;
} // loops ends here

// code to store the content of (m vector) to csv file.

// releasing memory
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);

return 0;
}
