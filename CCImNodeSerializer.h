#ifndef __CCIMSERIALIZER_H__
#define __CCIMSERIALIZER_H__

#include "cocos2d.h"

#include <vector>
#include <string>

namespace CCImWidgets
{
    class CCImSerializer : cocos2d::Ref
    {
    public:
        enum Context
        {
            Serializing,
            Deserializing,
            Drawing,
        };

        friend class CCImWidgetManager;

        CCImSerializer() {};
        virtual ~CCImSerializer() {};

        const std::string& getName() const { return _name; }
        const std::string& getDescription() const { return _description; }

        void register()
        {
            constructor("2D/Sprite", &Sprite::create, {"filename"});
            
        }
    protected:
        template<typename Getter, typename Setter, typename NodeType, typename... Args>
        CCImSerializer& process(const char* label, Getter&& getter, Setter&& setter, NodeType* node, Args&&... args)
        {
			using namespace std;
			using ValueType = std::remove_cv<std::remove_reference<std::result_of<Getter(NodeType*)>::type>::type>::type;

            if (_context == Drawing)
            {
                ValueType val = std::forward<Getter>(getter)(node);
                if (CCImGuiPropertyRenderer<ValueType>::draw(label, val, std::forward<Args>(args)...))
                {
                    std::forward<Setter>(setter)(node, val);
                }
            }
        }


        template<typename T, typename... Args>
        CCImSerializer& constructor(const char* label, T*(*f)(Args...), const std::initializer_list<const char* > & names)
        {
            
        }


        Context _context = Serializing;

    private:
        std::string _name;
        std::string _description;
    };
}

#endif