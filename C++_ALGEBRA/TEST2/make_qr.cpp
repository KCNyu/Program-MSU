#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;
template <typename T>
class matrix {
private:
	vector<vector<T> > M;
	int row;
	int col;
public:
	matrix();
	matrix(const string& filename);
	matrix(int m,int n);
	int getRow() const;
	int getCol() const;
	void set(int i,int j,T val);
	matrix<T>& operator=(const matrix<T>& M1);
	template <typename U>
	friend matrix<U> operator+(const matrix<U>& M1,const matrix<U>& M2);
	template <typename U>
	friend matrix<U> operator-(const matrix<U>& M1,const matrix<U>& M2);
	template <typename U>
	friend matrix<U> operator*(const matrix<U>& M1,const matrix<U>& M2);
	matrix<T> operator*(T val);
	matrix<T>& transpose();
	template <typename U>
	friend matrix<U> H(const matrix<U>& M1);
	static matrix<T> identity(int n);
	template <typename U>
	friend double squareOfNorm2(const matrix<U>& A);
	template <typename U>
	friend U alpha(const matrix<U>& A);
	template <typename U>
	friend U w(const matrix<U>& x,const matrix<U>& u);
	template <typename U>
	friend matrix<U> getRn(const matrix<U>& x);
	template <typename U>
	friend void makeQR1(const matrix<U>& A,string filename);
	void GivensRotation(int r1,int r2,matrix<T>& Q);
	template <typename U>
	friend void makeQR2(const matrix<U>& A,string filename);
	template <typename U>
	friend U scalarProduct(const matrix<U>& M1,const matrix<U>& M2);
	template <typename U>
	friend void makeQR3(const matrix<U>& A,string filename);
	template <typename U>
	friend void write(const matrix<U>& M1,string filename);
	template <typename U>
	friend ostream& operator<<(ostream& os,const matrix<U>& M1);
	matrix<T>& swaps(int a,int b);
	T determinant() const;
	template <typename U>
	friend matrix<U> getX(const matrix<U>& Q,const matrix<U>& R,const matrix<U>& b);
};
double conjugation(double d) {
	return d;
}
complex<double> conjugation(complex<double> c) {
	complex<double> res(c.real(),-c.imag());
	return res;
}
double mold(double n) {
	return fabs(n);
}
double mold(const complex<double>& c) {
	return sqrt(c.real() * c.real() + c.imag() * c.imag());
}
template <typename T>
matrix<T>::matrix():row(0),col(0) {
}
template <>
matrix<double>::matrix(const string& filename) {
	ifstream file;
	file.open(filename);
	string s;
	string num;
	double n;
	vector<double> temp;
	bool read = false;
	if (filename[0] != 'b') {
		getline(file,s);
	}
	while (getline(file,s)) {
		for (char c : s) {
			if (c == '-' || isdigit(c)) {
				read = true;
			}
			else if (c == ' ') {
				read = false;
				if (num.size() > 0) {
					n = stod(num);
					temp.push_back(n);
					num.clear();
				}
			}
			else if (c == ';') {
				read = false;
				n = stod(num);
				temp.push_back(n);
				M.push_back(temp);
				num.clear();
				temp.clear();
			}
			else if (c == ']') {
				n = stod(num);
				temp.push_back(n);
				M.push_back(temp);
				num.clear();
				temp.clear();
				break;
			}
			if (read) {
				num += c;
			}
		}
	}
	file.close();
	row = M.size();
	col = M[0].size();
}
template <>
matrix<complex<double> >::matrix(const string& filename) {
	ifstream file;
	file.open(filename);
	string s;
	string num;
	double n;
	vector<complex<double> > temp;
	bool read = false;
	bool isFirst = true;
	int i = 0,j = 0;
	if (filename[0] != 'b') {
		getline(file,s);
	}
	while (getline(file,s)) {
		for (char c : s) {
			if (c == '-' || isdigit(c)) {
				read = true;
			}
			else if (c == ' ') {
				read = false;
				if (num.size() > 0) {
					if (isFirst) {
						n = stod(num);
						temp.push_back(complex<double>(n,0));
						num.clear();
					}
					else {
						n = stod(num);
						M[i][j] += complex<double>(0,n);
						j++;
						num.clear();
					}
				}
			}
			else if (c == ';') {
				read = false;
				if (isFirst) {
					n = stod(num);
					temp.push_back(complex<double>(n,0));
					M.push_back(temp);
					num.clear();
					temp.clear();
				}
				else {
					n = stod(num);
					M[i][j] += complex<double>(0,n);
					i++;
					j = 0;
					num.clear();
				}
			}
			else if (c == ']') {
				read = false;
				if (isFirst) {
					n = stod(num);
					temp.push_back(complex<double>(n,0));
					M.push_back(temp);
					num.clear();
					temp.clear();
					isFirst = false;
				}
				else {
					n = stod(num);
					M[i][j] += complex<double>(0,n);
					num.clear();
					break;
				}
			}
			if (read) {
				num += c;
			}
		}
	}
	file.close();
	row = M.size();
	col = M[0].size();
}
template <typename T>
matrix<T>::matrix(int m,int n) {
	row = m;
	col = n;
	vector<T> temp(n);
	for (int i = 0;i < m;i++) {
		M.push_back(temp);
	}
}
template <typename T>
int matrix<T>::getRow() const {
	return row;
}
template <typename T>
int matrix<T>::getCol() const {
	return col;
}
template <typename T>
void matrix<T>::set(int i,int j,T val) {
	M[i][j] = val;
}
template <typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& M1) {
	row = M1.row;
	col = M1.col;
	M.clear();
	for (int i = 0;i < row;i++) {
		vector<T> temp;
		for (int j = 0;j < col;j++) {
			temp.push_back(M1.M[i][j]);
		}
		M.push_back(temp);
	}
	return *this;
}
template <typename U>
matrix<U> operator+(const matrix<U>& M1,const matrix<U>& M2) {
	if ((M1.row!=M2.row) || (M1.col!=M2.col))
		throw "Error!Can't add!\n";
	matrix<U> res(M1.row,M1.col);
	for (int i = 0;i < res.row;i++)
		for (int j = 0;j < res.col;j++)
			res.set(i,j,M1.M[i][j]+M2.M[i][j]);
	return res;
}
template <typename U>
matrix<U> operator-(const matrix<U>& M1,const matrix<U>& M2) {
	if ((M1.row!=M2.row) || (M1.col!=M2.col))
		throw "Error!Can't minus!\n";
	matrix<U> res(M1.row,M1.col);
	for (int i = 0;i < res.row;i++)
		for (int j = 0;j < res.col;j++)
			res.set(i,j,M1.M[i][j]-M2.M[i][j]);
	return res;
}
template <typename U>
matrix<U> operator*(const matrix<U>& M1,const matrix<U>& M2)
{
	if (M1.col!=M2.row)
		throw "Error!Can't multiplied!\n";
	matrix<U> res(M1.row,M2.col);
	for (int i=0;i<res.row;i++)
		for (int j=0;j<res.col;j++)
		{
			U val = 0;
			for (int k = 0;k < M1.col;k++)
				val += M1.M[i][k]*M2.M[k][j];
			res.set(i,j,val);
		}
	return res;
}
template <typename T>
matrix<T> matrix<T>::operator*(T val) {
	matrix<T> res(row,col);
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			res.set(i,j,val * M[i][j]);
		}
	}
	return res;
}
template <typename T>
matrix<T>& matrix<T>::transpose() {
	matrix<T> temp = *this;
	M.clear();
	row = temp.col;
	col = temp.row;
	for (int i = 0;i < row;i++) {
		vector<T> vec;
		for (int j = 0;j < col;j++) {
			vec.push_back(temp.M[j][i]);
		}
		M.push_back(vec);
	}
	return *this;
}
template <>
matrix<double> H(const matrix<double>& M1) {
	matrix<double> res;
	res = M1;
	res.transpose();
	return res;
}
template <>
matrix<complex<double> > H(const matrix<complex<double> >& M1) {
	matrix<complex<double> > res(M1.row,M1.col);
	for (int i = 0;i < M1.row;i++) {
		for (int j = 0;j < M1.col;j++) {
			res.set(i,j,conjugation(M1.M[i][j]));
		}
	}
	res.transpose();
	return res;
}
template <typename T>
matrix<T> matrix<T>::identity(int n) {
	matrix<T> res(n,n);
	for (int i = 0;i < res.row;i++)
		for (int j = 0;j < res.col;j++)
		{
			if (i==j)
				res.set(i,j,1);
			else
				res.set(i,j,0);
		}
	return res;
}
template <>
double squareOfNorm2(const matrix<double>& A) {
	double res = 0;
	for (int i = 0;i < A.row;i++) {
		for (int j = 0;j < A.col;j++) {
			res += A.M[i][j] * A.M[i][j];
		}
	}
	return res;
}
template <>
double squareOfNorm2(const matrix<complex<double> >& A) {
	double res = 0;
	for (int i = 0;i < A.row;i++) {
		for (int j = 0;j < A.col;j++) {
			res += A.M[i][j].real() * A.M[i][j].real() + A.M[i][j].imag() * A.M[i][j].imag();
		}
	}
	return res;
}
template <>
double alpha(const matrix<double>& A) {
	double norm = sqrt(squareOfNorm2(A));
	return A.M[0][0] > 0 ? -norm : norm;
}
template <>
complex<double> alpha(const matrix<complex<double> >& A) {
	double norm = sqrt(squareOfNorm2(A));
	double x = A.M[0][0].real(),y = A.M[0][0].imag();
	double z = mold(A.M[0][0]);
	if (z == complex<double>(0,0)) {
		return norm;
	}
	return complex<double>(norm * (x/z),norm * (y/z));
}
template <>
double w(const matrix<double>& x,const matrix<double>& u) {
	return 1;
}
template <>
complex<double> w(const matrix<complex<double> >& x,const matrix<complex<double> >& v) {
	matrix<complex<double> > a = H(x) * v;
	matrix<complex<double> > b = H(v) * x;
	return a.M[0][0] / b.M[0][0];
}
template <typename U>
matrix<U> getRn(const matrix<U>& x) {
	matrix<U> e(x.row,1);
	matrix<U> u(x.row,1);
	matrix<U> uH;
	matrix<U> R;
	matrix<U> I;
	e.set(0,0,1);
	u = x + e * alpha(x);
	uH = H(u);
	I = matrix<U>::identity(x.row);
	matrix<U> v = u * (1.0 / sqrt(squareOfNorm2(u)));
	R = I - u * uH * ((1.0 + w(x,v))/squareOfNorm2(u));
	return R;
}
template <typename U>
void makeQR1(const matrix<U>& A,string filename) {
	matrix<U> R = A;
	matrix<U> Q = matrix<U>::identity(A.row);
	for (int k = 0;k < A.row - 1;k++) {
		int curRow = A.row - k;
		matrix<U> Rn = matrix<U>::identity(A.row);
		matrix<U> x(curRow,1);
		for (int i = k;i < A.row;i++) {
			x.set(i-k,0,R.M[i][k]);
		}
		matrix<U> _Rn = getRn(x);
		for (int i = 0;i < curRow;i++) {
			for (int j = 0;j < curRow;j++) {
				Rn.set(i+k,j+k,_Rn.M[i][j]);
			}
		}
		R = Rn * R;
		Q = Q * Rn;
		for (int i = k + 1;i < A.row;i++) {
			R.set(i,k,0);
		}
	}
	int pos1 = filename.find("t") + 1;
	int pos2 = filename.find(".");
	string num = filename.substr(pos1,pos2 - pos1);
	string filenameQ = "Qmat" + num + ".m";
	string filenameR = "Rmat" + num + ".m";
	write(Q,filenameQ);
	write(R,filenameR);
}
double getC(double a,double b) {
	return a / sqrt(a * a + b * b);
}
double getS(double a,double b) {
	return b / sqrt(a * a + b * b);
}
complex<double> getC(complex<double> a,complex<double> b) {
	double x = a.real(),y = a.imag();
	double z = sqrt(a.real() * a.real() + a.imag() * a.imag() + b.real() * b.real() + b.imag() * b.imag());
	return complex<double>(x / z,-y / z);
}
complex<double> getS(complex<double> a,complex<double> b) {
	double x = b.real(),y = b.imag();
	double z = sqrt(a.real() * a.real() + a.imag() * a.imag() + b.real() * b.real() + b.imag() * b.imag());
	return complex<double>(x / z,-y / z);
}
template <typename T>
void matrix<T>::GivensRotation(int r1,int r2,matrix<T>& Q) {
	T c = getC(M[r1][r1],M[r2][r1]),s = getS(M[r1][r1],M[r2][r1]);
	for (int j = r1;j < col;j++) {
		T temp1 = M[r1][j],temp2 = M[r2][j];
		M[r1][j] = c * temp1 + s * temp2;
		M[r2][j] = conjugation(-s) * temp1 + conjugation(c) * temp2;
	}
	for (int j = 0;j < col;j++) {
		T temp1 = Q.M[r1][j],temp2 = Q.M[r2][j];
		Q.set(r1,j,c * temp1 + s * temp2);
		Q.set(r2,j,conjugation(-s) * temp1 + conjugation(c) * temp2);
	}
}
template <typename U>
void makeQR2(const matrix<U>& A,string filename) {
	matrix<U> Q = matrix<U>::identity(A.row);
	matrix<U> R = A;
	for (int k = 0;k < R.row - 1;k++) {
		for (int i = k + 1;i < R.row;i++) {
			if (R.M[i][k] == U(0)) {
				continue;
			}
			R.GivensRotation(k,i,Q);
		}
	}
	Q = H(Q);
	int pos1 = filename.find("t") + 1;
	int pos2 = filename.find(".");
	string num = filename.substr(pos1,pos2 - pos1);
	string filenameQ = "Qmat" + num + ".m";
	string filenameR = "Rmat" + num + ".m";
	write(Q,filenameQ);
	write(R,filenameR);
}
template <>
double scalarProduct(const matrix<double>& M1,const matrix<double>& M2) {
	double res = 0;
	for (int i = 0;i < M1.row;i++) {
		res += M1.M[i][0] * M2.M[i][0];
	}
	return res;
}
template <>
complex<double> scalarProduct(const matrix<complex<double> >& M1,const matrix<complex<double> >& M2) {
	complex<double> res = 0;
	for (int i = 0;i < M1.row;i++) {
		res += M1.M[i][0] * conjugation(M2.M[i][0]);
	}
	return res;
}
template <typename U>
void makeQR3(const matrix<U>& A,string filename) {
	matrix<U> Q(A.row,A.col);
	matrix<U> R(A.row,A.col);
	vector<matrix<U> > vec;
	for (int k = 0;k < A.row;k++) {
		matrix<U> a(A.row,1);
		for (int i = 0;i < A.row;i++) {
			a.set(i,0,A.M[i][k]);
		}
		matrix<U> b = a;
		for (int i = 0;i < vec.size();i++) {
			b = b - vec[i] * scalarProduct(a,vec[i]);
		}
		matrix<U> e = b * (1.0 / sqrt(squareOfNorm2(b)));
		vec.push_back(e);
		for (int i = 0;i < Q.row;i++) {
			Q.set(i,k,e.M[i][0]);
		}
		R.set(k,k,sqrt(squareOfNorm2(b)));
		for (int i = 0;i < k;i++) {
			R.set(i,k,scalarProduct(a,vec[i]));
		}
	}
	int pos1 = filename.find("t") + 1;
	int pos2 = filename.find(".");
	string num = filename.substr(pos1,pos2 - pos1);
	string filenameQ = "Qmat" + num + ".m";
	string filenameR = "Rmat" + num + ".m";
	write(Q,filenameQ);
	write(R,filenameR);
}
template <>
void write(const matrix<double>& M1,string filename) {
	ofstream f;
	f.open(filename);
	if (M1.col == 1) {
		f << filename[0] << " = [";
		for (int i = 0;i < M1.row;i++) {
			f << to_string(M1.M[i][0]);
			if (i != M1.row - 1) {
				f << "; ";
			}
		}
		f << "];";
		return;
	}
	f << filename[0] << " = ..." << endl << "[";
	for (int i = 0;i < M1.row;i++) {
		for (int j = 0;j < M1.col;j++) {
			f << to_string(M1.M[i][j]);
			if (j != M1.col - 1) {
				f << " ";
			}
		}
		if (i != M1.row - 1) {
			f << ";" << endl;
		}
	}
	f << "];";
	f.close();
}
template <>
void write(const matrix<complex<double> >& M1,string filename) {
	ofstream f;
	f.open(filename);
	f << filename[0] << " = complex([";
	if (M1.col == 1) {
		for (int i = 0;i < M1.row;i++) {
			f << to_string(M1.M[i][0].real());
			if (i != M1.row - 1) {
				f << "; ";
			}
		}
		f << "],[";
		for (int i = 0;i < M1.row;i++) {
			f << to_string(M1.M[i][0].imag());
			if (i != M1.row - 1) {
				f << "; ";
			}
		}
		f << "]);";
		return;
	}
	for (int i = 0;i < M1.row;i++) {
		for (int j = 0;j < M1.col;j++) {
			f << to_string(M1.M[i][j].real());
			if (j != M1.col - 1) {
				f << " ";
			}
		}
		if (i != M1.row - 1) {
			f << ";" << endl;
		}
	}
	f << "],[";
	for (int i = 0;i < M1.row;i++) {
		for (int j = 0;j < M1.col;j++) {
			f << to_string(M1.M[i][j].imag());
			if (j != M1.col - 1) {
				f << " ";
			}
		}
		if (i != M1.row - 1) {
			f << ";" << endl;
		}
	}
	f << "]);";
	f.close();
}
template <typename U>
ostream& operator<<(ostream& os,const matrix<U>& M1) {
	for (auto row : M1.M) {
		for (U val : row) {
			os << val << ' ';
		}
		os << endl;
	}
	return os;
}
int getMethodType(string filename) {
	ifstream file;
	file.open(filename);
	string s;
	getline(file,s);
	int pos = s.find("=") + 1;
	file.close();
	return s[pos] - '0';
}
bool isMatrixComplex(string filename) {
	ifstream file;
	file.open(filename);
	string s;
	getline(file,s);
	getline(file,s);
	bool res = (s.find("complex") != s.npos);
	file.close();
	return res;
}
template <typename T>
void makeQR(const matrix<T>& A,int type,string filename) {
	if (A.getRow() != A.getCol()) {
		cout << "Error!The matrix is not a square matrix!" << endl;
		return;
	}
	switch (type) {
		case 1:
			makeQR1(A,filename);
			break;
		case 2:
			makeQR2(A,filename);
			break;
		case 3:
			makeQR3(A,filename);
			break;
	}
}
template <typename T>
matrix<T>& matrix<T>::swaps(int a,int b) {
	T temp;
	for (int i = 0;i < col;i++)
	{
		temp = M[a][i];
		set(a,i,M[b][i]);
		set(b,i,temp);
	}
	return *this;
}
template <typename T>
T matrix<T>::determinant() const {
	if (row!=col)
		throw "Error!The matrix is not a square matrix!\n";
	matrix<T> res = *this;
	T d = 1;
	for (int k = 0;k < row - 1;k++)
	{
		T a = res.M[k][k];
		if (a == T(0))
		{
			int x;
			for (x = k + 1;x < row;x++)
				if (res.M[x][k] != T(0))
				{
					res.swaps(k,x);
					a = res.M[k][k];
					break;
				}
			if (x == row)
				return 0;
		}
		for (int i = k + 1;i < row;i++)
		{
			T b = res.M[i][k];
			d /= a;
			for (int j = k;j < col;j++)
				res.set(i,j,res.M[i][j]*a - res.M[k][j]*b);
		}
	}
	for (int i = 0;i < row;i++)
		d *= res.M[i][i];
	return d;
}
bool isExist(string filename) {
	ifstream f;
	f.open(filename);
	bool res = f.good();
	f.close();
	return res;
}
template <typename U>
matrix<U> getX(const matrix<U>& Q,const matrix<U>& R,const matrix<U>& b) {
	matrix<U> QHb = H(Q) * b;
	matrix<U> x(b.row,1);
	for (int k = 0;k < x.row;k++) {
		U sum = 0;
		int index = x.row - k - 1;
		for (int j = index + 1;j < R.col;j++) {
			sum += R.M[index][j] * x.M[j][0];
		}
		x.set(index,0,(QHb.M[index][0] - sum) / R.M[index][index]);
	}
	return x;
}
void makeQR(string filename) {
	bool isComplex = isMatrixComplex(filename);
	int type = getMethodType(filename);
	if (!isComplex) {
		matrix<double> A(filename);
		makeQR(A,type,filename);
	}
	else {
		matrix<complex<double> > A(filename);
		makeQR(A,type,filename);
	}
}
void solve(string filenameA,string filenameb) {
	int pos1 = filenameA.find("t") + 1;
	int pos2 = filenameA.find(".");
	string num = filenameA.substr(pos1,pos2 - pos1);
	string filenameQ = "Qmat" + num + ".m";
	string filenameR = "Rmat" + num + ".m";
	string filenamex = "xvec" + num + ".m";
	bool isComplex = isMatrixComplex(filenameA);
	int type = getMethodType(filenameA);
	if (!isComplex) {
		matrix<double> A(filenameA);
		matrix<double> b(filenameb);
		if (A.getRow() != b.getRow() || A.determinant() == 0) {
			cout << "Error!Can't solve!" << endl;
			return;
		}
		if (!isExist(filenameQ) || !isExist(filenameR)) {
			makeQR(A,type,filenameA);
		}
		matrix<double> Q(filenameQ);
		matrix<double> R(filenameR);
		matrix<double> x = getX(Q,R,b);
		write(x,filenamex);
	}
	else {
		matrix<complex<double> > A(filenameA);
		matrix<complex<double> > b(filenameb);
		if (A.getRow() != b.getRow() || A.determinant() == complex<double>(0)) {
			cout << "Error!Can't solve!" << endl;
			return;
		}
		if (!isExist(filenameQ) || !isExist(filenameR)) {
			makeQR(A,type,filenameA);
		}
		matrix<complex<double> > Q(filenameQ);
		matrix<complex<double> > R(filenameR);
		matrix<complex<double> > x = getX(Q,R,b);
		write(x,filenamex);
	}
}
int main() {
	string filenameA,filenameb;
	for (int i = 5;i <= 7;i++) {
		filenameA = "Amat" + to_string(i) +".m";
		makeQR(filenameA);
	}
	filenameA = "Amat8.m";
	filenameb = "bvec8.m";
	solve(filenameA,filenameb);
	clock_t start,end;
	filenameA = "Amat9.m";
	filenameb = "bvec9.m";
	start = clock();
	solve(filenameA,filenameb);
	end = clock();
	ofstream f;
	f.open("task_2c.txt");
	f << "The runtime is " << (end - start) / CLOCKS_PER_SEC << " s";
	f.close();
	return 0;
}
