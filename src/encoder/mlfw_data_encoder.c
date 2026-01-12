#include<mlfw_encoder.h>
#include<mlfw_set.h>
#include<mlfw_matrix.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void mlfw_encoder_encode_one_hot(char *source, char *target, int *encode_columns, int size, int header_exists)
{
	mlfw_mat_string *matrix;
	dimension_t matrix_rows, matrix_columns;
	mlfw_set_string **sets;
	dimension_t set_size;
	index_t i,j;
	index_t r,c;
	index_t data_start_row_index;
	char *string;
	char *set_string;
	FILE *target_file;

	if(source==NULL || target==NULL || encode_columns==NULL || size<=0)
	{
		printf("invalide input\n");
		return;
	}
	
	// loading data set
	matrix=mlfw_mat_string_from_csv(source);
	if(matrix==NULL)
	{
		printf("unable to load dataset\n");
		return;
	}
	mlfw_mat_string_get_dimensions(matrix, &matrix_rows, &matrix_columns);

	// encode_columns validation	
	for(i=0;i<size;i++)
	{
		if(encode_columns[i]<0 || encode_columns[i]>=matrix_columns)
		{
			printf("invalid input data for encode_columns\n");
			mlfw_mat_string_destroy(matrix);
			return;
		}
	}	
	
	// initializing sets
	sets=(mlfw_set_string **)malloc(sizeof(mlfw_set_string *)*size);
	if(sets==NULL)
	{
		printf("Low memory\n");
		mlfw_mat_string_destroy(matrix);
		return;
	}
	for(i=0;i<size;i++)
	{
		sets[i]=mlfw_set_string_create_new();	
		if(sets[i]==NULL)
		{
			printf("Low memory\n");
			for(j=0;j<i;j++) mlfw_set_string_destroy(sets[j]);
			free(sets);
			mlfw_mat_string_destroy(matrix);
			return;			
		}
	}
	
	
	if(header_exists) data_start_row_index=1;
	else data_start_row_index=0;
	
	// filling data in sets
	for(r=data_start_row_index;r<matrix_rows;r++)
	{
		for(i=0;i<size;i++)
		{
			c=encode_columns[i];
			mlfw_mat_string_get(matrix, r, c, &string);
			if(string==NULL)
			{
				for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
				free(sets);
				mlfw_mat_string_destroy(matrix);
				return;									
			}
			if(mlfw_set_string_add(sets[i], string)==-1)
			{
				for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
				free(sets);
				mlfw_mat_string_destroy(matrix);
				return;									
			}			
			free(string);
		}
	}
	
	// logic to create targets file starts here	
	target_file=fopen(target, "w");
	if(target_file==NULL)
	{
		printf("unable to open file %s\n", target);
		for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
		free(sets);
		mlfw_mat_string_destroy(matrix);
		return;									
	}
	
	if(header_exists)
	{
		for(c=0;c<matrix_columns;c++)
		{
			mlfw_mat_string_get(matrix, 0, c, &string);
			if(string==NULL)
			{
				for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
				free(sets);
				mlfw_mat_string_destroy(matrix);
				fclose(target_file);
				target_file=fopen(target, "w");
				fclose(target_file);
				return;												
			}
			
			for(i=0;i<size;i++)
			{
				if(encode_columns[i]==c) break;
			}
			
			if(i<size) // this column is found in encode_columns array and it is to be hot coded.
			{
				set_size=mlfw_set_string_get_dimension(sets[i]);
				for(j=0;j<set_size;j++)
				{
					mlfw_set_string_get(sets[i], j, &set_string);
					if(set_string==NULL)
					{
						for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
						free(sets);
						mlfw_mat_string_destroy(matrix);
						fclose(target_file);
						target_file=fopen(target, "w");
						fclose(target_file);				
						free(set_string);
						return;	
					}
					fputs(string, target_file);
					fputc('_', target_file);
					fputs(set_string, target_file);
					if(!(j==set_size-1 && c==matrix_columns-1)) fputc(',', target_file);
					free(set_string);
				}
			}
			else // this column is not be hot coded
			{
				fputs(string, target_file);
				if(c!=matrix_columns-1) fputc(',', target_file);
			}
		}
		fputc('\n', target_file);		
	} // if(header_exists) ends here
	
	// encode data
	for(r=data_start_row_index;r<matrix_rows;r++)
	{
		for(c=0;c<matrix_columns;c++)
		{
			mlfw_mat_string_get(matrix, r, c, &string);
			if(string==NULL)
			{
				for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
				free(sets);
				mlfw_mat_string_destroy(matrix);
				fclose(target_file);
				target_file=fopen(target, "w");
				fclose(target_file);
				return;												
			}
			
			for(i=0;i<size;i++)
			{
				if(encode_columns[i]==c) break;
			}
			
			if(i<size) // this column is found in encode_columns array and it is to be hot coded.
			{
				set_size=mlfw_set_string_get_dimension(sets[i]);
				for(j=0;j<set_size;j++)
				{
					mlfw_set_string_get(sets[i], j, &set_string);
					if(set_string==NULL)
					{
						for(i=0;i<size;i++) mlfw_set_string_destroy(sets[i]);
						free(sets);
						mlfw_mat_string_destroy(matrix);
						fclose(target_file);
						target_file=fopen(target, "w");
						fclose(target_file);				
						free(set_string);
						return;	
					}
					if(strcmp(string, set_string)==0)
					{
						fputc('1', target_file);
					}
					else
					{
						fputc('0', target_file);
					}
					if(!(j==set_size-1 && c==matrix_columns-1)) fputc(',', target_file);
					free(set_string);
				}
			}
			else // this column is not be hot coded
			{
				fputs(string, target_file);
				if(c!=matrix_columns-1) fputc(',', target_file);
			}
		} // column loop ends here
		fputc('\n', target_file);		
	} // row loop ends here						
	fclose(target_file);
}
