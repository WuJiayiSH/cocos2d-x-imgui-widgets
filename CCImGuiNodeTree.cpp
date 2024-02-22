#include "CCImGuiNodeTree.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"

namespace CCImGuiWidgets
{
    void ImGuiNodeTree::draw()
    {
		bool open = true;
         if (ImGui::Begin("Node Tree", &open))
        {
            
        }
        ImGui::End();
    }

    static CCImGuiWidgets::ImGuiWidgetManager::AutoRegister<CCImGuiWidgets::ImGuiNodeTree> s_imGuiNodeTreeRegister(
        "CCImGuiWidgets.ImGuiNodeTree",
        "Node Tree",
        {}
    );
}


