// DataPrepDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

int main()
{
    const int eventSize = 0x68;
    std::ifstream ifs;
    ifs.open("loggerdata.txt", std::ifstream::binary);
    char buf[eventSize];

    std::ofstream ofs;
    ofs.open("prepareddata.txt",std::ifstream::binary);
    int i = 0;
    std::cout << ifs.good() << ifs.eof() << ifs.fail() << ifs.bad() << std::endl;
    while (ifs.read(buf, eventSize))
    {
        ++i;
        if (buf[0] != eventSize)
        {
            break;
        }
        
        
        float x = *(float*)(buf + 0x18);
        float y = *(float*)(buf + 0x1c);
        float z = *(float*)(buf + 0x20);
        long t = *(long*)(buf + 0x10);
        //sensor type here int s = *(int*)(buf + 0x08);
        std::cout << x << ' ' << y << ' ' << z << std::endl;
        ofs.write(buf + 0x10, 0x14); // write timestamp and sensor data
        

    }
    std::cout << i << std::endl;
    std::cout << ifs.good() << ifs.eof() << ifs.fail() << ifs.bad() << std::endl;
    ifs.close();
    ofs.close();

    
    //ofs.write(buf, 104);
    
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
