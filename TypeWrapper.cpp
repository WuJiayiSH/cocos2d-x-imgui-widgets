

#include <vector>
#include <string>

namespace CCImWidgets
{
    class Node3DWrapper: public TypeWrapper
    {
    public:
        void wrap()
        {
            constructor("3D Node", &Node::create);
            property("Position", &Node::getPosition, &Node::setPosition);
        }
    }
        


    namespace
    {
        static WidgetManager::TypeWrapperRegister<Node3DWrapper> s_node3DWrapperRegister("CCImWidgets.Node3D", "3D/Node");
    }
}
