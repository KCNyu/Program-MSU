class shape {
	public:
	virtual double area () = 0;
	static int n;
};
class circle : public shape {
	double r;
	public:
	circle (double x = 0);
	virtual double area ();
	~circle ();
};
class triangle : public shape {
	double a;
	double h;
	public:
	triangle (double x = 0,double y = 0);
	virtual double area ();
	~triangle ();
};
class rhombus : public shape {
	double a;
	double h;
	public:
	rhombus (double x = 0,double y = 0);
	virtual double area ();
    void get();
	~rhombus ();
};
class square : public rhombus {
	public:
	square (double x = 0);
};
/*class tri_squ : public triangle,public square {
	double t_a;
	double t_h;
	double s_a;
	public:
	tri_squ (double x,double y,double z);
	virtual double area ();
	~tri_squ ();
};*/
