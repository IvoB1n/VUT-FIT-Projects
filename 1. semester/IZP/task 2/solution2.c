/*
 	IZP Projekt c.2
 	Autor: Ivan Bobrov
 	Login: xbobro01 	
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define i0 1e-12
#define ut 0.0258563

// check if the value is positive, negative or zero
int get_sign_value(double func_value) {
	if (func_value < 0) {
		return -1;
	}
	else if (func_value > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

// Up equation
double f(double up, double u0, double r) {
	return i0 * (exp(up/ut) - 1) - (u0 - up)/r;
}

// calculating Ip value
double ip_calculation(double up) {
	return i0 * (exp(up/ut) - 1);
}

// calculating Up value
double diode(double u0, double r, double eps) {
	double min = 0;
	double up;
	double max = u0;

	// if Up is the same as U0 or zero, return it 
	if (get_sign_value(f(min, u0, r)) == 0) {
		return 0;
	}
	else if (get_sign_value(f(max, u0, r)) == 0) {
		return u0;
	}

	// Bisection method
	while(fabs(max - min)  >= eps) {	
		up = (max + min)/2;
		// condition for avoiding infinite cycle
		if (up == max) {
			return up;
		}
		if (get_sign_value(f(min, u0, r)) != get_sign_value(f(up, u0, r))) {
		 	max = up;
		}
		else {
			min = up;
		}
	} 
	return up;
}

int main (int argv, char *argc[]) {
	double up = 0;
	double ip = 0;
	// validation of arguments
	if(argv == 4){ 
		char *endptr1, *endptr2, *endptr3;
		double u0 = strtod(argc[1], &endptr1);
		double r = strtod(argc[2], &endptr2);
		double eps = strtod(argc[3], &endptr3);

		// argument format validation
		if (strcmp(endptr1, "") || strcmp(endptr2, "") || strcmp(endptr3, "")) {
			fprintf(stderr, "%s\n", "error: invalid arguments");
			return 3;
		}
		// argument value validation
		else if (u0 < 0 || r <= 0) {
			fprintf(stderr, "%s\n", "error: invalid arguments");
			return 3;
		}
		else if (u0 == 0) {
			up = 0;
			ip = 0;
			fprintf(stdout, "Up=%g V\nIp=%g A\n", up, ip);
		} 
		else {
			up = diode(u0, r, eps);
			ip = ip_calculation(up);	
			fprintf(stdout, "Up=%g V\nIp=%g A\n", up, ip);
		}
	}
	else {
		fprintf(stderr, "%s\n", "Please, add three arguments");
		return 4;
	}
    return 0;
}
