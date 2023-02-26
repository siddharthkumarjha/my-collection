#include<iostream>
using namespace std;
struct test{
	int x=0;
	int y=0;
	test operator + (test &t2){
		test t = {0,0};
		t.x = this->x + t2.x;
		t.y = this->y + t2.y;
		cout << "Within class\n["<<this->x<<", "<<this->y<<"], ["<<t2.x<<", "<<t2.y<<"]"<<endl;
		return t;
	}
};
int main(){
	test t1 = {3,5};
	test t2 = {4,5};
	test t3 = {7, 8};
	test t = t1 + t2 + t3;
	cout << "["<<t.x<<", "<<t.y<<"]"<<endl;
	return 0;
}
