#include "task.h"

//очень нужная функция, в том числе и в mainwindow
bool compare(const vertex_smpt& first, const vertex_smpt& second)
{
    if(first->getName().mid(3).toInt() > second->getName().mid(3).toInt())
        return false;
    return true;
}
