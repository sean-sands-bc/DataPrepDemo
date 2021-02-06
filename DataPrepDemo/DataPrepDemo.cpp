// DataPrepDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <fstream>
#include <string>
//#include <filesystem>
#include <experimental/filesystem>


void extractFields()
{
    const int eventSize = 0x68;

    //std::filesystem::directory_entry("/tdg");
    auto gyro = std::experimental::filesystem::directory_entry("./gyro");
    std::cout << gyro.path().generic_string() << std::endl;
    for (auto& entry : std::experimental::filesystem::directory_iterator("./tdg"))
    {   
        std::cout << entry.path().generic_string() << std::endl;
        //std::cout << gyro.path().generic_string() +"/"+ entry.path().filename().replace_extension(".gyro").generic_string() << std::endl;
        std::cout << ( gyro.path() / (entry.path().filename().replace_extension(".gyro") ) ).generic_string() << std::endl;
        
        std::ifstream ifs;
        //ifs.open("loggerdata.txt", std::ifstream::binary);
        ifs.open(entry.path().generic_string(), std::ifstream::binary);
        char buf[eventSize];

        std::ofstream ofs;
        //ofs.open("prepareddata.txt", std::ifstream::binary);
        ofs.open((gyro.path() / (entry.path().filename().replace_extension(".gyro"))).generic_string(), std::ifstream::binary);
        int i = 0;
        //std::cout << ifs.good() << ifs.eof() << ifs.fail() << ifs.bad() << std::endl;
//        unsigned long long t1=0;
//        unsigned long long t2;
        while (ifs.read(buf, eventSize))
        {
            ++i;
            if (buf[0] != 0x68) // check for size signature
            {
                std::cout << i << std::endl;
                break;
            }


            //float x = *(float*)(buf + 0x18);
            //float y = *(float*)(buf + 0x1c);
            //float z = *(float*)(buf + 0x20);
//            t2 = *(unsigned long long*)(buf + 0x10);
            //sensor type here int s = *(int*)(buf + 0x08);
            //std::cout << x << ' ' << y << ' ' << z << std::endl;
//            std::cout << (t2-t1) << std::endl;
            ofs.write(buf + 0x10, 0x14); // write timestamp and sensor data
//            t1 = t2;
            
        }
        ifs.close();
        ofs.close();
            
    }
        //std::cout << i << std::endl;
        //std::cout << ifs.good() << ifs.eof() << ifs.fail() << ifs.bad() << std::endl;
        

}

void normalizeFields()
{
    const int eventSize = 0x14;
    std::ifstream ifs;
    ifs.open("prepareddata.txt", std::ifstream::binary);
    char buf[eventSize];

    std::ofstream ofs;
    ofs.open("normalizeddata.txt", std::ifstream::binary);

    while (ifs.read(buf, eventSize))
    {
        //++i;
        //long t = *(long*)(buf);
        float x = *(float*)(buf + 0x8);
        float y = *(float*)(buf + 0xc);
        float z = *(float*)(buf + 0x10);
        
        //sensor type here int s = *(int*)(buf + 0x08);
        std::cout << x << ' ' << y << ' ' << z << std::endl;

        float mag = sqrtf(x * x + y * y + z * z);
        float xn = x / mag;
        float yn = y / mag;
        float zn = z / mag;

        std::cout << xn << ' ' << yn << ' ' << zn << ' ' << mag << std::endl;

        ofs.write(buf, 0x8); // write timestamp
        ofs.write((char*)&mag,4);
        ofs.write((char*)&xn, 4);
        ofs.write((char*)&yn, 4);
        ofs.write((char*)&zn, 4);
        
    }
}

int main()
{
    

    extractFields();
    //normalizeFields();

    //char c;
    //std::cin >> c;
    //ofs.write(buf, 104);
    return 0;
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
