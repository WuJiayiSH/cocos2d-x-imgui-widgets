#ifndef __CCIMWIDGETS_IMGUIHELPER_H__
#define __CCIMWIDGETS_IMGUIHELPER_H__

namespace CCImWidgets
{
    class ImGuiHelper
    {
    public:
        static bool BeginMenu(const char* name);
        static void EndMenu();
    };
}

#endif