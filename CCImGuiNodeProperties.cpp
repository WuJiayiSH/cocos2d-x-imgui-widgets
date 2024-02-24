#include "CCImGuiNodeProperties.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"
#include "cocos2d.h"
#include "CCImGuiPropertyRenderer.h"

using namespace cocos2d;
using namespace std;

namespace CCImGuiWidgets
{
	template<typename LambdaType>
	using LambdaSignature = decltype(&LambdaType::operator());

	template<typename LambdaType>
	LambdaSignature<LambdaType>* optional_override(const LambdaType& fp) {
		return fp;
	}

    void ImGuiNodeProperties::draw()
    {
		bool open = true;
         if (ImGui::Begin("Node Properties", &open))
        {
					if (Node* node = dynamic_cast<Node*>(ImGuiWidgetManager::getInstance()->getHandle("CCImGuiWidgets.ImGuiNodeTree.SelectedNode")))
					{

						
						ImGuiNodeProcessor::getInstance()->render(node);
						
					}
        }
        ImGui::End();
    }

    static CCImGuiWidgets::ImGuiWidgetManager::WidgetRegister<CCImGuiWidgets::ImGuiNodeProperties> s_imGuiNodePropertiesRegister(
        "CCImGuiWidgets.ImGuiNodeProperties",
        "Node Properties",
        {}
    );
}


