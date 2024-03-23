#include "Widget.h"

namespace CCImWidgets
{
    bool Widget::init(const std::string& name, const std::string& windowName, uint32_t mask)
    {
        _name = name;
        _windowName = windowName;
        _mask = mask;
        return true;
    }
}
