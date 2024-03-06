#include "Preview.h"
#include "WidgetFactory.h"
#include "WidgetManager.h"
#include "CCIMGUI.h"

namespace CCImWidgets
{
    void Preview::draw()
    {
        
    }

    namespace
    {
        static WidgetFactory::AutoRegister<Preview> s_register(
            "CCImWidgets.Preview",
            "Preview"
        );
    }
}


