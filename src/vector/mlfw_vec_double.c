#include<stdio.h>
#include<stdlib.h>
#include<mlfw_vector.h>
typedef struct __mlfw_column_vec_double
{
double *data;
dimension_t size;
} mlfw_column_vec_double;

typedef struct __mlfw_row_vec_double
{
double *data;
dimension_t size;
} mlfw_row_vec_double;

// column vector
mlfw_column_vec_double * mlfw_column_vec_double_create_new(dimension_t size)
{
	mlfw_column_vec_double *vector;
       	if(size<=0) return NULL;	
	vector=(mlfw_column_vec_double *)malloc(sizeof(mlfw_column_vec_double));
	if(vector==NULL) return NULL;
	vector->data=(double *)malloc(sizeof(double)*size);
	if(vector->data==NULL)
	{
		free(vector);
		return NULL;
	}
	vector->size=size;
	return vector;
}

mlfw_column_vec_double * mlfw_column_vec_double_create_new_filled(dimension_t size, double value)
{
	mlfw_column_vec_double *vector;
	if(size<=0) return NULL;
	vector=(mlfw_column_vec_double *)malloc(sizeof(mlfw_column_vec_double));
	if(vector==NULL) return NULL;
	vector->data=(double *)malloc(sizeof(double)*size);
	if(vector->data==NULL)
	{
		free(vector);
		return NULL;
	}
	vector->size=size;
	for(int i=0;i<vector->size;i++) vector->data[i]=value;
	return vector;
}

void mlfw_column_vec_double_destroy(mlfw_column_vec_double *vector)
{
	if(vector==NULL) return;
	if(vector->data!=NULL) free(vector->data);
	free(vector);	
}

double mlfw_column_vec_double_get(mlfw_column_vec_double *vector, index_t index)
{
	double value=0.0;
	if(vector==NULL) return value;
	if(index<0 || index>=vector->size) return value;
	value=vector->data[index];
	return value;
}

void mlfw_column_vec_double_set(mlfw_column_vec_double *vector, index_t index, double value)
{
	if(vector==NULL) return;
	if(index<0 || index>=vector->size) return;
	vector->data[index]=value;
}

dimension_t mlfw_column_vec_double_get_size(mlfw_column_vec_double *vector)
{
	if(vector==NULL) return 0;
	return  vector->size;
}

mlfw_row_vec_double * mlfw_column_vec_double_transpose(const mlfw_column_vec_double *vector)
{
	mlfw_row_vec_double *transposed_vector;
	if(vector==NULL) return NULL;
	transposed_vector=mlfw_row_vec_double_create_new(vector->size);
	if(transposed_vector==NULL) return NULL;
	for(int i=0;i<vector->size;i++)
	{
		mlfw_row_vec_double_set(transposed_vector, i, vector->data[i]);
	}
	return transposed_vector;
}

// row vector
mlfw_row_vec_double * mlfw_row_vec_double_create_new(dimension_t size)
{
	mlfw_row_vec_double *vector;
	if(size<=0) return NULL;
	vector=(mlfw_row_vec_double *)malloc(sizeof(mlfw_row_vec_double));
	if(vector==NULL) return NULL;
	vector->data=(double *)malloc(sizeof(double)*size);
	if(vector->data==NULL)
	{
		free(vector);
		return NULL;
	}
	vector->size=size;
	return vector;
}

mlfw_row_vec_double * mlfw_row_vec_double_create_new_filled(dimension_t size, double value)
{
	mlfw_row_vec_double *vector;
	if(size<=0) return NULL;
	vector=(mlfw_row_vec_double *)malloc(sizeof(mlfw_row_vec_double));
	if(vector==NULL) return NULL;
	vector->data=(double *)malloc(sizeof(double)*size);
	if(vector->data==NULL)
	{
		free(vector);
		return NULL;
	}
	vector->size=size;
	for(int i=0;i<vector->size;i++) vector->data[i]=value;
	return vector;
}

void mlfw_row_vec_double_destroy(mlfw_row_vec_double *vector)
{
	if(vector==NULL) return;
	if(vector->data!=NULL) free(vector->data);
	free(vector);	
}

double mlfw_row_vec_double_get(mlfw_row_vec_double *vector, index_t index)
{
	double value=0.0;
	if(vector==NULL) return value;
	if(index<0 || index>=vector->size) return value;
	value=vector->data[index];
	return value;
}

void mlfw_row_vec_double_set(mlfw_row_vec_double *vector, index_t index, double value)
{
	if(vector==NULL) return;
	if(index<0 || index>=vector->size) return;
	vector->data[index]=value;
}

dimension_t mlfw_row_vec_double_get_size(mlfw_row_vec_double *vector)
{
	if(vector==NULL) return 0;
	return vector->size;
}

mlfw_column_vec_double * mlfw_row_vec_double_transpose(const mlfw_row_vec_double *vector)
{
	mlfw_column_vec_double *transposed_vector;
	if(vector==NULL) return NULL;
	transposed_vector=mlfw_column_vec_double_create_new(vector->size);
	if(transposed_vector==NULL) return NULL;
	for(int i=0;i<vector->size;i++)
	{
		mlfw_column_vec_double_set(transposed_vector, i, vector->data[i]);
	}
	return transposed_vector;
}

