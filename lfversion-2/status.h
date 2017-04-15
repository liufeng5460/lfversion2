#ifndef STATUS
#define STATUS

#include "ui-showwidget.h"
#include <string>
using namespace std;
namespace Status {

extern bool listening;
extern quint16 port;
extern ShowWidgetUI* showWidget;
extern string cipherText;
extern string plainText;

}



#endif // STATUS

