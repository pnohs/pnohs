//
// Created by genshen on 3/28/18.
//

#ifndef PNOHS_DISPATCH_PARSE_H
#define PNOHS_DISPATCH_PARSE_H

#include <string>
#include <fstream>
#include <utils/data_def.h>
#include "../utils/predefine.h"
#include "dispatch_type.h"
#include "node_parse.h"

/**
 * DispatchParse read dispatch file, so each processor can handle some nodes(also called simulation units (usually they are sub-basins)).
 * this dispatch file format:
 * todo
 *
 * Usage:
 * DispatchParse *pa = new DispatchParse(filePath,rankId);
 * pa->locate();
 * while(pa->nextNode()){
 *  // process this unit.
 * }
 */

class DispatchParse {
public:

    /**
     * parse with file stream.
     * @param dispatchStream file path of dispatch file.
     * @param processorId  id (can be mpi rank). Each processor handle several simulation unit (nodes).
     */
    DispatchParse(std::fstream &dispatchStream, const _type_dispatch_rank_id processorId);

    /**
    * locate the start position of this processor in dispatch file.
    */
    void locate();

    /**
     * check if the end of the nodes result has been reached.
     * true for have more node(s), false for there is no more node to be read.
     */
    inline bool isAfterLast() {
        return current_node_index < nodes_count;
    }

    /**
     * Get next simulation unit (sub-basin) dispatched to this processor sequentially.
     * Can use traverse to get all simulation units.
     * @return return parsed node information, null for no other node (get to the end) for this processor.
     * @deprecated pointer may cause memory leak
     *
     */
    const DNode nextNode();

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
    std::fstream &fs; //输入文件的输入流
    _type_dispatch_file_offset base_offset = 0; // absolute offset from beginning of file to data position of this processor in dispatch file.
    //  kiwi::_type_io_offset relative_file_offset = 0; // relative offset form base_offset.

    _type_dispatch_nodes_count nodes_count = 0; // simulation unit(node) count on this processor.
    _type_dispatch_node_index current_node_index = 0;
    _type_dispatch_rank_id rid;

private:
    /**
     * This function locate file pointer to the start position of ith node.
     * It first read index of ith node, then locate to the node data by the node index.
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
    void locateNode(_type_dispatch_node_index index);

    /**
     * calculate relative offset by the offset to data position of this processor.
     * @param offset
     * @return
     */
    inline long relativeOffset(long offset) {
        return base_offset + offset - fs.tellg();
    }
};

#endif //PNOHS_DISPATCH_PARSE_H
