#include "CCImGuiNodeProperties.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"

namespace CCImGuiWidgets
{
    void ImGuiNodeProperties::draw()
    {
		bool open = true;
         if (ImGui::Begin("Node Properties", &open))
        {
            
        }
        ImGui::End();
    }

    static CCImGuiWidgets::ImGuiWidgetManager::AutoRegister<CCImGuiWidgets::ImGuiNodeProperties> s_imGuiNodePropertiesRegister(
        "CCImGuiWidgets.ImGuiNodeProperties",
        "Node Properties",
        {}
    );
}


