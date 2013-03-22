#include <stdio.h>
#include "vbyte.h"
#include <iostream>
#include <fstream.h>
#include <stdlib.h>

using namespace std;

int main(int args, char** argv){

    unsigned int a = 1624u;

    unsigned char buf[100] = {0};

    int len = writeVbyte(a, buf);

    ofstream file ("data", ios::out | ios::binary);
	file.write((char *)buf,100);
	file.close();

    int i=0;
    while(buf[i] != 0){
        printf("%d\n", buf[i++]);
    }
    printf("len = %d\n", len);

    unsigned int res;
    len = readVbyte(buf, res);
    printf("%u %d\n", res, len);

//    printf("size of char %d\n", sizeof(char));
//    printf("size of int %d\n", sizeof(int));

    return 0;
}
