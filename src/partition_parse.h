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
 * Usage:
 * PartitionParse pa = new PartitionParse();
 * pa->parse(filePath);
 * pa->locate()
 * while(pa->nexUnit()){
 *  // process this unit.
 * }
 */
class PartitionParse {

public:

    /** initial parse.
     * @param partitionFilePath file path of partition file.
     */
    void parse(std::string partitionFilePath);

    /**
     * locate the start position of this processor in partition file.
     */
    void locate();

    /**
     * Get next simulation unit (sub-basin) dispatched to this processor sequentially.
     * Use traverse to get all simulation units.
     * @return true for has more nodes, false for no other node (get to the end) for this processor.
     */
    bool nextNode();

    /**
     * Get current node's upstream metadata.
     * @return number of upstream nodes.
     */
    int getUpstream();

    /**
     * Get current nodes downstream nodes (usually there is only one downstream node).
     * @return number of downstream nodes.
     */
    int getDownstream();
};

#endif //PNOHS_PARTITION_PARSE_H
