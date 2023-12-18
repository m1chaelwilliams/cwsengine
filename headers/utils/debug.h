#ifndef CWS_DEBUG_H
#define CWS_DEBUG_H

#ifdef DEBUG

#include <iostream>
#define CWS_LOGLN(X) std::cout << X << std::endl;
#define CWS_LOG(x) std::cout << X;

#else

#define CWS_LOGLN(X)
#define CWS_LOG(X)

#endif

#endif