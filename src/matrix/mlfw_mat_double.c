#include<mlfw_vector.h>
#include<mlfw_operations.h>
#include<mlfw_matrix.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct mlfw_mat_double 
{
double **data;
dimension_t rows;
dimension_t columns;
} mlfw_mat_double;

mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows, dimension_t columns)
{
mlfw_mat_double * matrix=(mlfw_mat_double *)malloc(sizeof(mlfw_mat_double));
if(matrix==NULL) return NULL;
matrix->rows=rows;
matrix->columns=columns;
matrix->data=(double **)malloc(sizeof(double *)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}       
for(index_t i=0;i<rows;i++)
{
matrix->data[i]=(double *)malloc(sizeof(double)*columns);
if(matrix->data[i]==NULL)
{
for(index_t k=0;k<i;k++) free(matrix->data[k]);
free(matrix->data);
free(matrix);
return NULL;
}
}
return matrix;
}

void mlfw_mat_double_destroy(mlfw_mat_double *matrix)
{
if(matrix==NULL) return;
for(index_t i=0;i<matrix->rows;i++) free(matrix->data[i]);
free(matrix->data);
free(matrix);
}

mlfw_mat_double * mlfw_mat_double_from_csv(const char * csv_file_name)
{
char m;
int r,c;
double value;
char double_string[1025];
int index;
FILE *file;
dimension_t rows,columns;
mlfw_mat_double *matrix;
if(csv_file_name==NULL)
{
printf("invalid file name\n");
return NULL;
}
file=fopen(csv_file_name,"r");
if(file==NULL)
{
printf("unable to open file %s",csv_file_name);
return 0;
}
rows=columns=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(rows==0)
{
if(m==',') columns++;
}
if(m=='\n') rows++;
}
columns++;
matrix=mlfw_mat_double_create_new(rows,columns);
rewind(file);

r=0;
c=0;
index=0;
while(1)
{
m=fgetc(file);
if(feof(file)) break;
if(m==',' || m=='\n')
{
double_string[index]='\0';
index=0;
value=strtod(double_string,NULL);
matrix->data[r][c]=value;
c++;
if(c==matrix->columns) 
{
r++;
c=0;
}
}
else
{
double_string[index]=m;
index++;
}
}
fclose(file);
return matrix;
}

double mlfw_mat_double_get(mlfw_mat_double *matrix, index_t row, index_t col)
{
double value=0.0;
if(matrix==NULL) return value;
if(row<0 || row>=matrix->rows) return value;
if(col<0 || col>=matrix->columns) return value;
return matrix->data[row][col];
}

void mlfw_mat_double_set(mlfw_mat_double *matrix, index_t row, index_t col, double value)
{
if(matrix==NULL) return;
if(row<0 || row>=matrix->rows) return;
if(col<0 || col>=matrix->columns) return;
matrix->data[row][col]=value;
}

void mlfw_mat_double_get_dimensions(mlfw_mat_double *matrix, dimension_t *rows, dimension_t *columns)
{
	if(matrix==NULL) return;
	if(rows!=NULL) *rows=matrix->rows;
	if(columns!=NULL) *columns=matrix->columns;
}

void mlfw_mat_double_copy(mlfw_mat_double *target, mlfw_mat_double *source, index_t target_row_index, index_t target_column_index, index_t source_from_row_index, index_t source_from_column_index, index_t source_to_row_index, index_t source_to_column_index)
{
	int r,c;
	int target_r, target_c;

	if(target==NULL || source==NULL) return;
	
	if(target_row_index<0 || target_row_index>=target->rows) return;
	if(target_column_index<0 || target_column_index>=target->columns) return;
	
	if(source_from_row_index<0 || source_from_row_index>=source->rows) return;
	if(source_from_column_index<0 || source_from_column_index>=source->columns) return;

	if(source_to_row_index<0 || source_to_row_index>=source->rows) return;
	if(source_to_column_index<0 || source_to_column_index>=source->columns) return;

	target_r=target_row_index;

	r=source_from_row_index;
	while(r<=source_to_row_index)
	{
		target_c=target_column_index;
		c=source_from_column_index;
		while(c<=source_to_column_index)
		{
			if(target_r<target->rows && target_c<target->columns) mlfw_mat_double_set(target, target_r, target_c, source->data[r][c]);		
			target_c++;
			c++;
		}
		target_r++;
		r++;
	}
	
}

