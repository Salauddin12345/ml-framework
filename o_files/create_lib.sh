# remove library and all o files
rm *.o
rm ../lib/libml-framework.a

# creating o files
gcc -c ../src/matrix/*.c -I ../include -Wall
gcc -c ../src/vector/*.c -I ../include -Wall
gcc -c ../src/operations/*.c -I ../include -Wall

#creating library
ar rcs ../lib/libml-framework.a *.o

echo -e "\e[93mLibrary created successfully\e[0m"
