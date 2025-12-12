#include<stdio.h>
#include<stdlib.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>
mlfw_column_vec_double * mlfw_multiply_double_row_vector_with_column_vector(mlfw_row_vec_double *left_vector, mlfw_column_vec_double *right_vector)
{
	mlfw_column_vec_double *column_vector;
	dimension_t left_vector_size;
	dimension_t right_vector_size;
	double value=0;
	if(left_vector==NULL || right_vector==NULL) return NULL;
	left_vector_size=mlfw_row_vec_double_get_size(left_vector);
	right_vector_size=mlfw_column_vec_double_get_size(right_vector);
	if(left_vector_size!=right_vector_size) return NULL;
	column_vector=mlfw_column_vec_double_create_new(1);
	if(column_vector==NULL) return NULL;

	for(index_t i=0;i<left_vector_size;i++)
	{
		value+=(mlfw_row_vec_double_get(left_vector,i)*mlfw_column_vec_double_get(right_vector,i));
	}
	mlfw_column_vec_double_set(column_vector, 0, value);
	return column_vector;
}

mlfw_column_vec_double * mlfw_multiply_double_matrix_with_column_vector(mlfw_mat_double *left_matrix, mlfw_column_vec_double *right_vector)
{
	mlfw_column_vec_double *column_vector;
	dimension_t left_matrix_rows, left_matrix_columns;
	dimension_t right_vector_size;
	double value, left_value, right_value;
	if(left_matrix==NULL || right_vector==NULL) return NULL;
	mlfw_mat_double_get_dimensions(left_matrix, &left_matrix_rows, &left_matrix_columns);
	right_vector_size=mlfw_column_vec_double_get_size(right_vector);
	if(left_matrix_columns!=right_vector_size) return NULL;
	column_vector=mlfw_column_vec_double_create_new(left_matrix_rows);
	if(column_vector==NULL) return NULL;
	for(index_t i=0;i<left_matrix_rows;i++)
	{
		value=0;
		for(index_t j=0;j<left_matrix_columns;j++)
		{
			left_value=mlfw_mat_double_get(left_matrix, i, j);
			right_value=mlfw_column_vec_double_get(right_vector,j);
			value+=(left_value*right_value);
		}
		mlfw_column_vec_double_set(column_vector, i, value);
	}

	return column_vector;
}

mlfw_column_vec_double * mlfw_subtract_double_column_vector(mlfw_column_vec_double *left_vector, mlfw_column_vec_double *right_vector)
{
	mlfw_column_vec_double *column_vector;
	dimension_t left_vector_size,right_vector_size;
	if(left_vector==NULL || right_vector==NULL) return NULL;
	left_vector_size=mlfw_column_vec_double_get_size(left_vector);
	right_vector_size=mlfw_column_vec_double_get_size(right_vector);
	if(left_vector_size!=right_vector_size) return NULL;
	column_vector=mlfw_column_vec_double_create_new(left_vector_size);
	if(column_vector==NULL) return NULL;
	for(index_t i=0;i<left_vector_size;i++)
	{
		double value=mlfw_column_vec_double_get(left_vector, i)-mlfw_column_vec_double_get(right_vector, i);
		mlfw_column_vec_double_set(column_vector, i, value);		
	}
	return column_vector;
}

mlfw_column_vec_double * mlfw_multiply_double_scalar_with_column_vector(double scalar_value, mlfw_column_vec_double *vector)
{
	mlfw_column_vec_double *product_vector;
	dimension_t vector_size;
	index_t i;
	double val;
	if(vector==NULL) return NULL;
	vector_size=mlfw_column_vec_double_get_size(vector);
	product_vector=mlfw_column_vec_double_create_new(vector_size);
	if(product_vector==NULL) 
	{
		printf("Insufficient memory\n");
		return NULL;
	}
	for(i=0;i<vector_size;i++)
	{
		val=mlfw_column_vec_double_get(vector,i);
		mlfw_column_vec_double_set(product_vector,i, val*scalar_value);
	}
	return product_vector;
}


