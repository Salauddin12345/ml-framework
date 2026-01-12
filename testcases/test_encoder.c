#include<mlfw_encoder.h>
#include<stdio.h>

int main()
{
int encode_columns[]={1,4,5};
mlfw_encoder_encode_one_hot("insurance.csv", "insurance_one_hot_encoded.csv", encode_columns, 3,1);
return 0;
}
