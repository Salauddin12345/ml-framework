#include<mlfw_set.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
char *str;
dimension_t size;
mlfw_set_string *set;
set=mlfw_set_string_create_new();
mlfw_set_string_add(set, "one");
mlfw_set_string_add(set, "two");
mlfw_set_string_add(set, "one");
mlfw_set_string_add(set, "two");
mlfw_set_string_add(set, "one");
mlfw_set_string_add(set, "one");
mlfw_set_string_add(set, "three");
size=mlfw_set_string_get_dimension(set);
for(index_t i=0;i<size;i++)
{
mlfw_set_string_get(set,i,&str);
if(str!=NULL)
{
	printf("%s\n",str);
	free(str);
}
}
printf("size of set is %d\n",size);
mlfw_set_string_destroy(set);
return 0;
}
