//
// Created by wujiahao on 2018/4/6.
//

#ifndef PNOHS_SIMPLE_POTENTIAL_EVAPORATION_MODEL_H
#define PNOHS_SIMPLE_POTENTIAL_EVAPORATION_MODEL_H


#include "interface_potential_evaporation_model.h"

class SimplePotentialEvaporationModel : public IPotentialEvaporationModel {

public:

    SimplePotentialEvaporationModel();

    bool checkDatas(const mlcg::_type_ddatas *dDatas, const mlcg::_type_idatas *idDatas) override;

    bool
    checkParameters(const mlcg::_type_dparas *dParas, const mlcg::_type_iparas *iParas) override;

public:
    bool calculatePotentialEvaporation(const mlcg::_type_dparas *dParas,
                                       const mlcg::_type_iparas *iParas,
                                       const mlcg::_type_ddatas *dDatas,
                                       const mlcg::_type_idatas *iDatas,
                                       double *epot_base) override;

};


#endif //PNOHS_SIMPLE_POTENTIAL_EVAPORATION_MODEL_H
