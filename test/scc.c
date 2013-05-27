void f1();
void f2();
void f3();
void f4();

void f1() { f2();}
void f2() { f3();}
void f3() { f4();}
void f4() { f1(); f3();}
