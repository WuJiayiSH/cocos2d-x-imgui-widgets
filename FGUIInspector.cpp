#include "cocos2d.h"
#include "FairyGUI.h"
#include "imgui/imgui.h"

using namespace cocos2d;
using namespace fairygui;
using namespace std;

namespace CCImGuiWidgets
{
    namespace
    {
        cocos2d::WeakPtr<GObject> selectedObject = nullptr;

        char queryString[128] = "";

        bool queryMatchCase = true;

        void DrawObject(GObject *object)
        {
            GComponent *component = dynamic_cast<GComponent *>(object);
            string name = object->name;
            if (PackageItem *packageItem = object->getPackageItem())
            {
                size_t length = packageItem->name.length();
                if (length)
                {
                    if (name.empty())
                    {
                        name.reserve(2 + length);
                        name.append("[");
                    }
                    else
                    {
                        name.reserve(name.size() + 3 + length);
                        name.append(" [");
                    }

                    name.append(packageItem->name);
                    name.append("]");
                }
            }

            if (GRoot *root = dynamic_cast<GRoot *>(object))
            {
                if (name.empty())
                {
                    name = "<ROOT>";
                }
                else
                {
                    const char postfix[] = " <ROOT>";
                    name.reserve(name.size() + sizeof(postfix));
                    name.append(postfix);
                }
            }

            if (strlen(queryString) > 0)
            {
                size_t index;
                if (queryMatchCase)
                {
                    index = name.find(queryString);
                }
                else
                {
                    string nameLower;
                    nameLower.resize(name.size());
                    transform(name.begin(), name.end(), nameLower.begin(), ::tolower);

                    string queryStringLower;
                    queryStringLower.resize(strlen(queryString));
                    transform(queryString, queryString + queryStringLower.size(), queryStringLower.begin(), ::tolower);

                    index = nameLower.find(queryStringLower);
                }

                if (index != string::npos)
                {
                    ImGui::TreeNodeEx(
                        (void *)(intptr_t)object,
                        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | (selectedObject == object ? ImGuiTreeNodeFlags_Selected : 0),
                        name.c_str());

                    if (ImGui::IsItemClicked())
                        selectedObject = object;
                }

                if (component && component->numChildren() > 0)
                {
                    auto children = component->getChildren();
                    for (GObject *child : children)
                    {
                        DrawObject(child);
                    }
                }
                return;
            }

            if (component && component->numChildren() > 0)
            {
                bool ok = ImGui::TreeNodeEx(
                    (void *)(intptr_t)object,
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (selectedObject == object ? ImGuiTreeNodeFlags_Selected : 0),
                    name.c_str());

                if (ImGui::IsItemClicked())
                    selectedObject = object;

                if (ok)
                {
                    auto children = component->getChildren();
                    for (GObject *child : children)
                    {
                        DrawObject(child);
                    }
                    ImGui::TreePop();
                }
            }
            else
            {
                ImGui::TreeNodeEx(
                    (void *)(intptr_t)object,
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | (selectedObject == object ? ImGuiTreeNodeFlags_Selected : 0),
                    name.c_str());

                if (ImGui::IsItemClicked())
                    selectedObject = object;
            }
        }

        void DrawObjectProperties()
        {
            if (selectedObject)
            {
                GObject *object = selectedObject;
                bool b = false;
                int i = 0, j = 0;
                float v[4];

                if (ImGui::BeginTabBar("Object Properties", ImGuiTabBarFlags_None))
                {
                    if (ImGui::BeginTabItem("Object"))
                    {
                        v[0] = object->getX();
                        v[1] = object->getY();
                        if (ImGui::DragFloat2("Position", v, 1.0f))
                            object->setPosition(v[0], v[1]);

                        v[0] = object->getWidth();
                        v[1] = object->getHeight();
                        if (ImGui::DragFloat2("Size", v, 1.0f))
                            object->setSize(v[0], v[1]);

                        v[0] = object->getPivot().x;
                        v[1] = object->getPivot().y;
                        if (ImGui::DragFloat2("Pivot", v, 0.01f))
                            object->setPivot(v[0], v[1], object->isPivotAsAnchor());

                        b = object->isPivotAsAnchor();
                        if (ImGui::Checkbox("Is Pivot As Anchor", &b))
                        {
                            const cocos2d::Vec2 &pivot = object->getPivot();
                            object->setPivot(pivot.x, pivot.y, b);
                        }

                        v[0] = object->getScaleX();
                        v[1] = object->getScaleY();
                        if (ImGui::DragFloat2("Scale", v, 0.01f))
                            object->setScale(v[0], v[1]);

                        v[0] = object->getSkewX();
                        v[1] = object->getSkewY();
                        if (ImGui::DragFloat2("Skew", v, 0.01f))
                        {
                            object->setSkewX(v[0]);
                            object->setSkewY(v[1]);
                        }

                        v[0] = object->getRotation();
                        if (ImGui::DragFloat("Rotation", v, 1.0f))
                            object->setRotation(v[0]);

                         v[0] = object->getAlpha();
                        if (ImGui::DragFloat("Alpha", v, 0.01f))
                            object->setAlpha(v[0]);

                        i = object->getSortingOrder();
                        if (ImGui::DragInt("SortingOrder", &i))
                            object->setSortingOrder(i);

                        b = object->isVisible();
                        if (ImGui::Checkbox("Visible", &b))
                            object->setVisible(b);

                        b = object->isGrayed();
                        if (ImGui::Checkbox("Grayed", &b))
                            object->setGrayed(b);

                        b = object->isTouchable();
                        if (ImGui::Checkbox("Touchable", &b))
                            object->setTouchable(b);

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
            }
        }
    }

    void ShowFGUIInspector(bool *open)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 615), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("FGUIInspector", open))
        {
            ImGui::InputTextWithHint("", "Search Object...", queryString, IM_ARRAYSIZE(queryString));
            ImGui::SameLine();
            if (ImGui::Button("X"))
            {
                queryString[0] = '\0';
            }
            ImGui::SameLine();
            ImGui::Checkbox("Match Case", &queryMatchCase);

            ImGui::BeginChild("Object Tree", ImVec2(0, 250), true);
            if (GRoot *root = GRoot::getInstance())
            {
                DrawObject(root);
            }
            ImGui::EndChild();

            DrawObjectProperties();
        }
        ImGui::End();
    }
}
