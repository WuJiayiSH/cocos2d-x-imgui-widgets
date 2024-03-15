#include "Editor.h"
#include "NodeFactory.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "CCImGuiLayer.h"

namespace CCImWidgets
{
    namespace
    {
        void drawMenuItem(const std::string& displayName, const std::function<void()> callback)
        {
            size_t start = 0;
            size_t end = displayName.find("/", start);

            size_t depth = 0;
            bool isMenuOpened = true;
            while (end != std::string::npos && isMenuOpened)
            {
                if (ImGui::BeginMenu(displayName.substr(start, end).c_str()))
                {
                    depth++;
                    start = end + 1;
                    end = displayName.find("/", start);
                }
                else
                {
                    isMenuOpened = false;
                }
            }
            
            if (isMenuOpened)
            {
                if (ImGui::MenuItem(displayName.substr(start).c_str()))
                {
					callback();
                }
            }

            while (depth-- > 0)
            {
                ImGui::EndMenu();
            }
        }

        void drawDockSpace()
        {
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            bool open = true;
            ImGui::Begin("CCImWidgets.Editor", &open, windowFlags);
            ImGui::PopStyleVar();
            
            ImGui::PopStyleVar(2);

            ImGuiID dockspaceId = ImGui::GetID("CCImWidgets.Editor.DockSpace");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Add"))
                {
                    for (const auto& pair : NodeFactory::getInstance()->getCreators())
                    {
                        const NodeFactory::NodeCreator& creator = pair.second;
                        drawMenuItem(creator._displayName, [&creator]{
                            NodeFactory::getInstance()->createNode(creator._name);
                        });
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Layout"))
                {
                    ImGui::EndMenu();
                }
                
                if (ImGui::BeginMenu("Widget"))
                {
                    for (const auto& pair : WidgetFactory::getInstance()->getCreators())
                    {
                        const WidgetFactory::Creator& creator = pair.second;
                        drawMenuItem(creator.getDisplayName(), [&creator]{
                            WidgetFactory::getInstance()->createWidget(creator.getName());
                        });
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            ImGui::End();
        }
    }

    Editor::Editor()
    {
    }
    
    Editor::~Editor()
    {
    }

    Editor* Editor::getInstance()
    {
        static cocos2d::RefPtr<Editor> instance = nullptr;

        if (!instance)
            instance = cocos2d::utils::createHelper(&Editor::init);

        return instance;
    }

    bool Editor::init()
    {
        if (!Node::init())
            return false;

        ImGuiLayer* layer = ImGuiLayer::create();
        if (!layer)
            return false;

        setName("EditorSupport");
        setLocalZOrder(INT_MAX);
        addChild(layer, INT_MAX, "ImGuiLayer");
		return true;
    }

    void Editor::onEnter()
    {
        Node::onEnter();
        CCIMGUI::getInstance()->addCallback(std::bind(&Editor::draw, this), "CCImWidgets.Editor");

        addWidget(WidgetFactory::getInstance()->createWidget("CCImWidgets.NodeProperties"));
        addWidget(WidgetFactory::getInstance()->createWidget("CCImWidgets.NodeTree"));
        addWidget(WidgetFactory::getInstance()->createWidget("CCImWidgets.Preview"));

		scheduleUpdate();
    }

    void Editor::onExit()
    {
        Node::onExit();
        CCIMGUI::getInstance()->removeCallback("CCImWidgets.Editor");
    }

    void Editor::draw()
    {
        drawDockSpace();

        for(cocos2d::RefPtr<Widget>& widget : _widgets)
        {
            if (!widget)
                continue;

            bool open = true;
            if (ImGui::Begin(widget->getDisplayName().c_str(), &open))
            {
                widget->draw();
            }
            ImGui::End();
        
            if (!open)
                widget = nullptr;
        }
    }

    void Editor::update(float dt)
    {
        Node::update(dt);

        _widgets.erase(std::remove(_widgets.begin(), _widgets.end(), nullptr));
        for(Widget* widget : _widgets)
        {
            if (widget)
                widget->update(dt);
        }
    }

    void Editor::addWidget(Widget* widget)
    {
        _widgets.push_back(widget);
    }
}


