#include "WidgetManager.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    WidgetManager* WidgetManager::getInstance()
    {
        static WidgetManager* instance = new WidgetManager();
        return instance;
    }

    
}
