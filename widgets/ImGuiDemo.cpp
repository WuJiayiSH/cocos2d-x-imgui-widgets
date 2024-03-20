#include "ImGuiDemo.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "cocos2d.h"
#include "PropertyRenderer.h"
#include "Editor.h"
#include "NodeVisitor.h"
using namespace cocos2d;
using namespace std;

namespace CCImWidgets
{
    void ImGuiDemo::draw(bool* open)
    {
        ImGui::ShowDemoWindow(open);
    }

    namespace
    {
        static WidgetFactory::AutoRegister<ImGuiDemo> s_register(
            "CCImWidgets.ImGuiDemo",
            "Built-in/ImGui Demo"
        );
    }
}


