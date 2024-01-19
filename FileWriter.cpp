#include <rtabmap/core/FileWriter.h>
std::ofstream outFile_;

FileWriter::FileWriter() {
    std::string filePath = "/root/Documents/RTAB-Map/txtfolder/";

    // 현재 시간을 이용하여 파일 이름 생성
    std::string filename = generateFileName();

    outFile_.open(filePath + filename);

    if(!outFile_.is_open())
    {
        std::cerr << "Unable to open the file '" << filename << "' for writin+g." << std::endl;
    }
}

FileWriter::~FileWriter() {
    // 파일이 열려있으면 닫기
    if (outFile_.is_open()) 
    {
        outFile_.close();
    }
}

void FileWriter::writeTxt(const std::string& info) {
    // 파일에 정보 작성
    if (outFile_.is_open()) 
    {
        outFile_ << info << std::endl;
    } 
    else 
    {
        std::cout << "File is not open for writing." << std::endl;
    }
}

std::string FileWriter::generateFileName() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");
    return oss.str() + ".txt";
}
