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
        std::unordered_map<std::string, Creator>::iterator it = _creators.find(name);
        if (it != _creators.end())
        {
			Creator& creator = it->second;
			Widget* widget = creator._constructor();
            if (widget && widget->init(creator._name, creator._displayName, creator._count))
            {
                creator._count ++;
                return widget;
            }

            delete widget;
        }
        
        return nullptr;
    }
}
