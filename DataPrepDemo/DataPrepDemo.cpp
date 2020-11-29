// DataPrepDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

int main()
{
    std::ifstream ifs;
    ifs.open("loggerdemo.txt");
    char buf[104];


    ifs.get(buf, 104);

    std::cout << buf[0];
    float x = *(float*)(buf + 0x18);
    float y = *(float*)(buf + 0x1c);
    float z = *(float*)(buf + 0x20);
    std::cout << x << y << z;

    ifs.close();
    ofs.close();

    std::ofstream ofs;
    ofs.open("test.txt");
    ofs.write(buf, 104);
    
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file