#include "node.h"
void buildMap_helper(Node * node, BitString b, std::map<unsigned, BitString> & theMap) {
  if (node->sym != NO_SYM) {
    theMap[node->sym] = b;
    return;
  }
  else {
    if (node->left != NULL) {
      buildMap_helper(node->left, b.plusZero(), theMap);
    }
    if (node->right != NULL) {
      buildMap_helper(node->right, b.plusOne(), theMap);
    }
  }
}

void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //WRITE ME!
  Node * root = this;
  buildMap_helper(root, b, theMap);
}
