#include "WidgetFactory.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    
    WidgetFactory* WidgetFactory::getInstance()
    {
        static WidgetFactory* instance = new WidgetFactory();
        return instance;
    }

    Widget* WidgetFactory::createWidget(const std::string& name)
    {
        std::unordered_map<std::string, WidgetCreator>::iterator it = _widgetCreators.find(name);
        if (it != _widgetCreators.end())
        {
            WidgetCreator& creator = it->second;
            Widget* widget = creator._ctor();
            std::string name = creator._name;
            std::string displayName = creator._displayName;
            if (creator._count > 0)
            {
                name = name + "/" + creator._count;
             //   displayName = displayName + '(' + creator._count +')';
            }
            if (widget && widget->init(std::move(name), std::move(displayName)))
            {
                creator._count ++;
                return widget;
            }
            
            delete widget;
        }
        
        return nullptr;
    }
}
