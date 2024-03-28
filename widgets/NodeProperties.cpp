#include "NodeProperties.h"
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
    void NodeProperties::draw(bool* open)
    {
        if (ImGui::Begin(getWindowName().c_str(), open))
        {
            if (cocos2d::Node* node = dynamic_cast<cocos2d::Node*>(Editor::getInstance()->getUserObject("CCImGuiWidgets.NodeTree.SelectedNode")))
            {
                if (NodeVisitor* visitor = static_cast<NodeVisitor*>(node->getComponent("CCImWidgets.NodeVisitor")))
                {
                    visitor->visit();
                }
            }
        }

        ImGui::End();
    }

    namespace
    {
        static WidgetFactory::AutoRegister<NodeProperties> s_register(
            "CCImWidgets.NodeProperties",
            "Node Properties"
        );
    }
}


