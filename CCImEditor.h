#ifndef __CCIMEDITOR_H__
#define __CCIMEDITOR_H__

#include <string>
#include "CCImWidget.h"

namespace CCImWidgets
{
    class CCImEditor: public CCImWidget
    {
    private:
        void draw() override;
    };
}

#endif