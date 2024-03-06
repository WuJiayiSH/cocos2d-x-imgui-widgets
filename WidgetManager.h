#ifndef __CCIMWIDGETS_WIDGETMANAGER_H__
#define __CCIMWIDGETS_WIDGETMANAGER_H__

#include "Widget.h"

#include "cocos2d.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace CCImWidgets
{
    class WidgetManager : public cocos2d::Ref
    {
    
    public:
        template <typename T>
        struct WidgetRegister
        {
            WidgetRegister(const char* name, const char* displayName)
            {
                WidgetCreator& creator = _widgetCreators[name];
                creator._name = name;
                creator._displayName = displayName;
                creator._ctor = [] () -> Widget* {return new (std::nothrow) T();} ;
            }
        };

        template <typename T>
        struct TypeWrapperRegister
        {
            TypeWrapperRegister(const char* name, const char* displayName)
            {
                if (T* typeWrapper = new T())
                {
                    typeWrapper->autorelease();
                    typeWrapper->_name = name;
                    typeWrapper->_displayName = displayName;
                    
                }
            }
        };

        static WidgetManager* getInstance();

        
        Ref* getUserObject(const std::string& path) { return _userObjects[path]; };
        void setUserObject(const std::string& path, Ref* handle) { _userObjects[path] = handle; };

        
    private:
        
        std::unordered_map<std::string, cocos2d::WeakPtr<Ref>> _userObjects;
        Widget* _visitingWidget = nullptr;
    };
}

#endif