#pragma once

#include <QtCore>

#ifdef BUILD_TMCORE
    #define TMCORE_DLLSPEC Q_DECL_EXPORT
#else
    #define TMCORE_DLLSPEC Q_DECL_IMPORT
#endif

class TMCORE_DLLSPEC TMCore
{

public:
    TMCore();
};

