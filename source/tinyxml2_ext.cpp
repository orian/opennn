#include "tinyxml2_ext.h"

namespace tinyxml2 {

void DeepClone(XMLNode* newNode, const XMLNode* nodeSrc, XMLDocument* DocDest,
               const XMLNode*) {
  const XMLNode* child = nodeSrc->FirstChild();

  XMLNode* newNode2;

  if (child) {
    newNode2 = child->ShallowClone(DocDest);
    DeepClone(newNode2, child, DocDest, nodeSrc);
    newNode->InsertFirstChild(newNode2);
  } else {
    return;
  }

  XMLNode* lastClone = newNode2;

  while (1) {
    const XMLNode* child2 = child->NextSibling();

    if (!child2) {
      break;
    }

    XMLNode* newNode2 = child2->ShallowClone(DocDest);

    DeepClone(newNode2, child2, DocDest, nodeSrc);

    newNode->InsertAfterChild(lastClone, newNode2);
    child = child2;
    lastClone = newNode2;
  }
}

}  // namespace tinyxml2