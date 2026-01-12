#include<mlfw_matrix.h>
#include<mlfw_scale.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

mlfw_mat_double * mlfw_scale_double_min_max(mlfw_mat_double *matrix, index_t start_row_index, index_t start_column_index, index_t end_row_index, index_t end_column_index, char *min_max_file)
{
	mlfw_mat_double *new_matrix;
	dimension_t matrix_rows, matrix_columns;
	dimension_t new_matrix_rows, new_matrix_columns;
	double *min, *max;
	double min_value,max_value;
	double value;
	double scaled_value;
	index_t r,c,i,j;
	FILE *file;
	
	// validations
	if(matrix==NULL) return NULL;
	mlfw_mat_double_get_dimensions(matrix, &matrix_rows, &matrix_columns);
	if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
	if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
	if(start_row_index>end_row_index) return NULL;
	if(start_column_index>end_column_index) return NULL;
	
	// creating new matrix
	new_matrix_rows=(end_row_index-start_row_index)+1;
	new_matrix_columns=(end_column_index-start_column_index)+1;
	new_matrix=mlfw_mat_double_create_new(new_matrix_rows, new_matrix_columns);
	if(new_matrix==NULL) return NULL;
	
	// create min, max row vectors
	min=(double *)malloc(sizeof(double)*new_matrix_columns);
	if(min==NULL)
	{
		mlfw_mat_double_destroy(new_matrix);
		return NULL;
	}
	max=(double *)malloc(sizeof(double)*new_matrix_columns);
	if(max==NULL)
	{
		mlfw_mat_double_destroy(new_matrix);
		free(min);
		return NULL;
	}
	
	// populate min, max row vectors
	i=0;
	for(c=start_column_index;c<=end_column_index;c++)
	{
		min[i]=mlfw_mat_double_get_minimum(matrix, start_row_index, c, end_row_index, c);
		max[i]=mlfw_mat_double_get_maximum(matrix, start_row_index, c, end_row_index, c);
		i++;
	}	
	
	// normalize using min/max and fill in new matrix
	i=0;
	for(r=start_row_index;r<=end_row_index;r++)
	{
		j=0;
		for(c=start_column_index;c<=end_column_index;c++)
		{
			min_value=min[j];
			max_value=max[j];
			value=mlfw_mat_double_get(matrix, r, c);
			scaled_value=(value-min_value)/(max_value-min_value);
			mlfw_mat_double_set(new_matrix, i, j, scaled_value);
			j++;	
		}
		i++;
	}
	
	file=fopen(min_max_file,"w");
	if(file==NULL)
	{
		mlfw_mat_double_destroy(new_matrix);
		free(min);
		free(max);
		return NULL;	
	}
	
	for(i=0;i<new_matrix_columns;i++)
	{
		fprintf(file,"%lf",min[i]);
		if(i==new_matrix_columns-1) fputc('\n',file);
		else fputc(',',file);
	}
	
	for(i=0;i<new_matrix_columns;i++)
	{
		fprintf(file,"%lf",max[i]);
		if(i==new_matrix_columns-1) fputc('\n',file);
		else fputc(',',file);
	}

	free(min);
	free(max);
	fclose(file);
	return new_matrix;
}

mlfw_mat_double * mlfw_scale_double_with_given_min_max(mlfw_mat_double *matrix, index_t start_row_index, index_t start_column_index, index_t end_row_index, index_t end_column_index, mlfw_mat_double *min_max_matrix)
{
	mlfw_mat_double *new_matrix;
	dimension_t matrix_rows, matrix_columns;
	dimension_t new_matrix_rows, new_matrix_columns;
	dimension_t min_max_matrix_rows, min_max_matrix_columns; 
	double min_value,max_value;
	double value;
	double scaled_value;
	index_t r,c,i,j;
	
	// validations
	if(matrix==NULL || min_max_matrix==NULL) return NULL;
	mlfw_mat_double_get_dimensions(matrix, &matrix_rows, &matrix_columns);
	if(start_row_index<0 || end_row_index>=matrix_rows) return NULL;
	if(start_column_index<0 || end_column_index>=matrix_columns) return NULL;
	if(start_row_index>end_row_index) return NULL;
	if(start_column_index>end_column_index) return NULL;
			
	// creating new matrix
	new_matrix_rows=(end_row_index-start_row_index)+1;
	new_matrix_columns=(end_column_index-start_column_index)+1;
	new_matrix=mlfw_mat_double_create_new(new_matrix_rows, new_matrix_columns);
	if(new_matrix==NULL) return NULL;
	
	mlfw_mat_double_get_dimensions(min_max_matrix, &min_max_matrix_rows, &min_max_matrix_columns);	
	if(min_max_matrix_rows!=2 || min_max_matrix_columns!=new_matrix_columns)
	{
		mlfw_mat_double_destroy(new_matrix);
		return NULL;
	}
	
		
	// normalize using min/max and fill in new matrix
	i=0;
	for(r=start_row_index;r<=end_row_index;r++)
	{
		j=0;
		for(c=start_column_index;c<=end_column_index;c++)
		{
			min_value=mlfw_mat_double_get(min_max_matrix, 0, j);
			max_value=mlfw_mat_double_get(min_max_matrix, 1, j);
			value=mlfw_mat_double_get(matrix, r, c);
			scaled_value=(value-min_value)/(max_value-min_value);
			mlfw_mat_double_set(new_matrix, i, j, scaled_value);
			j++;	
		}
		i++;
	}
	
	return new_matrix;
}


