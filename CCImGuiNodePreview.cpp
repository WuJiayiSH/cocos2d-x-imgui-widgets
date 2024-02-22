#include "CCImGuiNodePreview.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"

namespace CCImGuiWidgets
{
    void ImGuiNodePreview::draw()
    {
		bool open = true;
         if (ImGui::Begin("Preview", &open))
        {
            
        }
        ImGui::End();
    }

    static CCImGuiWidgets::ImGuiWidgetManager::AutoRegister<CCImGuiWidgets::ImGuiNodePreview> s_imGuiNodePreviewRegister(
        "CCImGuiWidgets.ImGuiNodePreview",
        "Preview",
        {}
    );
}


