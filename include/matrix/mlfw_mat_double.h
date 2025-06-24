#ifndef __MLFW_MAT_DOUBLE__
#define __MLFW_MAT_DOUBLE__

struct mlfw_mat_double;
typedef struct mlfw_mat_double mlfw_mat_double;

mlfw_mat_double * mlfw_mat_double_create_new(dimension_t rows, dimension_t columns);

void mlfw_mat_double_destroy(mlfw_mat_double *matrix);

mlfw_mat_double * mlfw_mat_double_from_csv(const char * csv_file_name);

double mlfw_mat_double_get(mlfw_mat_double *matrix, index_t row, index_t col);

void mlfw_mat_double_set(mlfw_mat_double *matrix, index_t row, index_t col, double value);

void mlfw_mat_double_get_dimensions(mlfw_mat_double *matrix, dimension_t *rows, dimension_t *columns);

void mlfw_mat_double_copy(mlfw_mat_double *target, mlfw_mat_double *source, index_t target_row_index, index_t target_column_index, index_t source_from_row_index, index_t source_from_column_index, index_t source_to_row_index, index_t source_to_column_index);

void mlfw_mat_double_fill(mlfw_mat_double *matrix, index_t from_row_index, index_t from_column_index, index_t to_row_index, index_t to_column_index, double value);

mlfw_column_vec_double * mlfw_mat_double_create_column_vec(mlfw_mat_double *matrix, index_t column_index);

mlfw_mat_double * mlfw_mat_double_shuffle(mlfw_mat_double *matrix, uint8_t shuffle_count);
void mlfw_mat_double_to_csv(mlfw_mat_double *matrix, char *csv_file_name);

#endif

