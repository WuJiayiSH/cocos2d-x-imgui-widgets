#ifndef __CCIMNODEPREVIEW_H__
#define __CCIMNODEPREVIEW_H__

#include <string>
#include "CCImWidget.h"

namespace CCImWidgets
{
    class CCImNodePreview: public CCImWidget
    {
    private:
        void draw() override;
    };
}

#endif