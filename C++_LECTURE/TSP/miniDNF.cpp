#include <iostream>
#include <climits>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

using vec_i = vector<size_t>;
using vec_s = vector<string>;
using vec_p = vector<pair<string, bool>>;

using mat_i = vector<vec_i>;
using mat_b = vector<vector<bool>>;

using cube_i = vector<mat_i>;

size_t Weight(const string &a)
{
	size_t k = 0;
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] != '2')
			k++;
	}
	return k;
}
string Gluing(const string &a, const string &b)
{
	string result;
	size_t found = 0;
	size_t kol = 0, i = 0;
	while ((kol < 2) && (i < a.length()))
	{
		if ((a[i] != b[i]))
		{
			kol++;
			found = i;
		}
		i++;
	}
	if (kol == 1)
	{
		result = a;
		result[found] = '2';
	}
	return result;
}

string Absorption(const string &a, const string &b)
{
	string result;
	size_t found = 0;
	size_t kol = 0, i = 0;
	while ((kol < 2) && (i < a.length()))
	{
		if (((a[i] == '2') && (b[i] != '2')) || ((b[i] == '2') && (a[i] != '2')))
		{
			kol++;
			found = i;
		}
		else if ((a[i] != '2') && (b[i] != '2') && (a[i] != b[i]))
			return result;
		i++;
	}
	if (kol == 1)
	{
		result = a;
		result[found] = '2';
	}
	return result;
}

mat_i Implmult(mat_i a, mat_i b)
{
	mat_i result;
	for (auto &x : a)
		for (auto &y : b)
		{
			vec_i buff;
			for (auto &xi : x)
			{
				buff.push_back(xi);
			}
			for (auto &yi : y)
			{
				if (find(buff.begin(), buff.end(), yi) == buff.end())
				{
					buff.push_back(yi);
				}
			}
			result.push_back(buff);
		}
	return result;
}

class miniDNF
{
private:
	const string origin_string;
	vec_p adnf;
	vec_p sdnf;
	vec_s mdnf;
	mat_b mat;
	string result_string;

public:
	miniDNF(string input);
	void CheckInput();
	string Bin(size_t x, size_t len);
	void Abbreviate();
	void Abbreviate(string function(const string &, const string &));
	void InitMat();
	void Solve();
	bool Owns(const string &A, const string &B);
	void MDNF();
	void Formula();
	vec_s Cover(const vec_i &nepokr, const vec_i &ignor);
};
void miniDNF::CheckInput()
{
	if (origin_string.size() == 0)
	{
		throw "Empty file\n";
	}
	if (floor(log2(origin_string.size())) != log2(origin_string.size()))
	{
		throw "Check function\n";
	}
	for (auto &x : origin_string)
	{
		if (x != '0' && x != '1')
			throw "Unknown\n";
	}
}
string miniDNF::Bin(size_t x, size_t len)
{
	string res;
	while (x > 0)
	{
		size_t buf = x & 1;
		x >>= 1;
		res.append(to_string(buf));
	}
	reverse(res.begin(), res.end());
	if (res.length() < len)
	{
		string zeros(len - res.length(), '0');
		res = zeros + res;
	}
	return res;
}
miniDNF::miniDNF(string input) : origin_string(input)
{
	CheckInput();
	double len = log2(origin_string.size());
	for (size_t i = 0; i < origin_string.length(); ++i)
	{
		if (origin_string[i] == '1')
		{
			string res = Bin(i, static_cast<size_t>(len));
			sdnf.push_back(make_pair(res, false));
		}
	}
	adnf = sdnf;
}

