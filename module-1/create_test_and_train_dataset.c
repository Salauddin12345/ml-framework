#include<stdio.h>
#include<stdlib.h>
#include<mlfw_matrix.h>


int main(int argc, char *argv[]) 
{
	char *dataset_file;
	char *test_file;
	char *train_file;
	int minor_percentage;
	dimension_t minor_rows;
	dimension_t major_rows;
	dimension_t dataset_rows, dataset_columns;
	mlfw_mat_double *dataset;
	mlfw_mat_double *test_dataset;
	mlfw_mat_double *train_dataset;
	mlfw_mat_double *shuffled_matrix;

	// as arguments (dataset file, test_file, train_file, minor percentage)
	if(argc!=5)
	{
		printf("Usage: [create_test_train_dataset dataset test_file train_file minor_percentage]\n");
		return 0;
	}
	dataset_file=argv[1];
	test_file=argv[2];
	train_file=argv[3];
	minor_percentage=atoi(argv[4]);

	if(minor_percentage<=0 || minor_percentage>=50) 
	{
		printf("Invalid minor percentage\n");
		return 0;
	}
	
	dataset=mlfw_mat_double_from_csv(dataset_file);
	if(dataset==NULL)
	{
		printf("unable to load dataset file %s\n",dataset_file);
		return 0;
	}
	mlfw_mat_double_get_dimensions(dataset, &dataset_rows, &dataset_columns);
	
	shuffled_matrix=mlfw_mat_double_shuffle(dataset, 3);

	if(shuffled_matrix==NULL)
	{
		printf("Shuffling failed\n");
		mlfw_mat_double_destroy(dataset);
		return 0;
	}

	minor_rows=(minor_percentage*dataset_rows)/100;
	major_rows=dataset_rows-minor_rows;

	train_dataset=mlfw_mat_double_create_new(major_rows, dataset_columns);
	if(train_dataset==NULL)
	{
		printf("Unable to create train matrix\n");
		mlfw_mat_double_destroy(dataset);
		return 0;
	}
	test_dataset=mlfw_mat_double_create_new(minor_rows, dataset_columns);
	if(test_dataset==NULL)
	{
		printf("Unable to create test matrix\n");
		mlfw_mat_double_destroy(dataset);
		mlfw_mat_double_destroy(train_dataset);
		return 0;
	}

	mlfw_mat_double_copy(train_dataset, shuffled_matrix, 0, 0, 0, 0, major_rows-1, dataset_columns-1);
	mlfw_mat_double_copy(test_dataset, shuffled_matrix, 0, 0, major_rows, 0, dataset_rows-1, dataset_columns-1);

	mlfw_mat_double_to_csv(train_dataset, train_file);
	mlfw_mat_double_to_csv(test_dataset, test_file);

	mlfw_mat_double_destroy(dataset);
	mlfw_mat_double_destroy(shuffled_matrix);
	mlfw_mat_double_destroy(train_dataset);
	mlfw_mat_double_destroy(test_dataset);
	return 0;
}
