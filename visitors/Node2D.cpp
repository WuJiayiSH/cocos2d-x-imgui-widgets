#include "Node2D.h"
#include "NodeFactory.h"
#include "cocos2d.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    namespace
    {
        bool create(cocos2d::Node** node)
        {
            
            if (!ImGui::IsPopupOpen("CCImWidgets.Node2D"))
                ImGui::OpenPopup("CCImWidgets.Node2D");

            bool result = false;
            if (ImGui::BeginPopupModal("CCImWidgets.Node2D", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
                {
					*node = cocos2d::Node::create();
                    result = true;
                }
                ImGui::EndPopup();
            }

			return result;
        }

        static NodeFactory::AutoRegister<Node2D> s_register(
            "CCImWidgets.Node2D",
            "2D/Node2D",
            create);
    }
}
