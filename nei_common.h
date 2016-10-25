#ifndef NEI_COMMON
#define NEI_COMMON

#include <QDebug>

#include "nei_onepage.h"
#include "nei_result.h"
#include "nei_bottom.h"
#include "nei_login.h"
#include "mainwindow.h"

extern nei_bottom *mBottom;
extern nei_onepage *mOnepage;
extern nei_result *mRes;
extern nei_login *mLogin;
extern QStackedWidget *mStack;

extern int upscreenWidth;
extern int upscreenHeight;

#endif // NEI_COMMON

