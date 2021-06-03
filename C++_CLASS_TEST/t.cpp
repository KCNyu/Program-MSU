#include <iostream>
#include <string.h>

using namespace std;

class subject{
public:
	virtual ~subject(){}
	virtual double score()=0;
};

class ODE: virtual public subject{
	double kp1,kp2,kp3,kp4,kolok,exam;
public:
	ODE(double a1,double a2,double a3,double a4,double a5,double a6) {kp1=a1;kp2=a2;kp3=a3;kp4=a4;kolok=a5;exam=a6;}
	virtual double score(){
		return (kp1+kp2+kp3+kp4)/4*0.4+kolok*0.3+exam*0.3;
	}
};

class OC: virtual public subject{
	double kp1,kp2;
	int homework,prac;
public:
	OC(double a1,double a2,int a3,int a4){kp1=a1;kp2=a2;homework=a3;prac=a4;}
	virtual double score(){
		return (kp1+kp2)/2.0+homework/20+prac/20;
	}
};

class PE: public subject{
	int srun,lrun,ljump,situp,BMI;
public:
	PE(int a1,int a2,int a3,int a4,int a5){srun=a1;lrun=a2;ljump=a3;situp=a4;BMI=a5;}
	double score(){
		return srun+lrun+ljump+situp+BMI;
	}
};

class term: public OC, public ODE{
	string name;
public:
	term(string s,double kp1,double kp2,int homework,int prac,
		double Kp1,double Kp2,double Kp3,double Kp4,double kolok,double exam)
	:OC(kp1,kp2,homework,prac),ODE(Kp1,Kp2,Kp3,Kp4,kolok,exam){name=s;}
	string getname(){return name;}
	virtual double score();
};

double term::score(){
	if(OC::score()<60||ODE::score()<60){
		cout<<getname()<<" Got D in this term."<<endl;
		return 2;
	}
	if(OC::score()<75||ODE::score()<75){
		cout<<getname()<<" Got C in this term."<<endl;
		return 3;
	}
	if(OC::score()<85||ODE::score()<85){
		cout<<getname()<<" Got B in this term."<<endl;
		return 4;
	}
	if(OC::score()>=85&&ODE::score()>=85)
		cout<<getname()<<" Got A in this term."<<endl;
	return 5;
}

int main(){
	OC a1(85.0,87.5,90,70);
	ODE b1(60.0,95.0,100.0,70.5,76.5,91.5);
	PE c1(60,50,40,30,20);
	term Student1("Zhang San",85.0,87.5,90,70,60.0,95.0,100.0,70.5,76.5,91.5);
	subject *ptr = & Student1;
	ptr->score();
	return 0;
}
