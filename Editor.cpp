#include "Editor.h"
#include "NodeFactory.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "CCImGuiLayer.h"
#include "Helper.h"

namespace CCImWidgets
{
    namespace
    {
        size_t s_selectedSearthPathIndex = 0;

        void DrawNode(const std::string& path, const std::vector<std::string>& list)
        {
            cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
            for(size_t i = 2; i < list.size(); i++)
            {
				CCLOG("%s", list[i].c_str());
                size_t pos = list[i].find_last_of('/', list[i].size() - 2);
                std::string filename = list[i];
                if (pos != std::string::npos)
                {
                    filename = filename.substr(pos + 1);
                }
                
                if(fileUtils->isDirectoryExist(list[i]))
                {
                    bool ok;
                    const std::vector<std::string>& children = fileUtils->listFiles(list[i]);
                    if (children.size() > 2)
                    {
                        ok = ImGui::TreeNodeEx(
                            list[i].c_str(),
                            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick ,
                            "%s",
                            filename.c_str()
                        );

						if (ok)
						{
							DrawNode(list[i], children);
							ImGui::TreePop();
						}
                    }
                    else
                    {
                        ok = ImGui::TreeNodeEx(
                            list[i].c_str(),
                            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen ,
                            "%s",
                            filename.c_str()
                        );
                    }
        
                    
                }
                
            }
        }



        void drawFileSystem(bool* open)
        {
            cocos2d::FileUtils* fileUtils = cocos2d::FileUtils::getInstance();
            if (!ImGui::IsPopupOpen("Save?") && *open)
                ImGui::OpenPopup("Save?");
            if (ImGui::BeginPopupModal("Save?", open, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Save change to the following items?");
                
                std::vector<const char*> items;
                const std::vector<std::string>& paths = fileUtils->getSearchPaths();
                for (size_t i = 0; i < paths.size(); i++)
                {
                    items.push_back(paths[i].c_str());
                    // ImGui::TreeNodeEx(paths[i].c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
                }

                // const std::vector<std::string>& list = fileUtils->listFiles("/");
                // for (size_t i = 2; i < list.size(); i++)
                // {
                //     ImGui::TreeNodeEx(list[i].c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth);
                // }
                

                if (ImGui::BeginCombo("Search Path", paths[s_selectedSearthPathIndex].c_str()))
                {
                    for (size_t i = 0; i < paths.size(); i++)
                    {
						if (ImGui::Selectable(paths[i].c_str(), i == s_selectedSearthPathIndex))
                        {
                            s_selectedSearthPathIndex = i;
                        }
                    }
                    ImGui::EndCombo();
                }

                ImGui::BeginChild("left pane", ImVec2(150, 200), true);
				;
				DrawNode("/", cocos2d::FileUtils::getInstance()->listFiles("/"));
                ImGui::EndChild();
                        ImGui::SameLine();

                ImGui::BeginChild("right pane", ImVec2(500, 200), true);
				;

                auto& files = cocos2d::FileUtils::getInstance()->listFiles("/");
                for (auto& file: files)
                {
                    bool b = false;
                    if(fileUtils->isFileExist(file))
                    {
                        size_t pos = file.find_last_of('/');
                        std::string filename = file;
                        if (pos != std::string::npos)
                        {
                            filename = filename.substr(pos + 1);
                        }

                        ImGui::Selectable(filename.c_str(),    b);
                    }
                    
                }
				
                
                ImGui::EndChild();

                ImVec2 button_size(ImGui::GetFontSize() * 7.0f, 0.0f);
                if (ImGui::Button("Yes", button_size))
                {
                    
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("No", button_size))
                {
                    
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", button_size))
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
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
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("New"))
                    {
                        
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Open.."))
                    {
                        
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Save", "CTRL+S"))
                    {
                        
                    }

                    if (ImGui::MenuItem("Save As..."))
                    {
                        
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Exit"))
                    {
                        cocos2d::Director::getInstance()->end();
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Edit"))
                {
                    if (ImGui::MenuItem("Undo", "CTRL+Z"))
                    {
                        
                    }

                    if (ImGui::MenuItem("Redo", "CTRL+Y"))
                    {
                        
                    }

                    ImGui::Separator();

                    if (ImGui::MenuItem("Cut", "CTRL+X"))
                    {
                        
                    }

                    if (ImGui::MenuItem("Copy", "CTRL+C"))
                    {
                        
                    }

                    if (ImGui::MenuItem("Paste", "CTRL+V"))
                    {
                        
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Add"))
                {
                    for (const auto& pair : NodeFactory::getInstance()->getCreators())
                    {
                        const NodeFactory::NodeCreator& creator = pair.second;
                        Helper::drawMenuItem(creator._displayName, [&creator]{
                            NodeFactory::getInstance()->createNode(creator._name);
                        });
                    }
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Widget"))
                {
                    for (const auto& pair : WidgetFactory::getInstance()->getCreators())
                    {
                        const WidgetFactory::Creator& creator = pair.second;
                        Helper::drawMenuItem(creator.getDisplayName(), [&creator]{
                            Widget* widget = WidgetFactory::getInstance()->createWidget(creator.getName());
                            Editor::getInstance()->addWidget(widget);
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
        CCIMGUI::getInstance()->addCallback(std::bind(&Editor::callback, this), "CCImWidgets.Editor");

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

	 	static bool open = true;
        drawFileSystem(&open);
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
}


