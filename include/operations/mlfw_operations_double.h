#ifndef __MLFW_OPERATIONS_DOUBLE__
#define __MLFW_OPEARTIONS_DOUBLE_

mlfw_column_vec_double * mlfw_multiply_double_row_vector_with_column_vector(mlfw_row_vec_double *left_vector, mlfw_column_vec_double *right_vector);

mlfw_column_vec_double * mlfw_multiply_double_matrix_with_column_vector(mlfw_mat_double *left_matrix, mlfw_column_vec_double *right_vector);

mlfw_column_vec_double * mlfw_subtract_double_column_vector(mlfw_column_vec_double *left_vector, mlfw_column_vec_double *right_vector);

mlfw_column_vec_double * mlfw_multiply_double_scalar_with_column_vector(double scalar_value, mlfw_column_vec_double *vector);

#endif
