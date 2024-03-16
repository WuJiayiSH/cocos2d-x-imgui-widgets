#ifndef __CCIMWIDGETS_HELPER_H__
#define __CCIMWIDGETS_HELPER_H__

#include <string>
#include <functional>

namespace CCImWidgets
{
    class Helper
    {
    public:
        static void drawMenuItem(const std::string& displayName, const std::function<void()> callback);
    };
}

#endif