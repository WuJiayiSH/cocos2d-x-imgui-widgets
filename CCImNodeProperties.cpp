#include "CCImGuiNodeProperties.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"
#include "cocos2d.h"
#include "CCImGuiPropertyRenderer.h"

using namespace cocos2d;
using namespace std;

namespace CCImGuiWidgets
{
    void CCImNodeProperties::draw()
    {
		if (ImGui::Begin("Node Properties", &_visible))
        {
            if (Node* node = dynamic_cast<Node*>(ImGuiWidgetManager::getInstance()->getUserObject("CCImGuiWidgets.ImGuiNodeTree.SelectedNode")))
            {

                
                ImGuiNodeProcessor::getInstance()->render(node);
                
            }
        }
        ImGui::End();
    }

    static CCImGuiWidgetManager::CCImWidgetRegister<CCImNodeProperties> s_CCImNodePropertiesRegister(
        "CCImGuiWidgets.CCImNodeProperties",
        "Node Properties",
        {}
    );
}


