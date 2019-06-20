#ifndef TYPES_H
#define TYPES_H

const int MAX_LENGHT_STRING = 64;

enum USER_ACTION
{
    LOADMODEL = 0,
    SAVEMODEL,
    TRANSPORT,
    SCALE,
    ROTATE,
    QUIT
};

enum RESPONSE_ACTION
{
    RENDER_ACTION,
    ERROR_ACTION
};

enum ERROR
{
    OK = 0,
    INCORRECT_FILE = -1,
    INCORRECT_DATA = -2,
    FIGURE_NOT_LOADED = -3
};

namespace errorMessege
{
    const char incorrect_data[MAX_LENGHT_STRING] = "Файл содержит некорректные данные";
    const char incorrect_file[MAX_LENGHT_STRING] = "Файл повреждён";
    const char figure_not_loaded[MAX_LENGHT_STRING] = "Фигура не загружена";
}

#endif // TYPES_H
