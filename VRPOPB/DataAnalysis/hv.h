#ifndef HV_H
#define HV_H

double max(double x, double y) {
	if(x > y) {
		return x;
	}
	return y;
}

double min(double x, double y) {
	if(x > y) {
		return y;
	}
	return x;
}

double intersectionArea(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    
    double n1,m1;
	double n2,m2;
    
    n1 = max(min(x1,x2),min(x3,x4));
	m1 = max(min(y1,y2),min(y3,y4));
	n2 = min(max(x1,x2),max(x3,x4));
	m2 = min(max(y1,y2),max(y3,y4));
	
    if(n2 > n1 && m2 > m1){
		return (n2 - n1) * (m2 - m1);
	}else{
		return 0.0;
	}
}

void hv(string filename) {
	
}

#endif