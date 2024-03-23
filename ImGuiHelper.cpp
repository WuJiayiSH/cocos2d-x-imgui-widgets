#include "ImGuiHelper.h"
#include "imgui/imgui.h"
#include <string>

namespace CCImWidgets
{
    namespace
    {
        static size_t s_menuDepth = 0;
    }

    bool ImGuiHelper::BeginMenu(const char* name)
    {
		IM_ASSERT(s_menuDepth == 0);

        const char* start = name;
        const char* end = strchr(start, '/');

        bool isMenuOpen = true;
        while (end && isMenuOpen)
        {
            std::string menuName(start, end - start);
            if (ImGui::BeginMenu(menuName.c_str()))
            {
                s_menuDepth++;
                start = end + 1;
                end = strchr(start, '/');
            }
            else
            {
                isMenuOpen = false;
            }
        }

        if (isMenuOpen && strlen(start) != 0)
        {
            if (ImGui::BeginMenu(start))
            {
                s_menuDepth++;
            }
            else
            {
                isMenuOpen = false;
            }
        }

        
        if (isMenuOpen)
        {
            return true;
        }
        else
        {
            ImGuiHelper::EndMenu();
            return false;
        }
    }

    void ImGuiHelper::EndMenu()
    {
        while (s_menuDepth > 0)
        {
            ImGui::EndMenu();
			s_menuDepth--;
        }
    }
}
