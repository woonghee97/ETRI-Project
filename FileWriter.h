#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>

class FileWriter {
public:
    FileWriter();
    ~FileWriter();
    void writeTxt(const std::string& info);
    // std::ofstream outFile_;
private:
    std::string filePath_;
    std::string generateFileName();
};
