#include "Editor.h"
#include "NodeFactory.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"

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
    }

    Editor::Editor()
    {
        CCIMGUI::getInstance()->addCallback(std::bind(&Editor::draw, this), "Editor");
    }
    
    Editor::~Editor()
    {
        CCIMGUI::getInstance()->removeCallback("Editor");
    }

    Editor* Editor::getInstance()
    {
        static Editor* instance = new Editor();
        return instance;
    }

    void Editor::draw()
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


