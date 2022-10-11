#include <iostream>

#include "hv.h"
#include "igd.h"
#include "file.h"
using namespace std;

void process(string filename) {
    readData(filename);
    igd(filename);
}

int main()
{
    process("E-n23-k3.out");
    process("E-n33-k4.out");
    process("E-n51-k5.out");
    process("E-n76-k7.out");
    process("E-n76-k14.out");
    process("E-n101-k8.out");
    process("E-n101-k14.out");
	return 0;
}

