
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t, n, a[n];
    cout<<"enter number of iteration you want: \t";
    cin >> t;
    while (t--)
    {   
        cout<<"enter number of elements : \t ";
        cin >> n;
        cout<<"enter"<<" "<< n <<" "<<"of elements: \t";
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sort(a, a + n);
        for (int i = 0; i < n - 2; i++)
        {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}