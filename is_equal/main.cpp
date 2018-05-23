//#include <iostream>
//using namespace std;


//int main() {
//    int T, N, p;
//    int a[200];
//    cin >> T;
//    for (int i = 0; i < T; ++i )
//    {
//        cin >> N >> p;
//        bool is_equal = false;
//        for (int j = 0; j < N; ++j)
//        {
//             cin >> a[j];
//        }
//        for (int j = 0; j < N; ++j)
//        {
//             for (int n = 0; n < N; n++)
//             {
//                 for (int m = 0; m < N; m++)
//                 {
//                    if((a[n]*a[m])==p)
//                    {
//                        is_equal = true;
//                        break;
//                    }
//                 }
//                 if (is_equal)
//                    break;
//             }
//        }
//        if (is_equal)
//            cout << "Yes" << endl;
//        else
//            cout << "No" << endl;
//    }
//    return 0;
//}

// Static assertion using #error directive
#include <iostream>
using namespace std;
#if !defined(__geeksforgeeks)
#error "Geeksforgeeks hasn't been defined yet".
#endif
int main()
{
    cout << "main" << endl;
    return 0;
}
