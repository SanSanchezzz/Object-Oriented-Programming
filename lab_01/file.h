#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
//#include "errors.h"
#include "types.h"
#include <string.h>

#define READFILE  1
#define WRITEFILE 2

struct File
{
    std::ifstream f_in;
    std::ofstream f_out;

    int action;

    char *file;
};

File initFile();
ERROR openFile(File &f, char *filename, const char action);
bool isOpen(File &f);
ERROR closeFile(File &f);
ERROR readData(double &data, File &f);
ERROR readData(unsigned &data, File &f);
ERROR readData(unsigned short &data, File &f);
ERROR writeData(File &f, double &data);
ERROR writeData(File &f, unsigned &data);
ERROR writeData(File &f, unsigned short &data);
ERROR writeData(File &f, const char *data);

#endif // FILE_H
