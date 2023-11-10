#include <iostream>

#include "stockGemmes.h"
#include "plateau.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    //Tests concernant StockGemmes
    StockGemmes stockTest;
    cout << stockTest.get_Blanc() << endl;
    StockGemmes stockTest2(1, 2, 3, 4, 2, 1);
    cout << stockTest2.get_Blanc() << endl;
    //Tests concernant Plateau
    cout << Plateau::minLigne({0, 5}, {1, 4}, {2, 2})[0] << endl;
    cout << Plateau::minColonne({6, 5}, {1, 3}, {2, 2})[0] << endl;
    cout << Plateau::verifAdjacence({0, 0}, {1, 1}, {2, 2}) << endl;
    cout << Plateau::verifAdjacence({0, 0}, {1, 1}, {3, 3}) << endl;
    cout << Plateau::verifAdjacence({0, 0}, {0, 1}, {0, 2}) << endl;
    cout << Plateau::verifAdjacence({3, 1}, {1, 1}, {2, 1}) << endl;
    cout << Plateau::verifAdjacence({0, 0}, {1, 1}) << endl;
    cout << Plateau::verifAdjacence({0, 0}, {0, 1}) << endl;
    cout << Plateau::verifAdjacence({0, 0}, {1, 0}) << endl;
    cout << Plateau::verifAdjacence({3, 1}, {1, 1}) << endl;
    cout << Plateau::verifAdjacence({2, 2}, {1, 1}) << endl;
    Plateau pl;

    return 0;
}
