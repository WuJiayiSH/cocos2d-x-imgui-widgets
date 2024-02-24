#include "CCImGuiNodePreview.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"

namespace CCImGuiWidgets
{
    void ImGuiNodePreview::draw()
    {
        if (ImGui::Begin("Preview", &_visible))
        {
            
        }
        ImGui::End();
    }

    static CCImGuiWidgets::ImGuiWidgetManager::WidgetRegister<CCImGuiWidgets::ImGuiNodePreview> s_imGuiNodePreviewRegister(
        "CCImGuiWidgets.ImGuiNodePreview",
        "Preview",
        {}
    );
}


