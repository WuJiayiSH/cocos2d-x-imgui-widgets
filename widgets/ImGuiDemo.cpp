#include "ImGuiDemo.h"
#include "WidgetFactory.h"
#include "imgui/imgui.h"

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
            "ImGui Demo",
            static_cast<uint32_t>(WidgetFlag::UNIQUE)
        );
    }
}


