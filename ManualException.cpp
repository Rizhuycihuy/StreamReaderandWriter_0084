#include <iostream>
using namespace std;

int main()
{
    try
    {
        cout << "Selamat belajar di prodi ti umy" << endl;
        //throw 0.5;
        cout << " pernyataan tidak akan di tampilkan" << endl;
    }

    catch (int a)
    {
        cout << "pengecualian akan di eksekusi" << endl;
    }
}