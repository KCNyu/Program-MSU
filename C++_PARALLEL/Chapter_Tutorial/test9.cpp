#include "mpi.h"
#include <iostream>
using namespace std;
int main(){
    MPI_Init( nullptr , nullptr);
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return 0;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char name[9] = "temp.txt";
    int sz = 5;
    int order[sz] = {3,2,5,1,4};
    int nums[sz] = {21,32,124,521,7};
    /*
    int* order = new int[sz];
    int* nums = new int[sz];
    for (int i = 0; i < sz; i++) {
	//order[i] = i+1+rank*10;
	order[i] = sz-i;
	nums[i] = 10*i+rank;
    }
    */
    MPI_File f = MPI_FILE_NULL;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
    int type_size;
    MPI_Type_size(MPI_INT, &type_size);
    for (int i = 0; i < sz; i++) {
        int a = MPI_File_write_at(f, (order[i]-1)*4, nums+i, 1, MPI_INT, MPI_STATUSES_IGNORE);
	if(a != MPI_SUCCESS) cout << "failed "<< endl;
	int temp;
	MPI_File_read_at( f , (order[i]-1)*4, &temp , 1, MPI_INT, MPI_STATUSES_IGNORE);
	cout << "temp: " << temp << endl;
    }
    for (int i = 0; i < sz; i++){
    }
    
    return 0;
}