void mlfw_mat_double_fill(mlfw_mat_double *matrix, index_t from_row_index, index_t from_column_index, index_t to_row_index, index_t to_column_index, double value)
{
	int r,c;

	if(matrix==NULL) return;
		
	if(from_row_index<0 || from_row_index>=matrix->rows) return;
	if(from_column_index<0 || from_column_index>=matrix->columns) return;

	if(to_row_index<0 || to_row_index>=matrix->rows) return;
	if(to_column_index<0 || to_column_index>=matrix->columns) return;


	r=from_row_index;
	while(r<=to_row_index)
	{
		c=from_column_index;
		while(c<=to_column_index)
		{
			mlfw_mat_double_set(matrix, r, c, value);		
			c++;
		}
		r++;
	}
	
}

mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix, index_t column_index)
{
	mlfw_column_vec_double *vector;
	if(matrix==NULL) return NULL;
	if(column_index<0 || column_index>=matrix->columns) return NULL;
	vector=mlfw_column_vec_double_create_new(matrix->rows);
	if(vector==NULL) return NULL;
	for(int i=0;i<matrix->rows;i++)
	{
		mlfw_column_vec_double_set(vector, i, matrix->data[i][column_index]);
	}
	return vector;
}

mlfw_mat_double * mlfw_mat_double_shuffle(mlfw_mat_double *matrix, uint8_t shuffle_count)
{
	dimension_t matrix_rows;
	dimension_t matrix_columns;
	dimension_t random_index;
	mlfw_mat_double *shuffled_matrix;

	if(matrix==NULL || shuffle_count<=0) 
	{
		return NULL;	
	}
	
	mlfw_mat_double_get_dimensions(matrix, &matrix_rows, &matrix_columns);

	shuffled_matrix=mlfw_mat_double_create_new(matrix_rows, matrix_columns);
	if(shuffled_matrix==NULL) return NULL;

	mlfw_mat_double_copy(shuffled_matrix, matrix, 0, 0, 0, 0, matrix_rows-1, matrix_columns-1);	

	srand(time(NULL));
			
	for(index_t i=1;i<=shuffle_count;i++) 
	{
		// shuffle logic
		for(index_t u=0;u<=(matrix_rows-3);u++)
		{
			random_index=u+1+(rand()%(matrix_rows-u-1));
			for(index_t c=0;c<matrix_columns;c++)
			{
				double val=shuffled_matrix->data[u][c];
				shuffled_matrix->data[u][c]=shuffled_matrix->data[random_index][c];
				shuffled_matrix->data[random_index][c]=val;
			}
		}

	}
	return shuffled_matrix;
}

void mlfw_mat_double_to_csv(mlfw_mat_double *matrix, char *csv_file_name)
{
	if(matrix==NULL || csv_file_name==NULL) return;
	index_t r,c;
	char separator;

	FILE *file=fopen(csv_file_name, "w");
	if(file==NULL) 
	{
		printf("unable to open file %s\n",csv_file_name);
		return;
	}

	for(r=0;r<matrix->rows;r++)
	{
		for(c=0;c<matrix->columns;c++)
		{
			fprintf(file,"%lf",matrix->data[r][c]);
			if(c==matrix->columns-1) separator='\n';
			else separator=',';
			fputc(separator, file);	
		}
	}
	fclose(file);
}

mlfw_mat_double * mlfw_mat_double_transpose(mlfw_mat_double *matrix)
{
	mlfw_mat_double *transposed_matrix;
	index_t row, col;
	if(matrix==NULL)
	{
		printf("unable to create transpose of the matrix\n");
		return NULL;
	}
	transposed_matrix = mlfw_mat_double_create_new(matrix->columns, matrix->rows);
	if(transposed_matrix == NULL) {
		printf("unable to create transpose of the matrix\n");
		return NULL;
	}
	for(row=0;row<matrix->rows;row++)
	{
		for(col=0;col<matrix->columns;col++)
		{
			transposed_matrix->data[col][row]=matrix->data[row][col];
		}
	}
	return transposed_matrix;
}
