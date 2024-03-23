#include "Editor.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "CCImGuiLayer.h"
#include "ImGuiHelper.h"

namespace CCImWidgets
{
    namespace
    {
        void drawDockSpace()
        {
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("CCImWidgets.Editor", nullptr, windowFlags);
            ImGui::PopStyleVar(3);

            ImGuiID dockspaceId = ImGui::GetID("CCImWidgets.Editor");
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Widget"))
                {
                    const std::unordered_map<std::string, WidgetFactory::Creator>& creators = WidgetFactory::getInstance()->getCreators();
                    for (const std::pair<std::string, WidgetFactory::Creator>& pair : creators)
                    {
                        const WidgetFactory::Creator& creator = pair.second;
                        const std::string& displayName = creator.getDisplayName();
                        const size_t lastSlash = displayName.find_last_of('/');
                        
						bool isMenuOpen = true;
						if (lastSlash != std::string::npos)
							isMenuOpen = ImGuiHelper::BeginMenu(displayName.substr(0, lastSlash).c_str());

						if (isMenuOpen)
						{
							if (ImGui::MenuItem(displayName.c_str() + (lastSlash != std::string::npos ? lastSlash + 1 : 0)))
							{
                                const std::string& name = creator.getName();
								Widget* lastWidget = Editor::getInstance()->getWidgetByName(name);
                                if (lastWidget == nullptr || !lastWidget->isUnique())
                                {
                                    if (Widget* widget = WidgetFactory::getInstance()->createWidget(name))
                                    {
                                        Editor::getInstance()->addWidget(widget);
                                    }
                                }
							}
						}

						if (lastSlash != std::string::npos)
                            ImGuiHelper::EndMenu();
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

        if (!CCIMGUI::getInstance())
            return false;

        ImGuiLayer* layer = ImGuiLayer::create();
        if (!layer)
            return false;

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        setLocalZOrder(INT_MAX);
        addChild(layer, INT_MAX, "ImGuiLayer");
		return true;
    }

    void Editor::onEnter()
    {
        Node::onEnter();

        CCIMGUI::getInstance()->addCallback(std::bind(&Editor::callback, this), "CCImWidgets.Editor");
		scheduleUpdate();
    }

    void Editor::onExit()
    {
        Node::onExit();

        CCIMGUI::getInstance()->removeCallback("CCImWidgets.Editor");
        unscheduleUpdate();
    }

    void Editor::callback()
    {
        drawDockSpace();

        for(cocos2d::RefPtr<Widget>& widget : _widgets)
        {
            if (!widget)
                continue;

            bool open = true;
            widget->draw(&open);

            if (!open)
                widget = nullptr;
        }
    }

    void Editor::update(float dt)
    {
        Node::update(dt);

        _widgets.erase(std::remove(_widgets.begin(), _widgets.end(), nullptr), _widgets.end());
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

    Widget* Editor::getWidgetByName(const std::string& name) const
    {
        for(Widget* widget : _widgets)
        {
            if (!widget)
                continue;

            if (widget->getName() == name)
                return widget;
        }

        return nullptr;
    }
}


