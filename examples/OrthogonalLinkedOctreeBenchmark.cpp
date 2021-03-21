/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/

#include <iostream>
#include <sstream>
#include <memory>
#include <cmath>
#include <cstdlib>

#include <torch/torch.h>
#include "../file_format/point_cloud_base_presentation/Point.h"
#include "../orthogonal_linked/orthogonal_linked_octree_with_torch/LinkedOctree.h"
#include <chrono>


using namespace std;

int main(int argc, char* argv[])
{
    unsigned int num_pointers = 262144;
    unsigned int depth = 12;
    if (argc > 1)
    {
        num_pointers = atoi(argv[1]);
        if (argc > 2)
        {
            depth = atoi(argv[2]);
        }
    }
    return 0;
}
