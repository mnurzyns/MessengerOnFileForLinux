#pragma once
#include<memory>
#include<vector>
#include<string>
#include<fstream>


namespace FileInterface
{
    namespace Modification
    {
        bool addRow(const std::string& pathToFile, const std::string& text);
        bool removeRow(const std::string& pathToFile, const std::string& pattern);
        //std::unique_ptr<std::string> removeRowField(const std::string& row, const int fieldNumber);
        bool updateRow(const std::string& pathToFile, const std::string& newRow, const std::string& where);
        bool updateRowField(const std::string& pathToFile, const std::string& where, const std::string& newField, const int fieldNumber);

    }

    namespace Accesor
    {
        std::unique_ptr<std::vector<std::string>> getFilenamesFromFolder(const std::string& pathToDir);
        std::unique_ptr<std::string> getFolderName(const std::string& pathToFile);
        std::unique_ptr<std::string> getRowField(const std::string& field, const int fieldNumber);
        std::unique_ptr<std::vector<std::string>> getFileContent(const std::string& pathToFile);
    }

    namespace Managment
    {
        bool createFile(const std::string& pathToFile);
        bool removeFile(const std::string& pathToFile);
        bool isFileExist(const std::string& pathToFile);
    }
}

/** wrzucic to gdzie indzie*/
namespace ConsolControl
{
    std::string getStdoutFromCommand(std::string cmd);
}


