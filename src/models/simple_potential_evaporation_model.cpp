//
// Created by wujiahao on 2018/4/6.
//

#include "simple_potential_evaporation_model.h"

bool SimplePotentialEvaporationModel::checkParameters(const mlcg::_type_dparas *dParas,
                                                      const mlcg::_type_iparas *iParas) {
    return true;
}

bool SimplePotentialEvaporationModel::calculatePotentialEvaporation(const mlcg::_type_dparas *dParas,
                                                                    const mlcg::_type_iparas *iParas,
                                                                    const mlcg::_type_ddatas *dDatas,
                                                                    const mlcg::_type_idatas *iDatas,
                                                                    double *epot_base) {

    if (!this->checkParameters(dParas, iParas) || !this->checkDatas(dDatas, iDatas)) {
        return false;
    }

    *epot_base = dParas->at(mlcg::_pname_seasonal_factor) * dParas->at(mlcg::_pname_rate_parameter)
                 * (dDatas->at(mlcg::_dname_air_temperature) - dParas->at(mlcg::_pname_air_temperature_threshold));
    return true;
}

bool SimplePotentialEvaporationModel::checkDatas(const mlcg::_type_ddatas *dDatas,
                                                 const mlcg::_type_idatas *idDatas) {
    return true;
}

SimplePotentialEvaporationModel::SimplePotentialEvaporationModel() {

    this->dpara_thresholds[mlcg::_pname_rate_parameter][0] = 0.0;
    this->dpara_thresholds[mlcg::_pname_rate_parameter][1] = 0.1;
    this->dpara_thresholds[mlcg::_pname_air_temperature_threshold][0] = 100.0;
    this->dpara_thresholds[mlcg::_pname_air_temperature_threshold][1] = 200.1;
    this->dpara_thresholds[mlcg::_pname_seasonal_factor][0] = -0.1;
    this->dpara_thresholds[mlcg::_pname_seasonal_factor][1] = 0.1;

    this->data_names.push_back(mlcg::_dname_air_temperature);

}

