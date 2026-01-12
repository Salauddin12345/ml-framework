#ifndef __MLFW_MAT_STRING__
#define __MLFW_MAT_STRING__

struct mlfw_mat_string;
typedef struct mlfw_mat_string mlfw_mat_string;

mlfw_mat_string* mlfw_mat_string_create_new(dimension_t rows, dimension_t columns);

void mlfw_mat_string_destroy(mlfw_mat_string *matrix);

mlfw_mat_string* mlfw_mat_string_from_csv(const char * csv_file_name);

void mlfw_mat_string_get(mlfw_mat_string *matrix, index_t row, index_t col, char **string);

void mlfw_mat_string_set(mlfw_mat_string *matrix, index_t row, index_t col, char *string);

void mlfw_mat_string_get_dimensions(mlfw_mat_string *matrix, dimension_t *rows, dimension_t *columns);

#endif

