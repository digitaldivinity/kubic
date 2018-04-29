#include <stdio.h>
#include <SFML/Graphic.hpp>

#define N 4

struct k_point{
	double x,y;
	k_point(){
		x=y=0;
	}
	k_point(const double & x, const double & y){//not enough
		this->x=x;
		this->y=y;
	}
	k_point operator*(double num){
		k_point ob(x*num,y*num);
		return ob;
	}
	k_point operator+(k_point ob){
		k_point r(x+ob.x,y+ob.y);
		return r;
	}
	k_point operator/(k_point ob){
		k_point buf(this->x/ob.x,this->y/ob.y);
		return buf;
	}
	k_point operator/(double ob){
		k_point buf(this->x / ob,this-> / ob);
		return buf;
	}
	k_point operator*(k_point ob){
		k_point buf(this->x * ob.x,this->y * ob.y);
		return buf;
	}
	void out(){
		printf("%lf %lf\n",x,y);
	}
};



//метод прогонки
/*	a[0]=0;
 * b[n-1]=0;
	 * n - число уравнений (строк матрицы)
	 * b - диагональ, лежащая над главной (нумеруется: [0;n-2])
	 * c - главная диагональ матрицы A (нумеруется: [0;n-1])
	 * a - диагональ, лежащая под главной (нумеруется: [1;n-1])
	 * f - правая часть (столбец)
	 * x - решение, массив x будет содержать ответ
	 */
void progonka (int n, double *a, double *c, double *b, k_point *f, k_point *x)
{
	double m;
	for (int i = 1; i < n; i++)
	{
		m = a[i]/c[i-1];
		c[i] = c[i] - b[i-1]*m;
		f[i] = f[i] - f[i-1]*m;
	}

	x[n-1] = f[n-1]/c[n-1];

	for (int i = n - 2; i >= 0; i--)
		x[i]=(f[i]-x[i+1]*b[i])/c[i];
};

void proizv(k_point * p,k_point * d, int n){
	k_point  f[n-1];
	for (int i=1;i<n;i++){
		f[i]=(p[i+1]+p[i-1]-p[i]*2)*6;//f[i]?
	}
	//progonka
	double a[n];
	a[0]=0;
	for (i=1;i<n;i++) a[i]=1;
	double b[n];
	n[n-1]=0;
	for (i=0;i<n-1;i++) b[i]=1;
	double c[n];
	for (i=0;i<n;i++) c[i]=4;
	progonka(n,a,c,b,f,d);
}

void draw_curve(p

int main(){
	return 0;
}
