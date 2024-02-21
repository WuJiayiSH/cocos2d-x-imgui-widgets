#include "CCImGuiWidget.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"

namespace CCImGuiWidgets
{
    void ImGuiWidget::onLoad()
    {
        CCIMGUI::getInstance()->addCallback([this]()
        {
            draw();
        }, getName());
    }

    void ImGuiWidget::onUnload()
    {
        CCIMGUI::getInstance()->removeCallback(getName());
    }
}


