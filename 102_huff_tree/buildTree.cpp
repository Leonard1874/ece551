#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pq;
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] > 0) {
      pq.push(new Node(i, counts[i]));
    }
  }
  while (pq.size() > 1) {
    if (pq.size() >= 2) {
      Node * a = pq.top();
      pq.pop();
      Node * b = pq.top();
      pq.pop();
      pq.push(new Node(a, b));
    }
  }
  return pq.top();
}
