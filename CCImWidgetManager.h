#ifndef __CCIMWIDGETMANAGER_H__
#define __CCIMWIDGETMANAGER_H__

#include "CCImWidget.h"

#include "cocos2d.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace CCImWidgets
{
    class CCImWidgetManager : public cocos2d::Ref
    {
    public:
        template <typename T>
        struct CCImWidgetRegister
        {
            CCImWidgetRegister(const char* name, const char* description, const std::initializer_list<const char* > &dependencies)
            {
                if (T* widget = T::create())
                {
                    widget->_name = name;
                    widget->_description = description;
                    for (const char* dependency : dependencies)
                    {
                        widget->_dependencies.push_back(dependency);
                    }
                    CCImWidgetManager::getInstance()->_widgets.emplace(name, widget);
                }
            }
        };

        template <typename T>
        struct CCImNodeSerializerRegister
        {
            CCImNodeSerializerRegister(const char* name, const char* description, const std::initializer_list<const char* > &dependencies)
            {
                if (T* nodeSerializer = T::create())
                {
                    nodeSerializer->_name = name;
                    nodeSerializer->_description = description;
                    for (const char* dependency : dependencies)
                    {
                        nodeSerializer->_dependencies.push_back(dependency);
                    }
                    CCImWidgetManager::getInstance()->_widgets.emplace(name, nodeSerializer);
                }
            }
        };

        static CCImWidgetManager* getInstance();

        CCImWidget* getWidget(const std::string &name) { return _widgets[name]; };
        CCImNodeSerializer* getNodeSerializer(const std::string &path) { return _nodeSerializers[path]; };

        Ref* getUserObject(const std::string& path) { return _userObjects[path]; };
        void setUserObject(const std::string& path, Ref* handle) { _userObjects[path] = handle; };

        bool init();
    private:
        std::unordered_map<std::string, cocos2d::RefPtr<CCImWidget>> _widgets;
        std::unordered_map<std::string, cocos2d::RefPtr<CCImNodeSerializer>> _nodeSerializers;
        std::unordered_map<std::string, cocos2d::WeakPtr<Ref>> _userObjects;
    };
}

#endif