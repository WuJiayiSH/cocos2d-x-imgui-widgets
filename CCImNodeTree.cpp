#include "CCImGuiNodeTree.h"
#include "CCImGuiWidgetManager.h"
#include "CCIMGUI.h"
#include "cocos2d.h"

using namespace cocos2d;

namespace CCImGuiWidgets
{
    namespace
    {
        static Node* s_selectedNode = nullptr;

        void drawNode(Node* node)
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
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (s_selectedNode == node ? ImGuiTreeNodeFlags_Selected : 0),
                    "%s",
                    name.c_str()
                );

                if (ImGui::IsItemClicked())
                    s_selectedNode = node;

                if (ok)
                {
                    auto children = node->getChildren();
                    for (Node* child : children)
                    {
                        drawNode(child);
                    }
                    ImGui::TreePop();
                }
            }
            else
            {
                ImGui::TreeNodeEx(
                    (void*)(intptr_t)node,
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | (s_selectedNode == node ? ImGuiTreeNodeFlags_Selected : 0),
                    "%s",
                    name.c_str()
                );

                if (ImGui::IsItemClicked())
                    s_selectedNode = node;
            }
        }
    }

    void CCImGuiNodeTree::draw()
    {
        if (ImGui::Begin("Node Tree", &_visible))
        {
            static const std::string path = "CCImGuiWidgets.ImGuiNodeTree.SelectedNode";
            s_selectedNode = dynamic_cast<Node*>(CCImWidgetManager::getInstance()->getUserObject(path));
            drawNode(Director::getInstance()->getRunningScene());
            CCImWidgetManager::getInstance()->setUserObject(path, s_selectedNode);
        }
        ImGui::End();
    }

    static CCImWidgetManager::CCImWidgetRegister<CCImNodeTree> s_CCImNodeTreeRegister(
        "CCImGuiWidgets.ImGuiNodeTree",
        "Node Tree",
        {}
    );
}


