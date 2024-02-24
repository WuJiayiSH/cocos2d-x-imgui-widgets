#ifndef __CCIMGUINODETREE_H__
#define __CCIMGUINODETREE_H__

#include <string>
#include "CCImGuiWidget.h"
#include "cocos2d.h"

namespace CCImGuiWidgets
{
    template <typename T, typename = void>
    struct ImGuiPropertyRenderer
    {
        static bool draw(T&) = delete;
    };

    template <>
    struct ImGuiPropertyRenderer<bool> {
        static bool draw(const char* label, bool& val) {
             return ImGui::Checkbox(label, &val);
        }
    };

    template <>
    struct ImGuiPropertyRenderer<cocos2d::Vec3> {
        static bool draw(const char* label, cocos2d::Vec3& val, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
            float f[3];
            f[0] = val.x;
            f[1] = val.y;
            f[2] = val.z;
            if (ImGui::DragFloat3(label, f, v_speed, v_min, v_max, format, flags))
            {
                val.x = f[0];
                val.y = f[1];
                val.z = f[2];
                return true;
            }

            return false;
        }
    };

    class ImGuiNodeProcessor
    {
        public:
        static ImGuiNodeProcessor* getInstance()
        {
            static ImGuiNodeProcessor instance;
            return &instance;
		};

        void render(cocos2d::Node* node)
        {
            draw("Position", 
            [](cocos2d::Node* node) -> cocos2d::Vec3 {return node->getPosition3D(); },
            [](cocos2d::Node* node, const cocos2d::Vec3& pos) -> void {node->setPosition3D(pos); },
            node);

            
        }
        protected:
        template<typename Getter, typename Setter, typename NodeType, typename... Args>
        CC_ALWAYS_INLINE void draw(const char* label, Getter&& getter, Setter&& setter, NodeType* node, Args&&... args)
        {
			using namespace std;
			using ValueType = std::remove_cv<std::remove_reference<std::result_of<Getter(NodeType*)>::type>::type>::type;
			ValueType val = std::forward<Getter>(getter)(node);
			if (ImGuiPropertyRenderer<ValueType>::draw(label, val, std::forward<Args>(args)...))
			{
				std::forward<Setter>(setter)(node, val);
			}
        }
	};
   // class ImGuiNodeProcessor
   // {
    /*
        template<typename ClassType, typename ReturnType>
        CC_ALWAYS_INLINE void draw(const char* label, ClassType* node, ReturnType(ClassType::*getter)() const)
        {
			using T = std::remove_cv<std::remove_reference<ReturnType>::type>::type;
            T val = (node->*getter)();
			ImGuiPropertyRenderer<T>::draw(label, val);

        }
*/

        template<typename Getter, typename Setter, typename NodeType, typename... Args>
        CC_ALWAYS_INLINE void draw(const char* label, Getter&& getter, Setter&& setter, NodeType* node, Args&&... args)
        {
			using namespace std;
			using ValueType = std::remove_cv<std::remove_reference<std::result_of<Getter(NodeType*)>::type>::type>::type;
			ValueType val = std::forward<Getter>(getter)(node);
			if (ImGuiPropertyRenderer<ValueType>::draw(label, val, std::forward<Args>(args)...))
			{
				std::forward<Setter>(setter)(node, val);
			}
        }
        



        
   // }
}

#endif