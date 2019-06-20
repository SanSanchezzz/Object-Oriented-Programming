#include "file.h"
#include <QDebug>
File initFile()
{
    File file;

    file.action = READFILE;
    file.file = nullptr;

    return file;
}

ERROR openFile(File &f, char *filename, const char action)
{
    ERROR result = ERROR::OK;

    if (action != 'w' && action != 'r')
    {
        result = INCORRECT_DATA;
        return result;
    }

    f.file = filename;

    if (action == 'w')
    {
        f.f_out.open(f.file);
        f.action = WRITEFILE;
    }

    if (action == 'r')
    {
        f.f_in.open(f.file);
        f.action = READFILE;
    }

    return result;
}

bool isOpen(File &f)
{
    bool result = false;

    if ((f.action != READFILE) && (f.action != WRITEFILE))
    {
        return result;
    }

    if (f.action == WRITEFILE)
    {
        result = f.f_out.is_open();
    }

    if (f.action == READFILE)
    {
        result = f.f_in.is_open();
    }

    return result;
}

ERROR closeFile(File &f)
{
    ERROR result = OK;

    if ((f.action != READFILE) && (f.action != WRITEFILE))
    {
        result = INCORRECT_DATA;
        return result;
    }

    if (f.action == WRITEFILE)
    {
       f.f_out.close();
    }

    if (f.action == READFILE)
    {
        f.f_in.close();
    }

    return result;
}

ERROR readData(double &data, File &f)
{
    ERROR result = OK;

    f.f_in >> data;

    if (f.f_in.fail() == 1)
    {
        qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
        result = INCORRECT_DATA;
    }

    return result;
}

ERROR readData(unsigned &data, File &f)
{
    ERROR result = OK;

    f.f_in >> data;

    if (f.f_in.fail() == 1)
    {
        qDebug() << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << data;
        result = INCORRECT_DATA;
    }

    return result;
}

ERROR readData(unsigned short &data, File &f)
{
    ERROR result = OK;

    f.f_in >> data;

    if (f.f_in.fail() == 1)
    {
        result = INCORRECT_DATA;
    }

    return result;
}

ERROR writeData(File &f, double &data)
{
    ERROR result = OK;

    f.f_out << data;

    if (!f.f_out.good())
    {
        result = INCORRECT_DATA;
    }

    return result;
}
ERROR writeData(File &f, unsigned short &data)
{
    ERROR result = OK;

    f.f_out << data;

    if (!f.f_out.good())
    {
        result = INCORRECT_DATA;
    }

    return result;
}

ERROR writeData(File &f, unsigned &data)
{
    ERROR result = OK;

    f.f_out << data;

    if (!f.f_out.good())
    {
        result = INCORRECT_DATA;
    }

    return result;
}

ERROR writeData(File &f, const char *data)
{
    ERROR er = OK;

    f.f_out << data;

    if (!f.f_out.good())
    {
        er = INCORRECT_DATA;
    }

    return er;
}
