#include "Editor.h"
#include "NodeFactory.h"
#include "WidgetFactory.h"
#include "WidgetManager.h"
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

        WidgetFactory::getInstance()->createWidget("CCImWidgets.NodeProperties");
        WidgetFactory::getInstance()->createWidget("CCImWidgets.NodeTree");
        WidgetFactory::getInstance()->createWidget("CCImWidgets.NodeTree");
        
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
        static bool open = true;;
        bool* p_open = &open;
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();

        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);



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
                    const WidgetFactory::WidgetCreator& creator = pair.second;
                    drawMenuItem(creator._displayName, [&creator]{
                        WidgetFactory::getInstance()->createWidget(creator._name);
					});
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        

        ImGui::End();

        
    }
}


