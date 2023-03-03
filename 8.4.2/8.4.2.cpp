#include <iostream>
#include <fstream>
#include "SOLID.hpp"

int main() {

    std::string Hi="Hello world";
    Data data(Hi,Data::Format::kHTML);
    std::ofstream fout("SOLID.txt");
    saveToAsHTML(fout, data);
    
    return 0;
}