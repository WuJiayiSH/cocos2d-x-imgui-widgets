#ifndef __CCIMNODETREE_H__
#define __CCIMNODETREE_H__

#include <string>
#include "Widget.h"
#include "cocos2d.h"

namespace CCImWidgets
{
    template <typename T, typename Enabled = void>
    struct CCImPropertyRenderer
    {
        static bool draw(const char* label, ...)
        {
            CCLOGWARN("Can't draw property: %s, missing specialization", label);
            return false;
        }
    };

    template <>
    struct CCImPropertyRenderer<bool> {
        static bool draw(const char* label, bool& val) {
            return ImGui::Checkbox(label, &val);
        }
    };
    
}

#endif