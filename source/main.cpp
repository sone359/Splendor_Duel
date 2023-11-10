#include <iostream>

#include "stockGemmes.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    //Tests concernant StockGemmes
    StockGemmes stockTest;
    cout << stockTest.get_Blanc() << endl;
    StockGemmes stockTest2(1, 2, 3, 4, 2, 1);
    cout << stockTest2.get_Blanc() << endl;
    return 0;
}
