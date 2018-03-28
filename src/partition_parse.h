//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_PARTITION_PARSE_H
#define PNOHS_PARTITION_PARSE_H

#include <string>

/**
 * PartitionParse read partition file, so each processor can handle some simulation units (usually they are sub-basins).
 * this partition file format:
 * todo
 *
 */
class PartitionParse {

public:
    /**
     *
     * @param partitionFilePath file path of partition file.
     */
    void parse(std::string partitionFilePath);
    // void locate
    // bool nextUnit
    // int getUpstream
    // int getDownstream
};

#endif //PNOHS_PARTITION_PARSE_H
