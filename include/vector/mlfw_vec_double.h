#ifndef __MLFW_VEC_DOUBLE__
#define __MLFW_VEC_DOUBLE__

struct __mlfw_column_vec_double;
typedef struct __mlfw_column_vec_double mlfw_column_vec_double;

struct __mlfw_row_vec_double;
typedef struct __mlfw_row_vec_double mlfw_row_vec_double;

// column vector
mlfw_column_vec_double * mlfw_column_vec_double_create_new(dimension_t size);

mlfw_column_vec_double * mlfw_column_vec_double_create_new_filled(dimension_t size, double value);

void mlfw_column_vec_double_destroy(mlfw_column_vec_double *vector);

double mlfw_column_vec_double_get(mlfw_column_vec_double *vector, index_t index);

void mlfw_column_vec_double_set(mlfw_column_vec_double *vector, index_t index, double value);

dimension_t mlfw_column_vec_double_get_size(mlfw_column_vec_double *vector);

mlfw_row_vec_double * mlfw_column_vec_double_transpose(const mlfw_column_vec_double *vector);

// row vector
mlfw_row_vec_double * mlfw_row_vec_double_create_new(dimension_t size);

mlfw_row_vec_double * mlfw_row_vec_double_create_new_filled(dimension_t size, double value);

void mlfw_row_vec_double_destroy(mlfw_row_vec_double *vector);

double mlfw_row_vec_double_get(mlfw_row_vec_double *vector, index_t index);

void mlfw_row_vec_double_set(mlfw_row_vec_double *vector, index_t index, double value);

dimension_t mlfw_row_vec_double_get_size(mlfw_row_vec_double *vector);

mlfw_column_vec_double * mlfw_row_vec_double_transpose(const mlfw_row_vec_double *vector);

#endif
