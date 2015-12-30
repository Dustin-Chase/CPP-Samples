#include <iostream>
#include <vector>

using namespace std;

std::vector<int> reverse_vect1(const vector<int> & v)
{
    std::vector<int> reverse_v (v.size());
    for (unsigned int i = 0, j = v.size() - 1; i < v.size(); i++, j--)
    {
        reverse_v[j] = v[i];
    }
    return reverse_v;
}

void reverse_vect2(vector<int> & v)
{
    std::vector<int> reverse_v;
    for (unsigned int i = 0, j = v.size() - 1; i < v.size() / 2; i++, j--)
    {
        swap(v[i], v[j]);
    }
}

int main()
{

    std::vector<int> test;
    for (int i = 0; i < 11; i++)
    {
        test.push_back(i);
    }

    std::vector<int> reversed_1 = reverse_vect1(test);

    for (int i: test)
    {
        cout << i << " ";
    }
    cout << '\n';

    for (int i: reversed_1)
    {
        cout << i << " ";
    }
    cout << '\n';

    cout << "Reversing test using references...\n";
    reverse_vect2(test);

    for (int i: test)
    {
        cout << i << " ";
    }
    cout << '\n';
    return 0;
}
