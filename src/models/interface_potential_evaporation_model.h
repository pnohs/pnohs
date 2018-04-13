//
// Created by wujiahao on 2018/4/6.
//

#ifndef PNOHS_INTERFACE_POTENTIAL_EVAPORATION_MODEL_H
#define PNOHS_INTERFACE_POTENTIAL_EVAPORATION_MODEL_H

#include "models_config.h"

class IPotentialEvaporationModel {

protected:
    // the parameters' name and threshold needed by this model
    mlcg::_type_dpara_thresholds dpara_thresholds;
    mlcg::_type_ipara_thresholds ipara_thresholds;
    // the input data's name
    mlcg::_type_data_names data_names;

protected:
    virtual bool checkParameters(const mlcg::_type_dparas *dParas, const mlcg::_type_iparas *iParas) = 0;
    virtual bool checkDatas(const mlcg::_type_ddatas *dDatas, const mlcg::_type_idatas *idDatas) = 0;

public:
    virtual bool
    calculatePotentialEvaporation(const mlcg::_type_dparas *dParas,
                                  const mlcg::_type_iparas *iParas,
                                  const mlcg::_type_ddatas *dDatas,
                                  const mlcg::_type_idatas *iDatas,
                                  double *epot_base) = 0;
};

#endif //PNOHS_INTERFACE_POTENTIAL_EVAPORATION_MODEL_H
