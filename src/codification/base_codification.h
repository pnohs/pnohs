//
// Created by genshen on 2017/12/24.
//

#ifndef PNOHS_ENCODER_H
#define PNOHS_ENCODER_H

// codification for river network.
// base class.
class BaseCodification {
public:
    virtual void initialCodification() = 0;

    virtual void getDownstreamReach()= 0;

    virtual void getUpstreamReaches()= 0;
};

#endif //PNOHS_ENCODER_H
