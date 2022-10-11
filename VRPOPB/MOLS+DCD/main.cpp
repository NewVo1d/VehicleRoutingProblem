#include <iostream>
#include "nsga2.h"
using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    getAllFileName(floderPath, fileNames);
    for(string filename : fileNames){
        readData(filename);
        nsga2(changeSuffix(filename));
    }
    return 0;
}