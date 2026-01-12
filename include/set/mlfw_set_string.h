#ifndef __MLFW_SET_STRING__
#define __MLFW_SET_STRING__

struct mlfw_set_string;
typedef struct mlfw_set_string mlfw_set_string;

mlfw_set_string* mlfw_set_string_create_new();

void mlfw_set_string_destroy(mlfw_set_string *set);

void mlfw_set_string_get(mlfw_set_string *set, index_t i, char **string);

// returns -1 in case of low memory or 0 in case of added or not dded because of duplicate
int mlfw_set_string_add(mlfw_set_string *set, char *string);

dimension_t mlfw_set_string_get_dimension(mlfw_set_string *set);

#endif

