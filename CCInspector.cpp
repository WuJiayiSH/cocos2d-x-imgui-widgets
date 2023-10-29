#include "cocos2d.h"
#include "imgui/imgui.h"

using namespace cocos2d;
using namespace std;

namespace CCImGuiWidgets
{
    namespace
    {
        WeakPtr<Node> selectedNode = nullptr;

        char queryString[128] = "";

        bool queryMatchCase = true;

        void DrawNode(Node* node)
        {
            const string& desc = node->getDescription();
            string name = desc.substr(1, desc.find(' '));
            size_t length = node->getName().length();
            if (length)
            {
                name.reserve(name.size() + 2 + length);
                name.append("- ");
                name.append(node->getName());
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
                        (void*)(intptr_t)node,
                        ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | (selectedNode == node ? ImGuiTreeNodeFlags_Selected : 0),
                        name.c_str()
                    );

                    if (ImGui::IsItemClicked())
                        selectedNode = node;
                }
                
                auto children = node->getChildren();
                for (Node* child : children)
                {
                    DrawNode(child);
                }
                return;
            }

            if (node->getChildrenCount())
            {
                bool ok = ImGui::TreeNodeEx(
                    (void*)(intptr_t)node,
                    ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (selectedNode == node ? ImGuiTreeNodeFlags_Selected : 0),
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
                    name.c_str()
                );

                if (ImGui::IsItemClicked())
                    selectedNode = node;
            }
        }

        void DrawNodeProperties()
        {
            if (selectedNode)
            {
                Node* node = selectedNode;
                
                bool b = false;
                int i = 0, j = 0;
                float v[4];

                if (ImGui::BeginTabBar("Node Properties", ImGuiTabBarFlags_None))
                {
                    if (ImGui::BeginTabItem("2D"))
                    {
                        v[0] = node->getPositionX();
                        v[1] = node->getPositionY();
                        if (ImGui::DragFloat2("Position", v, 1.0f))
                            node->setPosition(v[0], v[1]);

                        v[0] = node->getContentSize().width;
                        v[1] = node->getContentSize().height;
                        if (ImGui::DragFloat2("Content Size", v, 1.0f))
                            node->setContentSize(Size(v[0], v[1]));

                        v[0] = node->getAnchorPoint().x;
                        v[1] = node->getAnchorPoint().y;
                        if (ImGui::DragFloat2("Anchor Point", v, 0.01f))
                            node->setAnchorPoint(Vec2(v[0], v[1]));

                        v[0] = node->getScaleX();
                        v[1] = node->getScaleY();
                        if (ImGui::DragFloat2("Scale", v, 0.01f))
                            node->setScale(v[0], v[1]);

                        v[0] = node->getRotation();
                        if (ImGui::DragFloat("Rotation", v, 1.0f))
                            node->setRotation(v[0]);

                        v[0] = node->getSkewX();
                        v[1] = node->getSkewY();
                        if (ImGui::DragFloat2("Skew", v, 0.1f))
                        {
                            node->setSkewX(v[0]);
                            node->setSkewY(v[1]);
                        }

                        i = node->getTag();
                        if (ImGui::DragInt("Tag", &i))
                            node->setTag(i);

                        i = node->getLocalZOrder();
                        if (ImGui::DragInt("Z Order", &i))
                            node->setLocalZOrder(i);

                        b = node->isVisible();
                        if (ImGui::Checkbox("Visible", &b))
                            node->setVisible(b);

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("3D"))
                    {
                        v[0] = node->getPositionX();
                        v[1] = node->getPositionY();
                        v[2] = node->getPositionZ();
                        if (ImGui::DragFloat3("Position", v, 1.0f))
                            node->setPosition3D(Vec3(v[0], v[1], v[2]));

                        v[0] = node->getScaleX();
                        v[1] = node->getScaleY();
                        v[2] = node->getScaleZ();
                        if (ImGui::DragFloat3("Scale", v, 0.01f))
                        {
                            node->setScaleX(v[0]);
                            node->setScaleY(v[1]);
                            node->setScaleZ(v[2]);
                        }

                        Vec3 rot = node->getRotation3D();
                        v[0] = rot.x;
                        v[1] = rot.y;
                        v[2] = rot.z;
                        if (ImGui::DragFloat3("Rotation", v, 1.0f))
                        {
                            rot.x = v[0];
                            rot.y = v[1];
                            rot.z = v[2];
                            node->setRotation3D(rot);
                        }

                        i = node->getTag();
                        if (ImGui::DragInt("Tag", &i))
                            node->setTag(i);

                        i = node->getLocalZOrder();
                        if (ImGui::DragInt("Z Order", &i))
                            node->setLocalZOrder(i);

                        b = node->isVisible();
                        if (ImGui::Checkbox("Visible", &b))
                            node->setVisible(b);

                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Color"))
                    {
                        Color3B color = node->getColor();
                        v[0] = color.r / 255.0f;
                        v[1] = color.g / 255.0f;
                        v[2] = color.b / 255.0f;
                        v[3] = node->getOpacity() / 255.0f;
                        if (ImGui::ColorEdit4("Color", v))
                        {
                            color.r = static_cast<GLubyte>(v[0] * 255);
                            color.g = static_cast<GLubyte>(v[1] * 255);
                            color.b = static_cast<GLubyte>(v[2] * 255);
                            node->setColor(color);
                            node->setOpacity(static_cast<GLubyte>(v[3] * 255));
                        }
                        
                        BlendProtocol* blendNode = dynamic_cast<BlendProtocol*>(node);
                        if (blendNode)
                        {
                            const char* factorItems[] = {
                                "ZERO",
                                "ONE",
                                "SRC_COLOR",
                                "ONE_MINUS_SRC_COLOR",
                                "SRC_ALPHA",
                                "ONE_MINUS_SRC_ALPHA",
                                "DST_COLOR",
                                "ONE_MINUS_DST_COLOR",
                                "DST_ALPHA",
                                "ONE_MINUS_DST_ALPHA"
                            };

                            const GLenum factors[] = {
                                GL_ZERO,
                                GL_ONE,
                                GL_SRC_COLOR,
                                GL_ONE_MINUS_SRC_COLOR,
                                GL_SRC_ALPHA,
                                GL_ONE_MINUS_SRC_ALPHA,
                                GL_DST_COLOR,
                                GL_ONE_MINUS_DST_COLOR,
                                GL_DST_ALPHA,
                                GL_ONE_MINUS_DST_ALPHA
                            };

                            BlendFunc blendFunc = blendNode->getBlendFunc();
                            i = distance(factors, find(begin(factors), end(factors), blendFunc.src));
                            j = distance(factors, find(begin(factors), end(factors), blendFunc.dst));
                            if (ImGui::Combo("Blend Src", &i, factorItems, IM_ARRAYSIZE(factorItems)) ||
                                ImGui::Combo("Blend Dst", &j, factorItems, IM_ARRAYSIZE(factorItems))
                                )
                            {
                                blendFunc.src = factors[i];
                                blendFunc.dst = factors[j];
                                blendNode->setBlendFunc(blendFunc);
                            }
                        }

                        b = node->isCascadeColorEnabled();
                        if (ImGui::Checkbox("Cascade Color Enabled", &b))
                            node->setCascadeColorEnabled(b);

                        b = node->isCascadeOpacityEnabled();
                        if (ImGui::Checkbox("Cascade Opacity Enabled", &b))
                            node->setCascadeOpacityEnabled(b);

                        b = node->isOpacityModifyRGB();
                        if (ImGui::Checkbox("Is Opacity Modify RGB", &b))
                            node->setOpacityModifyRGB(b);

                        ImGui::EndTabItem();
                    }
                    
                    ImGui::EndTabBar();
                }
            }
        }
    }

    void ShowInspector(bool* open)
    {
        ImGui::SetNextWindowSize(ImVec2(400, 575), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Inspector", open))
        {
            ImGui::InputTextWithHint("", "Search Node...", queryString, IM_ARRAYSIZE(queryString));
            ImGui::SameLine();
            if (ImGui::Button("X"))
            {
                queryString[0] = '\0';
            }
            ImGui::SameLine();
            ImGui::Checkbox("Match Case", &queryMatchCase);

            ImGui::BeginChild("Node Tree", ImVec2(0, 250), true);
            DrawNode(Director::getInstance()->getRunningScene());
            ImGui::EndChild();

            DrawNodeProperties();
        }
        ImGui::End();
    }
}
