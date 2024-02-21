
#include "CCImGuiWidgetManager.h"

namespace CCImGuiWidgets
{
    ImGuiWidgetManager::~ImGuiWidgetManager()
    {
        for (const std::pair<const std::string, ImGuiWidget*>& pair : _widgets)
        {
            if (ImGuiWidget* widget = pair.second)
            {
                delete widget;
            }
        }
    }

    ImGuiWidgetManager* ImGuiWidgetManager::getInstance()
    {
        static ImGuiWidgetManager* instance = new ImGuiWidgetManager();
        return instance;
    }

    ImGuiWidget* ImGuiWidgetManager::getWidget(const std::string& name)
    {
        std::unordered_map<std::string, ImGuiWidget*>::iterator it = _widgets.find(name);
        return it == _widgets.end() ? nullptr : it->second;
    }

    bool ImGuiWidgetManager::load()
    {
        std::vector<std::string> loadedWidgetNames;
        size_t loadedWidgetSize;
        do
        {
            loadedWidgetSize = loadedWidgetNames.size();
            for (const std::pair<const std::string, ImGuiWidget*>& pair : _widgets)
            {
                if (ImGuiWidget* widget = pair.second)
                {
                    if (widget->isLoaded())
                        continue;

                    const std::vector<std::string>& dependencies = widget->getDependencies();
                    bool areAllDependenciesLoaded = true;
                    for (const std::string& dependency: dependencies) {
                        if (std::find(loadedWidgetNames.begin(), loadedWidgetNames.end(), dependency) == loadedWidgetNames.end()) {
                            areAllDependenciesLoaded = false;
                            break;
                        }
                    }

                    if (!areAllDependenciesLoaded)
                        continue;

                    widget->onLoad();
                    widget->_loaded = true;
                    loadedWidgetNames.push_back(widget->getName());
                }
            }
        } while (loadedWidgetNames.size() < _widgets.size() && loadedWidgetNames.size() > loadedWidgetSize);

        return loadedWidgetNames.size() == _widgets.size();
    }

    void ImGuiWidgetManager::update(float dt)
    {

    }

    void ImGuiWidgetManager::draw()
    {
        for (const std::pair<const std::string, ImGuiWidget*>& pair : _widgets)
        {
            if (ImGuiWidget* widget = pair.second)
            {
                if (widget->isLoaded())
                    widget->draw();
            }
        }
    }
}
