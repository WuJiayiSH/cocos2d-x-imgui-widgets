#ifndef __CCIMWIDGETS_PROPERTYRENDERER_H__
#define __CCIMWIDGETS_PROPERTYRENDERER_H__

#include <string>
#include "Widget.h"
#include "imgui/imgui.h"

namespace CCImWidgets
{
    template <typename T, typename Enabled = void>
    struct PropertyRenderer
    {
        static bool draw(const char* label, ...)
        {
            CCLOGWARN("Can't draw property: %s, missing specialization", label);
            return false;
        }
    };

    template <>
    struct PropertyRenderer<bool> {
        static bool draw(const char* label, bool& v) {
            return ImGui::Checkbox(label, &v);
        }
    };
    
    template <>
    struct PropertyRenderer<cocos2d::Vec3> {
        static bool draw(const char* label, cocos2d::Vec3& vec, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
            float v[3] = { vec.x, vec.y, vec.z };
            if (ImGui::DragFloat3(label, v, v_speed, v_min,  v_max, format, flags))
            {
                vec.set(v);
                return true;
            }
            return false;
        }
};
}

#endif