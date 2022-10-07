#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <io.h>
#include <vector>
#include "utility.h"
using namespace std;

const string floderPath = ".\\examples\\in";
vector<string> fileNames;

void getAllFileName(string floderPath, vector<string>& fileNames) {
    //文件句柄  
    intptr_t hFile = 0;
    //文件信息，声明一个存储文件信息的结构体  
    struct _finddata_t fileinfo;
    string p;  //字符串，存放路径
    if ((hFile = _findfirst(p.assign(floderPath).append("\\*").c_str(), &fileinfo)) != -1)//若查找成功，则进入
    {
        do
        {
            //如果是目录,迭代之（即文件夹内还有文件夹）  
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                //文件名不等于"."&&文件名不等于".."
                //.表示当前目录
                //..表示当前目录的父目录
                //判断时，两者都要忽略，不然就无限递归跳不出去了！
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getAllFileName(p.assign(floderPath).append("\\").append(fileinfo.name), fileNames);
            }
            //如果不是,加入列表  
            else
            {
                fileNames.push_back(p.assign(floderPath).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        //_findclose函数结束查找
        _findclose(hFile);
    }
}

string changeSuffix(string filename)
{
    int oldPos = 0;
	while (filename.find("in", oldPos) != -1)
	{
		int start = filename.find("in", oldPos);
		filename.replace(start, 2, "out");
		oldPos = start + 3;
	}
	return filename;
}

void readData(string filename)
{
	printf("%s\n", filename.c_str());

	int i, j, k;
	FILE *file = fopen(filename.c_str(), "r");

	fscanf(file, "%d%d%d%d", &n, &V, &C, &nc);

//~~~~~~
//nc = V;
	for (i = 0; i < nc; i++)
		vc[i] = 0;

	for (i = 0; i < V; i++)
		cap[i] = C;
	cap[V] = 0x3fffffff;

	k = 0;
	for (i = 0; i < nc; i++){
		fscanf(file, "%d", &vc[i]);
		for(j = 0;j < vc[i];j ++){
			company[k ++] = i;
		}
	}
	company[V] = -1;

	for (i = 0; i < n; i++)
		fscanf(file, "%lf%lf", &p[i].x, &p[i].y);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			c[i][j] = dist(p[i], p[j]);
//		c[i][j] = int(dist(p[i], p[j]) + 0.5);
//		c[i][j] = dist(p[i], p[j]) * 50;
	
	for (i = 0; i < n; i++) {
		fscanf(file, "%lf", &d[i]);

		reward[i] = 0;
		for (j = 0; j < n; j++)
			if (c[i][j] * 2 > reward[i]) 
				reward[i] = c[i][j] * 2;
	}
	reward[0] = 0;
		
	fclose(file);
}

void writeData(Solution &s)
{
	int i, j;

	printf("%.8lf %.8lf\n", s.length, s.fairness);
	for (i = 0; i < n; i++)
		printf("%d, ", s.tour[i]);
	printf("\n");
	for (i = 0; i <= V; i++) {
		printf("V%d %d (%.2lf %.2lf %.2lf):", i, company[i], s.r[i].load, s.r[i].length, s.r[i].profit);
		for (j = 0; j <= s.r[i].nv; j++)
			printf(" %d", s.r[i].v[j]);
		printf("\n");
	}
	fflush(stdout);
}

void writeData(FILE *file, Solution &s)
{
	int i, j;
	fprintf(file, "%.8lf %.8lf\n", s.length, s.fairness);
	for (i = 0; i < n; i++)
		fprintf(file, "%d, ", s.tour[i]);
	fprintf(file, "\n");
	for (i = 0; i <= V; i++) {
		fprintf(file, "V%d %d (%.2lf %.2lf %.2lf):", i, company[i], s.r[i].load, s.r[i].length, s.r[i].profit);
		for (j = 0; j <= s.r[i].nv; j++)
			fprintf(file, " %d", s.r[i].v[j]);
		fprintf(file, "\n");
	}
}

#endif
