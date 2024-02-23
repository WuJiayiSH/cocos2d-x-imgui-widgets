#include "CCImGuiNodeTree.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace CCImGuiWidgets
{
	namespace
	{
		Node* selectedNode = nullptr;
		const std::string pathSelectedNode = "CCImGuiWidgets.ImGuiNodeTree.SelectedNode";

		void DrawNode(Node* node)
		{
			

			const std::string& desc = node->getDescription();
			std::string name = desc.substr(1, desc.find(' '));
			size_t length = node->getName().length();
			if (length)
			{
				name.reserve(name.size() + 2 + length);
				name.append("- ");
				name.append(node->getName());
			}

			if (node->getChildrenCount())
			{
				bool ok = ImGui::TreeNodeEx(
					(void*)(intptr_t)node,
					ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (selectedNode == node ? ImGuiTreeNodeFlags_Selected : 0),
					"%s",
					name.c_str()
				);

				if (ImGui::IsItemClicked())
					selectedNode = node;

				if (ok)
				{
					auto children = node->getChildren();
					for (Node* child : children)
					{
						DrawNode(child);
					}
					ImGui::TreePop();
				}
			}
			else
			{
				ImGui::TreeNodeEx(
					(void*)(intptr_t)node,
					ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | (selectedNode == node ? ImGuiTreeNodeFlags_Selected : 0),
					"%s",
					name.c_str()
				);

				if (ImGui::IsItemClicked())
					selectedNode = node;
			}

			
		}

		
	}

    void ImGuiNodeTree::draw()
    {
		bool open = true;
         if (ImGui::Begin("Node Tree", &open))
        {
			 
			 selectedNode = dynamic_cast<Node*>(ImGuiWidgetManager::getInstance()->getHandle(pathSelectedNode));
			 DrawNode(Director::getInstance()->getRunningScene());

			 ImGuiWidgetManager::getInstance()->setHandle(pathSelectedNode, selectedNode);
        }
        ImGui::End();
    }

    static CCImGuiWidgets::ImGuiWidgetManager::AutoRegister<CCImGuiWidgets::ImGuiNodeTree> s_imGuiNodeTreeRegister(
        "CCImGuiWidgets.ImGuiNodeTree",
        "Node Tree",
        {}
    );
}


