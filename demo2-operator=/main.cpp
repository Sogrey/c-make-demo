#include <iostream>
using namespace std;
class Point{
public:
	float _x,_y;

	Point(float x=0.0,float y=0.0): _x(x),_y(y){
	}
	Point& operator=(const Point& p){
		if(this==&p)
			return *this;
		_x=p._x;
		_y=p._y;
		return *this;
	}
	void printData(){
		cout<<"_x="<<_x<<endl;
		cout<<"_y="<<_y<<endl;
	}
};
 
class Point3d:public virtual Point{
public:
	float _z;

	Point3d(float x=0.0,float y=0.0,float z=0.0):Point(x,y),_z(z){
		_x = x;
		_y = y;
	}
	Point3d& operator=(const Point3d& p){
		if(this==&p)
			return *this;
		Point::operator=(p);
		_z=p._z;
		return *this;
	}
	void printData(){
		Point::printData();
		cout<<"_z="<<_z<<endl;
	}	
};

class Point4d:public virtual Point3d{
public:
	float _w;

	Point4d(float x=0.0,float y=0.0,float z=0.0,float w=0.0):Point3d(x,y,z),_w(w){
		_x = x;
		_y = y;
		_z = z;
	}
	Point4d& operator=(const Point4d& p){
		if(this==&p)
			return *this;
		Point3d::operator=(p);
		_w=p._w;
		return *this;
	}
	void printData(){
		Point3d::printData();
		cout<<"_w="<<_w<<endl;
	}
};

int main(){	
	Point3d a(1,2,3),b(4,5,6);
	a=b;
	a.printData();
	
	Point4d a4,b4(4,5,6,7);
	a4 = b4;
	a4.printData();
	b4.printData();
	return 0;
}