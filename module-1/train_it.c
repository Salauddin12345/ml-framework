#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
#include<mlfw_matrix.h>
#include<mlfw_vector.h>
#include<mlfw_operations.h>

uint64_t NUMBER_OF_ITERATIONS=-1;
char *DATASET_FILE_NAME=NULL;
double LEARNING_RATE=1.0;
dimension_t HISTORY_SIZE=0;
char *HISTORY_FILE_NAME=NULL;
uint8_t STOP_FLAG=0;

void train_it()
{

FILE *graph_file;

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

mlfw_mat_double *history;
dimension_t history_rows;
dimension_t history_columns;
index_t history_index;
double iteration_number;
index_t i,j;

double sum_of_squared_error_values;
double final_error_value;

dimension_t  dataset_rows, dataset_columns;
dimension_t I_rows, I_columns;

dataset=mlfw_mat_double_from_csv(DATASET_FILE_NAME);
if(dataset==NULL) 
{
	printf("Unable to load dataset\n");
	return;
}
mlfw_mat_double_get_dimensions(dataset, &dataset_rows, &dataset_columns);
A=mlfw_mat_double_create_column_vec(dataset, dataset_columns-1);
if(A==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	return;
}
I_rows=dataset_rows;
I_columns=dataset_columns-1+1;
I=mlfw_mat_double_create_new(I_rows, I_columns);
if(I==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	return;
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
	return;
	
}

m=mlfw_column_vec_double_create_new_filled(I_columns,0);
if(m==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
	return;
}

history_rows=HISTORY_SIZE;
history_columns=I_columns+2; // 1 extra for iteration number | 1 extra for error value at 1 index
history=mlfw_mat_double_create_new_filled(history_rows, history_columns, 0.0);
if(history==NULL)
{
	printf("Low memory\n");
	mlfw_mat_double_destroy(dataset);
	mlfw_column_vec_double_destroy(A);
	mlfw_mat_double_destroy(I);
	mlfw_mat_double_destroy(IT);
	mlfw_column_vec_double_destroy(m);
	return;

}

graph_file=fopen("graph.csv", "w");

history_index=0;
// Operation start
k=1;
while(STOP_FLAG==0)
{
if(k==(NUMBER_OF_ITERATIONS+1)) break;
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
	mlfw_mat_double_destroy(history);
	return;
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
	mlfw_mat_double_destroy(history);
	return;
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
	mlfw_mat_double_destroy(history);
	return;
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
	mlfw_mat_double_destroy(history);
	return;
}

sum_of_squared_error_values=mlfw_column_vec_double_get(ETE,0);
final_error_value=sum_of_squared_error_values/(2*I_rows);

printf("Iteration Number %" PRIu64 ", Error : %41.15lf\n", k, final_error_value);

fprintf(graph_file, "%" PRIu64 ", %lf\n", k, final_error_value);

iteration_number=(double)(k);

// logic to add history
if(history_index==HISTORY_SIZE)
{
	for(i=1;i<HISTORY_SIZE;i++)
	{
		for(j=0;j<history_columns;j++)
		{
			mlfw_mat_double_set(history, i-1, j, mlfw_mat_double_get(history, i, j));
		}
	}
	history_index--;
}
mlfw_mat_double_set(history, history_index, 0, iteration_number);
mlfw_mat_double_set(history, history_index, 1, final_error_value);
j=mlfw_column_vec_double_get_size(m);
for(i=0;i<j;i++)
{
	mlfw_mat_double_set(history, history_index, 2+i, mlfw_column_vec_double_get(m, i));
}
history_index++;

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
	mlfw_mat_double_destroy(history);
	return;
}

TMP=mlfw_multiply_double_scalar_with_column_vector((LEARNING_RATE*(1.0/I_rows)), ITE);
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
	mlfw_mat_double_destroy(history);
	return;
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
	mlfw_mat_double_destroy(history);
	return;
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

fclose(graph_file);

// code to store the content of (m vector) to csv file.

mlfw_mat_double_to_csv(history, HISTORY_FILE_NAME);

// releasing memory
mlfw_mat_double_destroy(dataset);
mlfw_column_vec_double_destroy(A);
mlfw_mat_double_destroy(I);
mlfw_mat_double_destroy(IT);
mlfw_column_vec_double_destroy(m);
mlfw_mat_double_destroy(history);
}

void * thread_function(void *p)
{
	train_it();
	return NULL;
}

int main(int argc, char *argv[])
{
char *ptr;
int result;
pthread_t thread_id;
char m;

if(argc!=5 && argc!=6)
{
printf("[ Usage: train_it.out dataset_file_name learning_rate history_size history_file_name number_of_iterations (optional) ]\n");
return 0;
}
DATASET_FILE_NAME=argv[1];
ptr=NULL;
LEARNING_RATE=strtod(argv[2], &ptr);
ptr=NULL;
HISTORY_SIZE=(dimension_t)strtoull(argv[3], &ptr, 10);
if(HISTORY_SIZE<5)
{
	printf("History size can never be less than 5\n");
	return 0;
}
HISTORY_FILE_NAME=argv[4];
if(argc==6)
{
ptr=NULL;
NUMBER_OF_ITERATIONS=strtoull(argv[5], &ptr, 10);
}

printf("NUMBER_OF_ITERATIONS = %" PRIu64 "\n", NUMBER_OF_ITERATIONS);
printf("DATASET_FILE_NAME = %s\n", DATASET_FILE_NAME ? DATASET_FILE_NAME : "NULL");
printf("LEARNING_RATE = %lf\n", LEARNING_RATE);
printf("HISTORY_SIZE = %" PRIu32 "\n", HISTORY_SIZE);
printf("HISTORY_FILE_NAME = %s\n", HISTORY_FILE_NAME ? HISTORY_FILE_NAME : "NULL");

result=pthread_create(&thread_id, NULL, thread_function, NULL);
if(result!=0)
{
printf("Unable to create thread\n");
return 0;
}

while(1)
{
	m=getchar();
	if(m=='\n')
	{
		STOP_FLAG=1;
		break;
	}
}

pthread_join(thread_id, NULL);
return 0;
}
