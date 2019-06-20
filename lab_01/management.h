#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <string.h>

#include "types.h"
#include "controller.h"
#include "process.h"

RESPONSE_ACTION handleProcessResult(char *messege, ERROR action);

ERROR management(controller_t &controller, USER_ACTION action);
ERROR manageTask(figure_t &figure, controller_t &controller, USER_ACTION action);
#endif // MANAGEMENT_H
