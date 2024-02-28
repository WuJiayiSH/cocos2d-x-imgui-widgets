#include "CCImNodePreview.h"
#include "CCImWidgetManager.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    void CCImPreview::draw()
    {
        if (ImGui::Begin("Preview", &_visible))
        {
            
        }
        ImGui::End();
    }

    static CCImGuiWidgetManager::CCImWidgetRegister<CCImPreview> s_CCImPreviewRegister(
        "CCImGuiWidgets.CCImPreview",
        "Preview",
        {}
    );
}


