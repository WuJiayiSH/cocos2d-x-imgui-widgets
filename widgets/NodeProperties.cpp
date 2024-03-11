#include "NodeProperties.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "cocos2d.h"
#include "PropertyRenderer.h"
#include "Editor.h"

using namespace cocos2d;
using namespace std;

namespace CCImWidgets
{
    void NodeProperties::draw()
    {
        if (Node* node = dynamic_cast<Node*>(Editor::getInstance()->getUserObject("CCImGuiWidgets.NodeTree.SelectedNode")))
        {
            
        }
    }

    namespace
    {
        static WidgetFactory::AutoRegister<NodeProperties> s_register(
            "CCImWidgets.NodeProperties",
            "Built-in/Node Properties"
        );
    }
}


