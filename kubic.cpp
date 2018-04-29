#include <stdio.h>
#include <SFML/Graphics.hpp>


#define X 800
#define Y 800
#define BORDER 10
#define STEP 10
#define MAXPOINTS 100

using namespace sf;

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
	k_point operator-(k_point ob){
		k_point buf(x-ob.x,y-ob.y);
		return buf;
	}
	k_point operator/(k_point ob){
		k_point buf(this->x/ob.x,this->y/ob.y);
		return buf;
	}
	k_point operator/(double ob){
		k_point buf(this->x / ob,this-> y / ob);
		return buf;
	}
	k_point operator*(k_point ob){
		k_point buf(this->x * ob.x,this->y * ob.y);
		return buf;
	}
	k_point operator=(k_point ob){
		x=ob.x;
		y=ob.y;
		return (*this);
	}
	k_point operator=(double num){
		x=num;
		y=num;
		return (*this);
	}
	void out(){
		printf("%lf %lf\n",x,y);
	}
	void zero(){
		x=0;
		y=0;
	}
};

class ex{
	int a;
	public:
	ex(int i=0) : a(i) {}
	void out(){
		switch (a){
			
			case 1: printf("one\n"); break;
			case 2: printf("two\n"); break;
			case 3: printf("array overflow error\n"); break;
			case 5: printf("Неполный набор параметров\n"); break;
			default: printf("undef error code %d\n",a); break;
		}
	}
};

double pow(double x,int y){
	int i;
	double buf=x;
	if (y==0) return 0;
	if (y<0) throw 2; //throw
	for (i=0;i<y-1;i++){
		x*=buf;
	}
	return x;
}

//место - номер в массиве, количество - колво значимых элементов массива
void ins_point(k_point * p,k_point & chto, int mesto, int & kolvo){
	if (kolvo==MAXPOINTS) throw ex(40);
	if (mesto > kolvo-1) throw ex(40); //throw
	for (int i=kolvo-1;i>=mesto;i--) p[i+1]=p[i];//сдвиг	
	p[mesto]=chto;
	kolvo++;
}
//количество передается по ссылке, это важно
void del_point(k_point * p, int mesto, int & kolvo){
	if (kolvo<1) return ; //thrwo
	if (mesto>kolvo-1) throw ex(41); //throw
	for (int i=mesto;i<kolvo-1;i++){//сдвиг
		p[i]=p[i+1];
	}
	kolvo--;
}
/* b-главная
 * a-под
 * c-над
 * d-производные
 * right-правая часть
 */
void solve_matrix(int n,k_point * d,k_point * right){
	//крайние случаи
	int i,j;
	if (n==1) {d[0]=right[0]/4; return ;}
	//не крайние
	double m[n][n];//строка, столбец
	
	for (i=0;i<n;i++){
		for (j=0;j<n;j++){
			m[i][j]=0;
		}
		if (i==0) {
			m[0][0]=4;
			m[0][1]=1;
		}
		else if(i==n-1){
			m[i][i-1]=1;
			m[i][i]=4;
		}
		else {
			m[i][i-1]=1;
			m[i][i]=4;
			m[i][i+1]=1;
		}
	}
	for (i=1;i<n;i++){
		double k=m[i][i-1]/m[i-1][i-1];
		m[i][i-1]=0;
		m[i][i]=m[i][i]-m[i-1][i]*k;
		right[i]=right[i]-right[i-1]*k;	
	}
	d[n-1]=right[n-1]/m[n-1][n-1];
	for (i=n-2;i>=0;i--){
		double k=m[i][i+1]/m[i+1][i+1];
		right[i]=right[i]-right[i+1]*k;
		d[i]=right[i]/m[i][i];
	}
}

//зависимости k_point, progonka
void proizv(k_point * p,k_point * d, int n){
	if (n<2) return;
	d[0]=0;
	d[n-1]=0;
	k_point  f[n-2];
	int i;
	for (i=1;i<n-1;i++){
		f[i-1]=(p[i+1]+p[i-1]-p[i]*2)*6;//f[i]?
	}
	solve_matrix(n-2,&d[1],f);
}


double h1(double t){
	return 2*pow(t,3)-3*pow(t,2)+1;
}

double h3(double t){
	return pow(t,3)-2*pow(t,2)+t;
}

double h2(double t){
	return -2*pow(t,3)+3*pow(t,2);
}

double h4(double t){
	return pow(t,3)-pow(t,2);
}

k_point polinom(k_point one,k_point two,k_point done, k_point dtwo, double t){
	return one*h1(t)+two*h2(t)+done*h3(t)+dtwo*h4(t);
}


double abs(double x){
	if (x<0) return -x;
	else if (x==0) return 0;
	else return x;
}

int check_points(k_point * p,int amount, k_point what){
	for (int i=0;i<amount;i++){
		if (abs(p[i].x-what.x)<=8 && abs(p[i].y-what.y)<=8) return i;
	}
	return -1;
}

