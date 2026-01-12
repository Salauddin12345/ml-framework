#include<mlfw_matrix.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct mlfw_mat_string 
{
char ***data;
dimension_t rows;
dimension_t columns;
} mlfw_mat_string;

mlfw_mat_string * mlfw_mat_string_create_new(dimension_t rows, dimension_t columns)
{
mlfw_mat_string * matrix=(mlfw_mat_string *)malloc(sizeof(mlfw_mat_string));
if(matrix==NULL) return NULL;
matrix->rows=rows;
matrix->columns=columns;
matrix->data=(char ***)malloc(sizeof(char **)*rows);
if(matrix->data==NULL)
{
free(matrix);
return NULL;
}       
for(index_t i=0;i<rows;i++)
{
matrix->data[i]=(char **)malloc(sizeof(char *)*columns);
if(matrix->data[i]==NULL)
{
for(index_t k=0;k<i;k++) free(matrix->data[k]);
free(matrix->data);
free(matrix);
return NULL;
}
else
{
for(index_t c=0;c<columns;c++) matrix->data[i][c]=NULL; // imp to set null 
}
}
return matrix;
}


void mlfw_mat_string_destroy(mlfw_mat_string *matrix)
{
if(matrix==NULL) return;
for(index_t i=0;i<matrix->rows;i++) 
{
	for(index_t j=0;j<matrix->columns;j++) 
	{
		if(matrix->data[i][j]!=NULL) free(matrix->data[i][j]);
	}
	free(matrix->data[i]);
}
free(matrix->data);
free(matrix);
}

mlfw_mat_string * mlfw_mat_string_from_csv(const char * csv_file_name)
{
char m;
int r,c;
char string[5000];
int index;
FILE *file;
dimension_t rows,columns;
mlfw_mat_string *matrix;
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
matrix=mlfw_mat_string_create_new(rows,columns);
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
string[index]='\0';
matrix->data[r][c]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[r][c]!=NULL)
{
strcpy(matrix->data[r][c], string);
}
index=0;
c++;
if(c==matrix->columns) 
{
r++;
c=0;
}
}
else
{
string[index]=m;
index++;
}
}
fclose(file);
return matrix;
}

void mlfw_mat_string_get(mlfw_mat_string *matrix, index_t row, index_t col, char **string)
{
if(matrix==NULL || string==NULL)
{
*string=NULL;
return;
}
if(row<0 || row>=matrix->rows)
{
*string=NULL;
return;
}
if(col<0 || col>=matrix->columns)
{
*string=NULL;
return;
}
if(matrix->data[row][col]==NULL)
{
*string=NULL;
return;
}
*string=(char *)malloc(sizeof(char)*(strlen(matrix->data[row][col])+1));
if(*string==NULL) return;
strcpy(*string, matrix->data[row][col]);
}

void mlfw_mat_string_set(mlfw_mat_string *matrix, index_t row, index_t col, char *string)
{
if(matrix==NULL || string==NULL)
{
return;
} 
if(row<0 || row>=matrix->rows) 
{
return;
}
if(col<0 || col>=matrix->columns)
{
return;
}
if(matrix->data[row][col]!=NULL) free(matrix->data[row][col]);
matrix->data[row][col]=(char *)malloc(sizeof(char)*(strlen(string)+1));
if(matrix->data[row][col]!=NULL)
{
strcpy(matrix->data[row][col], string);
}
}

void mlfw_mat_string_get_dimensions(mlfw_mat_string *matrix, dimension_t *rows, dimension_t *columns)
{
	if(matrix==NULL) return;
	if(rows!=NULL) *rows=matrix->rows;
	if(columns!=NULL) *columns=matrix->columns;
}
