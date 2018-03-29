//
// Created by wujiahao on 24/03/2018.
//

#ifndef PNOHS_GEO_INFO_SUBBASIN_H
#define PNOHS_GEO_INFO_SUBBASIN_H

/**
 * geographical infomation of a subbasin node needed by simmulation
 */
class geo_info_subbasin {
public:
    geo_info_subbasin();
    virtual ~geo_info_subbasin();

    double              lat;
    double              lon;
    double              elev;

private:

};


#endif //PNOHS_GEO_INFO_SUBBASIN_H
