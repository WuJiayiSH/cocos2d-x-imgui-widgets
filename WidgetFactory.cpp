#include "WidgetFactory.h"
#include "CCIMGUI.h"
#include <inttypes.h>
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
            std::string displayName = creator._displayName;
            if (creator._count > 0)
            {
				char postfix[16];
				sprintf(postfix, " (%" PRIu32 ")", creator._count);
				displayName.append(postfix);
            }
            if (widget && widget->init(creator._name, displayName))
            {
                creator._count ++;
                return widget;
            }
            
            delete widget;
        }
        
        return nullptr;
    }
}
