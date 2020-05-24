#include <iostream>
#include <algorithm>
#include <string>

class Grade
{
private:
	int kor, eng, math;
	std::string name;
public:
	Grade();
	Grade(int k, int e, int m, const std::string& n);
	void PrintName();
	bool operator < (const Grade& g) const;
};

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	int N;
	std::cin >> N;
	Grade* gArr = new Grade[N];

	for (int i = 0; i < N; ++i)
	{
		std::string n;
		int k, e, m;
		std::cin >> n >> k >> e >> m;
		gArr[i] = Grade(k, e, m, n);
	}

	std::sort(gArr, gArr + N);

	for (int i = 0; i < N; ++i)
	{
		gArr[i].PrintName();
	}

	delete[] gArr;
	return 0;
}

Grade::Grade()
{
	kor = eng = math = 0;
	name = "";
}

Grade::Grade(int k, int e, int m, const std::string& n)
{
	kor = k;
	eng = e;
	math = m;
	name = n;
}

void Grade::PrintName()
{
	std::cout << name << "\n";
}

bool Grade::operator<(const Grade& g) const
{
	if (kor > g.kor) return true;
	else if (kor == g.kor)
	{
		if (eng < g.eng) return true;
		else if (eng == g.eng)
		{
			if (math > g.math) return true;
			else if (math == g.math)
			{
				return name < g.name;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}