void miniDNF::Abbreviate()
{
	Abbreviate(Gluing);
	Abbreviate(Absorption);
}
void miniDNF::Abbreviate(string function(const string &, const string &))
{
	while (1)
	{
		vec_p h;
		bool flag = false;
		for (auto i = sdnf.begin(); i != sdnf.end(); i++)
		{
			for (auto j = i + 1; j != sdnf.end(); ++j)
			{
				if (i != j)
				{
					string buf = function(i->first, j->first);
					if (!buf.empty())
					{
						i->second = true;
						j->second = true;
						flag = true;
						auto object = pair<string, bool>(buf, false);
						bool X3 = false;
						for (auto &x : h)
						{
							if (x.first == object.first)
							{
								X3 = true;
							}
						}
						if (!X3)
							h.push_back(object);
					}
				}
			}
			if (i->second == false)
			{
				bool X3 = false;
				for (auto &x : h)
				{
					if (x.first == i->first)
					{
						X3 = true;
					}
				}
				if (!X3)
					h.push_back(*i);
			}
		}
		if (flag != true)
			break;
		sdnf = h;
	}
}
void miniDNF::InitMat()
{
	mat.resize(adnf.size());
	for (size_t i = 0; i < adnf.size(); i++)
	{
		mat[i].resize(sdnf.size());
		for (size_t j = 0; j < sdnf.size(); j++)
		{
			if (Owns(adnf[i].first, sdnf[j].first))
			{
				mat[i][j] = true;
			}
			else
			{
				mat[i][j] = false;
			}
		}
	}
}
bool miniDNF::Owns(const string &A, const string &B)
{
	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] != B[i] && A[i] != '2' && B[i] != '2')
		{
			return false;
		}
	}
	return true;
}
void miniDNF::MDNF()
{
	vec_i pokr;
	vec_i consider;
	for (size_t i = 0; i < sdnf.size(); i++)
	{
		size_t kol = 0;
		size_t cec = 0;
		for (size_t j = 0; j < adnf.size(); j++)
		{
			if (mat[j][i] == true)
			{
				kol++;
				cec = j;
			}
		}
		if (kol == 1)
		{
			auto object = make_pair(adnf[cec].first, false);
			bool X3 = false;
			for (auto &x : mdnf)
			{
				if (x == object.first)
				{
					X3 = true;
				}
			}
			if (!X3)
			{
				for (size_t k = 0; k < sdnf.size(); k++)
				{
					if (mat[cec][k] == true && find(pokr.begin(), pokr.end(), k) == pokr.end())
					{
						pokr.push_back(k);
					}
				}
				consider.push_back(cec);
				mdnf.push_back(object.first);
			}
		}
	}
	if (pokr.size() == sdnf.size())
		return;
	vec_i nepokr;
	for (size_t i = 0; i < sdnf.size(); i++)
	{
		if (find(pokr.begin(), pokr.end(), i) == pokr.end())
			nepokr.push_back(i);
	}
	vec_i ignor;
	for (size_t i = 0; i < adnf.size(); i++)
	{
		if (find(consider.begin(), consider.end(), i) == consider.end())
			ignor.push_back(i);
	}
	vec_s b = Cover(nepokr, ignor);
	for (auto &x : b)
	{
		mdnf.push_back(x);
	}
}
vec_s miniDNF::Cover(const vec_i &nepokr, const vec_i &ignor)
{
	vec_s a;
	cube_i patrik;
	patrik.resize(nepokr.size());
	size_t i = 0;
	for (auto &x : nepokr)
	{
		size_t j = 0;
		for (auto &y : ignor)
		{
			vec_i K;
			if (mat[y][x] == true)
			{
				K.push_back(y);
				patrik[i].push_back(K);
			}
			j++;
		}
		i++;
	}

	while (patrik.size() > 1)
	{
		mat_i sets = Implmult(patrik[0], patrik[1]);
		patrik.erase(patrik.begin(), patrik.begin() + 2);
		if (sets.size())
		{
			patrik.push_back(sets);
		}
	}
	size_t wei = LONG_MAX;
	size_t l = 0, p = 0;
	for (size_t i = 0; i < patrik.size(); i++)
	{
		for (size_t j = 0; j < patrik[i].size(); j++)
		{
			size_t cur_w = 0;
			for (auto &x : patrik[i][j])
			{
				cur_w += Weight(adnf[x].first);
			}
			if (cur_w < wei)
			{
				wei = cur_w;
				l = i;
				p = j;
			}
		}
	}
	for (auto &x : patrik[l][p])
	{
		a.push_back(adnf[x].first);
	}
	return a;
}
void miniDNF::Formula()
{
	stringstream result;
	if (mdnf.size() > 0)
	{
		size_t k = 0;
		for (auto &x : mdnf)
		{
			k++;
			size_t i = 0;
			for (auto &y : x)
			{
				if (y == '2')
				{
					i++;
					continue;
				}
				else if (y == '1')
				{

					result << "x" << i;
					i++;
				}
				else if (y == '0')
				{
					result << "!x" << i;
					i++;
				}
			}
			if (k != mdnf.size())
				result << " U ";
		}
	}
	result_string = result.str();
}
void miniDNF::Solve()
{
	Abbreviate();
	InitMat();
	MDNF();
	Formula();
	cout << result_string << endl;
}
int main(int argc, char *argv[])
{
	miniDNF mdnf = miniDNF("10101110");
	mdnf.Solve();
	return 0;
}