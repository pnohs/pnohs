//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_PARTITION_PARSE_H
#define PNOHS_PARTITION_PARSE_H

#include <string>
#include <fstream>
#include <utils/data_def.h>
#include "../utils/typedef.h"
#include "partition_type.h"
#include "node_parse.h"

/**
 * PartitionParse read partition file, so each processor can handle some simulation units (usually they are sub-basins).
 * this partition file format:
 * todo
 *
 * Usage:
 * PartitionParse pa = new PartitionParse(filePath,rankId);
 * pa->parse();
 * pa->locate()
 * while(pa->nextNode()){
 *  // process this unit.
 * }
 */

class PartitionParse {

public:

    /** initial parse.
     * @param partitionFilePath file path of partition file.
     */

    PartitionParse(const std::string &partitionFilePath, const kiwi::RID processorId);

    /**
         * locate the start position of this processor in partition file.
         */
    void locate();

    /**
     * Get next simulation unit (sub-basin) dispatched to this processor sequentially.
     * Can use traverse to get all simulation units.
     * @return return parsed node information, null for no other node (get to the end) for this processor.
     */
    NodeParse *nextNode();

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

protected:
    std::fstream fs; //输入文件的输入流
    _type_part_offset base_offset = 0; // absolute offset from beginning of file to data position of this processor in partition file.
    //  kiwi::_type_io_offset relative_file_offset = 0; // relative offset form base_offset.

    _type_nodes_count nodes_count = 0; // simulation unit(node) count on this processor.
    _type_node_index current_node_index = 0;
    kiwi::RID rid;

private:
    /**
     * this function locate file pointer to the start position of ith node.
     *
     * [count of nodes] [nodes index]       [nodes data]
     *   |_________|___________________|___________________________|
     *   0                  | |                |    |
     *                [ith node's index]      [ith node's data]
     *
     * If we use tuple <I,V> to indicate offset and value stored in file,
     * in which, I denotes the offset from the number 0, V denotes value in the block (may be type long/int .etc).
     * If the the <I,V> of [ith node's index] is <I_i, V_i>, then the value I of [ith node data] will be V_i. This is what index mean.
     * That is, the offset value of [ith node's data] is stored in [ith node's index].
     *
     * @param index node index starting from 0, 1, 2 ...
     */
    void locateNode(_type_node_index index);

    /**
     * calculate relative offset by the offset to data position of this processor.
     * @param offset
     * @return
     */
    inline long relativeOffset(long offset) {
        return base_offset + offset - fs.tellg();
    }
};

#endif //PNOHS_PARTITION_PARSE_H
