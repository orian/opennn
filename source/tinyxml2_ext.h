#ifndef __TINYXML2_EXT_H__
#define __TINYXML2_EXT_H__

#ifdef __linux__
#include "tinyxml2.h"
#else
#include "../tinyxml2/tinyxml2.h"
#endif

namespace tinyxml2 {
void DeepClone(XMLNode* newNode, const XMLNode* nodeSrc, XMLDocument* DocDest,
               const XMLNode*);
}  // namespace tinyxml2

#endif  // __TINYXML2_EXT_H__