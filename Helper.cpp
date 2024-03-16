#include "Helper.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    void Helper::drawMenuItem(const std::string& displayName, const std::function<void()> callback)
    {
        size_t start = 0;
        size_t end = displayName.find("/", start);

        size_t depth = 0;
        bool isMenuOpened = true;
        while (end != std::string::npos && isMenuOpened)
        {
            if (ImGui::BeginMenu(displayName.substr(start, end).c_str()))
            {
                depth++;
                start = end + 1;
                end = displayName.find("/", start);
            }
            else
            {
                isMenuOpened = false;
            }
        }
        
        if (isMenuOpened)
        {
            if (ImGui::MenuItem(displayName.substr(start).c_str()))
            {
                callback();
            }
        }

        while (depth-- > 0)
        {
            ImGui::EndMenu();
        }
    }
}
