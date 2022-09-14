#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct Student
{
	int d = 0;
	std::set<int> known;
};

int StuCompare(const Student* s1, const Student* s2)
{
	return s1->d < s2->d;
}

int CountUni(int* alg, int K)
{
	int result = 0;
	for (int i = 0; i < K; ++i)
	{
		if (alg[i] > 0)
			++result;
	}

	return result;
}

int CountInter(int* alg, int K, int numOfPeople)
{
	int result = 0;
	for (int i = 0; i < K; ++i)
	{
		if (alg[i] == numOfPeople)
			++result;
	}

	return result;
}

void UpdateUni(Student* ele, int* alg, int K, int& uni, bool removed)
{
	if (removed)
	{
		for (int ai : ele->known)
		{
			if (alg[ai] - 1 == 0)
				--uni;

			--alg[ai];
		}
	}

	else
	{
		for (int ai : ele->known)
		{
			if (alg[ai] == 0)
				++uni;

			++alg[ai];
		}
	}
}

void UpdateInter(Student* ele, int* algAfter, int K, int numOfPeople, int& inter, bool removed)
{
	if (numOfPeople == 0)
		return;

	if (removed)
	{
		inter = CountInter(algAfter, K, numOfPeople);
	}

	else
	{
		int newInter = 0;
		for (int ai : ele->known)
		{
			if (algAfter[ai] == numOfPeople)
				++newInter;
		}

		inter = newInter;
	}
}

Student* students[100001];

int main()
{
	int N, K, D;
	scanf("%d %d %d", &N, &K, &D);

	for (int i = 0; i < N; ++i)
	{
		int M, d;
		scanf("%d %d", &M, &d);

		Student* s = new Student;
		s->d = d;

		for (int j = 0; j < M; ++j)
		{
			int ai;
			scanf("%d", &ai);

			s->known.insert(ai);
		}

		students[i] = s;
	}

	std::sort(students, students + N, StuCompare);

	Student* arrEnd = students[N];
	Student* left = students[0];
	Student* right = students[0];

	int algMembers[30] = {0, };

	while (right != arrEnd && right->d - left->d <= D)
		++right;

	for (Student* s = left; s != right; ++s)
	{
		for (int n : s->known)
		{
			++algMembers[n];
		}
	}

	int uni = CountUni(algMembers, K), inter = CountInter(algMembers, K, (right - left) / sizeof(Student));
	int maxE = -1;

	while (left != arrEnd)
	{
		int E = (uni - inter) * ((right - left) / sizeof(Student));
		maxE = std::max(maxE, E);

		if (right != arrEnd)
		{
			++right;
			UpdateUni(right - 1, algMembers, K, uni, false);
			UpdateInter(right - 1, algMembers, K, ((right - left) / sizeof(Student)), inter, false);
		}

		while (left != arrEnd && right->d - left->d > D)
			UpdateUni(left++, algMembers, K, uni, true);

		inter = CountInter(algMembers, K, (right - left) / sizeof(Student));
	}

	printf("%d", maxE);
}