//
// Created by genshen on 2017/12/24.
//

#ifndef PNOHS_BINARY_TREE_CODIFY_H
#define PNOHS_BINARY_TREE_CODIFY_H

#include "base_codification.h"

// other implement: [2-3 tree](https://cathyatseneca.gitbooks.io/data-structures-and-algorithms/content/2-3_trees/)
class BinaryTreeCodify : public BaseCodification {
public:
    void getDownstreamReach() override;

    void getUpstreamReaches() override;
};

#endif // PNOHS_BINARY_TREE_CODIFY_H
