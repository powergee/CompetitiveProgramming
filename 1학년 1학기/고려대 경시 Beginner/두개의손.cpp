#include <iostream>
#include <string>
using namespace std;

string Winner(char m, char t)
{
    switch (m)
    {
    case 'R':
        if (t == 'R') return "?";
        else if (t == 'S') return "MS";
        else return "TK";
    case 'S':
        if (t == 'R') return "TK";
        else if (t == 'S') return "?";
        else return "MS";
    case 'P':
        if (t == 'R') return "MS";
        else if (t == 'S') return "TK";
        else return "?";

    default: return "";
    }
}

int main()
{
    char ml, mr, tl, tr;
    scanf("%c %c %c %c", &ml, &mr, &tl, &tr);

    bool mSame = ml == mr;
    bool tSame = tl == tr;

    if (mSame && tSame)
        cout << Winner(ml, tl);

    else if (mSame && !tSame)
    {
        string w1 = Winner(ml, tl);
        string w2 = Winner(ml, tr);

        if (w1 == "TK" || w2 == "TK")
            cout << "TK";
        else cout << "?";
    }

    else if (!mSame && tSame)
    {
        string w1 = Winner(ml, tl);
        string w2 = Winner(mr, tl);

        if (w1 =="MS" || w2 == "MS")
            cout << "MS";
        else cout << "?";
    }

    else
    {
        printf("?");
    }
    
    return 0;
}