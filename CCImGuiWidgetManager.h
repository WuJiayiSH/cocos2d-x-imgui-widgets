#ifndef __CCIMGUIWIDGETMANAGER_H__
#define __CCIMGUIWIDGETMANAGER_H__

#include "cocos2d.h"
#include "CCImGuiWidget.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace CCImGuiWidgets
{
	class ImGuiNodeProxy
	{

	};
    class ImGuiWidgetManager : public cocos2d::Ref
    {
    public:
        template <typename T>
        struct WidgetRegister
        {
            WidgetRegister(const char* name, const char* description, const std::initializer_list<const char* > &dependencies)
            {
                T* widget = new T();
                widget->_name = name;
                widget->_description = description;
                for (const char* dependency : dependencies)
                {
                    widget->_dependencies.push_back(dependency);
                }
                ImGuiWidgetManager::getInstance()->_widgets.emplace(name, widget);
            }
        };

        template <typename T>
        struct NodeProxyRegister
        {
            NodeProxyRegister(const char* name, const char* description, const std::initializer_list<const char* > &dependencies)
            {
                T* nodeProxy = new T();
                nodeProxy->_name = name;
                nodeProxy->_description = description;
                for (const char* dependency : dependencies)
                {
                    nodeProxy->_dependencies.push_back(dependency);
                }
                ImGuiWidgetManager::getInstance()->_nodeProxies.emplace(name, nodeProxy);
            }
        };

        static ImGuiWidgetManager* getInstance();
        ImGuiWidget* getWidget(const std::string &name);

        Ref* getHandle(const std::string &key) { return _handles[key]; };
        void setHandle(const std::string &key, Ref* handle) { _handles[key] = handle; };

        bool load();
        void update(float dt);
        void draw();

    private:
        ImGuiWidgetManager(){};
        ~ImGuiWidgetManager();
        std::unordered_map<std::string, ImGuiWidget*> _widgets;
        std::unordered_map<std::string, cocos2d::WeakPtr<Ref>> _handles;
        std::unordered_map<std::string, ImGuiNodeProxy*> _nodeProxies;
    };
}

#endif