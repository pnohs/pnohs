//
// Created by genshen on 4/1/18.
//

#ifndef PNOHS_DISPATCH_JSON_STRING_H
#define PNOHS_DISPATCH_JSON_STRING_H

#include <string>

const std::string DISPATCH_JSON = R"(
{
  "header": {
    "ranks": 3
  },
  "dispatch": [
    {
      "rank_id": 0,
      "nodes_count": 1,
      "nodes": [
        {
          "node_id": 16,
          "upstream": [
            {
              "node_id": 1000,
              "locate": 2000
            },
            {
              "node_id": 1001,
              "locate": 2002
            },
            {
              "node_id": 1002,
              "locate": 2004
            },
            {
              "node_id": 1003,
              "locate": 2006
            }
          ],
          "downstream": []
        }
      ]
    },
    {
      "rank_id": 1,
      "nodes_count": 2,
      "nodes": [
        {
          "node_id": 8,
          "upstream": [
            {
              "node_id": 4,
              "locate": 0
            },
            {
              "node_id": 2,
              "locate": 1
            },
            {
              "node_id": 5,
              "locate": 1
            },
            {
              "node_id": 3,
              "locate": 2
            }
          ],
          "downstream": [
            {
              "node_id": 12,
              "locate": 2
            }
          ]
        },
        {
          "node_id": 15,
          "upstream": [],
          "downstream": [
            {
              "node_id": 16,
              "locate": 0
            }
          ]
        }
      ]
    },
    {
      "rank_id": 3,
      "nodes_count": 0,
      "nodes": []
    }
  ]
}
)";

#endif //PNOHS_DISPATCH_JSON_STRING_H
