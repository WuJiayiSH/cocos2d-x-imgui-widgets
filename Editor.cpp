#include "Editor.h"
#include "NodeFactory.h"
#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include "CCImGuiLayer.h"
#include "Helper.h"

using namespace cocos2d;
namespace CCImWidgets
{
    namespace
    {
        
        const size_t numOfIgnoreDirectories = 2;// ignore . and ..
        std::string s_fileDialogCurrentPath;
		std::string s_fileDialogCurrentFile;
        void drawDirectories(const std::vector<std::string>& directories)
        {
            FileUtils* fileUtils = FileUtils::getInstance();
            for(size_t i = 0; i < directories.size(); i++)
            {
                const std::string& directory = directories[i];
				CCLOG("%s", directory.c_str());
                
                if(fileUtils->isDirectoryExist(directory))
                {
                    size_t size = directory.size();
                    size_t pos = directory.find_last_of('/', size - 2);
                    pos = (pos == std::string::npos) ? 0 : pos + 1;
                    std::string dirname = directory.substr(pos, size - 1 - pos);
                    

					//if (dirname != "." && dirname != "..")
					{
						ImGuiTreeNodeFlags selectedFlag = s_fileDialogCurrentPath == directory ? ImGuiTreeNodeFlags_Selected : 0;

						const std::vector<std::string>& subDirectories = fileUtils->listFiles(directory);
						if (subDirectories.size() > numOfIgnoreDirectories)
						{
							bool ok = ImGui::TreeNodeEx(
								dirname.c_str(),
								ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | selectedFlag,
								"%s",
								dirname.c_str()
							);

							if (ImGui::IsItemClicked())
								s_fileDialogCurrentPath = directory;

							if (ok)
							{
								drawDirectories(subDirectories);
								ImGui::TreePop();
							}
						}
						else
						{
							ImGui::TreeNodeEx(
								dirname.c_str(),
								ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | selectedFlag,
								"%s",
								dirname.c_str()
							);

							if (ImGui::IsItemClicked())
								s_fileDialogCurrentPath = directory;
						}
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
                // search paths
                
                const std::vector<std::string>& searchPaths = fileUtils->getSearchPaths();
                

                if (s_fileDialogCurrentPath.empty() && searchPaths.size() > 0)
                    s_fileDialogCurrentPath = searchPaths[0];

                
                if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody, ImVec2(600, 300)))
                {
                    ImGui::TableSetupColumn("Search Paths", ImGuiTableColumnFlags_WidthFixed);
                    ImGui::TableSetupColumn("Files", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableHeadersRow();

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    drawDirectories(searchPaths);

                    ImGui::TableSetColumnIndex(1);
					const std::vector<std::string>& files = cocos2d::FileUtils::getInstance()->listFiles(s_fileDialogCurrentPath);
					for (const std::string& file: files)
					{
						bool b = false;
						if(fileUtils->isFileExist(file))
						{
							size_t lastSlash = file.find_last_of('/');
							const char* filename = file.c_str();
							if (lastSlash != std::string::npos)
							{
								filename = filename + lastSlash + 1;
							}

							if (ImGui::Selectable(filename, s_fileDialogCurrentFile == file))
							{
								s_fileDialogCurrentFile = file;
							}
						}
                    
					}

                    
                    ImGui::EndTable();
                }
				
                ImVec2 button_size(ImGui::GetFontSize() * 7.0f, 0.0f);
                if (ImGui::Button("Yes", button_size))
                {
                    *open = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("No", button_size))
                {
                    *open = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", button_size))
                {
                    *open = false;
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


