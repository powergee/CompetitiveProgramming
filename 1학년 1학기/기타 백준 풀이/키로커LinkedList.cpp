// 제출해보니 틀림. 이유 불명.

#include <iostream>
#include <list>

using namespace std;

char input[1000001];

int main()
{
	int tc;
	scanf("%d", &tc);

	list<char> text;
	list<char>::iterator pos;

	for (; tc > 0; --tc)
	{
		text.clear();

		cin >> input;

		for (int i = 0; input[i] != '\0'; ++i)
		{
			switch (input[i])
			{
			case '-':
				if (!text.empty() && pos != text.begin())
					text.erase(prev(pos));

				break;

			case '<':
				if (!text.empty() && pos != text.begin())
					--pos;

				break;

			case '>':
				if (!text.empty() && pos != text.end())
					++pos;

				break;

			default:
				if (text.empty() || pos == text.end())
				{
					text.push_back(input[i]);
					pos = text.end();
				}
				else
				{
					text.insert(pos, input[i]);
					++pos;
				}

				break;
			}
		}

		for (char ch : text)
			printf("%c", ch);

		printf("\n");
	}

	return 0;
}
