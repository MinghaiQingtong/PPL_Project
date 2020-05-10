#include <iostream>
#include <ppl_test.hh>
#include <ppl_c.h>
using namespace std;
int main(){
	Variable a(0);
	Variable b(1);
	Variable c(2);
	Variable d(3);

	Constraint_System cs;
	cs.insert(a+b+c+d >= 1);
	cs.insert(a-2*c <= -1);
	cs.insert(b+c-d >= 0);

	C_Polyhedron cp(cs);
	cp.print();cout<<endl;

	Generator_System gs = cp.generators();
	gs.print();cout<<endl;


}