int check_points(k_point * p,k_point * m, int amount, k_point what){
	for (int i=0;i<amount;i++){
		if (abs(p[i].x+m[i].x-what.x)<=8 && abs(p[i].y+m[i].y-what.y)<=8) return i;
	}
	return -1;
}


void draw_points(k_point * p,int amount,RenderWindow & window,sf::Color clr){
	CircleShape shape(2,100);
	shape.setFillColor(clr);
	for (int i=0;i<amount;i++){
		shape.setPosition(p[i].x-2,p[i].y-2);
		window.draw(shape);
	}
}

void draw_points(k_point * p,k_point *m,int amount,RenderWindow & window,sf::Color clr){
	CircleShape shape(2,100);
	shape.setFillColor(clr);
	for (int i=0;i<amount;i++){
		shape.setPosition(p[i].x+m[i].x-2,p[i].y+m[i].y-2);
		window.draw(shape);
	}
}

void draw_line(k_point p1,k_point p2,RenderWindow & window, sf::Color clr){
	sf::Vertex pts[2];
	pts[0].position = sf::Vector2f(p1.x,p1.y);
	pts[1].position = sf::Vector2f(p2.x,p2.y);
	pts[0].color=clr;
	pts[1].color=clr;
	window.draw(pts, 2, sf::Lines);
}

void draw_curve(k_point * p,k_point * m, int amount, RenderWindow & window,sf::Color clr){
	k_point buf1,buf2=p[0];
	int i;
	for (i=0;i<amount-1;i++)//внешний цикл по парам точек
	{
		for (double t=0;t<=1.01;t+=0.04){
			buf1=polinom(p[i],p[i+1],m[i],m[i+1],t);
			draw_line(buf1,buf2,window,clr);
			buf2=buf1;
		}
	}
	draw_points(p,amount,window,Color::Red);
}

double check_border(double x,double window,double border){
	if (x<border) return border;
	else if (x>window) return window-border;
	else return x;
}

void dnd(k_point * p,k_point *m,int amount, RenderWindow & window,Color curve){
	window.clear(Color::White);
	draw_curve(p,m,amount,window,curve);
	window.display();
}

void dnd(k_point * p,k_point *m,int amount, RenderWindow & window,Color curve,Color line){
	window.clear(Color::White);
	draw_curve(p,m,amount,window,curve);
	for (int i=0;i<amount;i++) draw_line(p[i],p[i]+m[i],window,line);
	draw_points(p,m,amount,window,Color::Green);
	window.display();
}

int main(int argc,char ** argv){
	k_point a[5];
	k_point b[5];
	a[0]=500;
	a[1]=300;
	a[2]=600;
	a[3]=200;
	a[4]=450;
	solve_matrix(5,b,a);
	int k;
	
	for (k=0;k<5;k++) b[k].out();
try{//можно добавить параметры
	k_point p[100];
	k_point m[100];
	int i=0;
	int turn=0;
	int mode=0;
	RenderWindow window(VideoMode(X,Y),"Spline");
	window.clear(Color::White);
	window.display();
	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event)){
			if (event.type == Event::Closed) window.close();//закрытие
			else if (event.type ==sf::Event:: MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !mode){ //кнопка нажата
				turn=0;
				if (i==MAXPOINTS-1) throw ex(3);//throw
				p[i].x=event.mouseButton.x;
				p[i].y=event.mouseButton.y;
				i++;
				proizv(p,m,i);
				dnd(p,m,i,window,Color::Black);
			}
			else if (event.type == Event::MouseButtonPressed && mode){//кнопка нажата, режим редактирвоания
				k_point buf;
				int num;
				buf.x=event.mouseButton.x;
				buf.y=event.mouseButton.y;
				num=check_points(p,i,buf);
				if (-1!=(num=check_points(p,i,buf))){
					//попали в точку кривой
					turn = 0;
					while (!turn){
						Event event0;
						while (window.pollEvent(event0)){
							if (event0.type ==sf::Event::MouseMoved){//мышка переместилась с зажатой кнопкой
								p[num].x=check_border(event0.mouseMove.x,X,BORDER);
								p[num].y=check_border(event0.mouseMove.y,Y,BORDER);
								proizv(p,m,i);
								dnd(p,m,i,window,Color::Black);
							}
							else if (event0.type == sf::Event:: MouseButtonReleased && event0.mouseButton.button == sf::Mouse::Left){//кнопка отжата
								turn=1;
							}
							else if (event0.type == Event::KeyPressed && event0.key.code == Keyboard::A){
								k_point buf;
								ins_point(p,p[num],num,i);
								proizv(p,m,i);
								num++;
								dnd(p,m,i,window,Color::Black);
							}
							else if (event0.type == Event:: KeyPressed && event0.key.code == Keyboard::D){
								del_point(p,num,i);
								proizv(p,m,i);
								dnd(p,m,i,window,Color::Black);
								turn=1;
							}
						}
						
					}
					
				}
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
				mode=mode^1;
				if (mode) dnd(p,m,i,window,Color::Black); else dnd(p,m,i,window,Color::Black);
			}
		}
	}
}
	catch (int i){printf("%d\n",i);}
	catch (ex a){a.out();}
	return 0;
}
