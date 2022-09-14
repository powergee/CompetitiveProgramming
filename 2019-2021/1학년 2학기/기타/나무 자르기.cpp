#include <iostream>
#include <algorithm>

struct Func
{
    long long a, b;
    double cross;
};


template <typename T>
class ArrayStack
{
private:
	T arr[100001] = {0,};
	int pos = 0;

public:
	ArrayStack() { }

	T& operator[](int index)
	{
		return arr[index];
	}

	void Push(const T& ele)
	{
		arr[pos++] = ele;
	}

	int Size()
	{
		return pos;
	}

	void Pop()
	{
		if (pos > 0)
			--pos;
	}

	T Top()
	{
		return arr[pos - 1];
	}

	bool Empty()
	{
		return pos == 0;
	}
};

double Cross(Func& f1, Func& f2)
{
	return ((double)f2.b - f2.b) / ((double)f1.a - f2.a);
}

ArrayStack<Func> s;
long long height[100001];
long long cost[100001];
long long dp[100001];

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
		scanf("%lld", height + i);

	for (int i = 0; i < n; ++i)
		scanf("%lld", cost + i);

	int fPos = 0;

	for (int i = 1; i < n; ++i)
	{
		Func newF = { cost[i - 1], dp[i - 1] };
		while (!s.Empty())
		{
            newF.cross = Cross(newF, s.Top());
            if (s.Top().cross < newF.cross)
                break;

            s.Pop();
            if (s.Size() == fPos)
                --fPos;
		}

		s.Push(newF);

		long long x = height[i];
		while (fPos + 1 < s.Size() && s[fPos + 1].cross < x)
			++fPos;

		dp[i] = s[fPos].a * x + s[fPos].b;
	}

	printf("%lld\n", dp[n - 1]);

	return 0;
}