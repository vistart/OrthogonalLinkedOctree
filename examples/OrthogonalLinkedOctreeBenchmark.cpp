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
    if (num_pointers < 100000 || depth < 4) {
        std::cout << "The total of pointers should not be less than 100000, and the depth should not be less than 4." << std::endl;
        return 0;
    }
    std::cout << "To insert " << num_pointers << " pointers into the space with the depth of " << depth << ":" << std::endl;
    const at::Tensor coords = at::rand({num_pointers, 3});
    const auto& c1 = torch::clamp(torch::round(coords * pow(2, depth)), 0, pow(2, depth) - 1);
    std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<3,std::vector<double>>> space = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<3,std::vector<double>>>();

    std::chrono::steady_clock::time_point time_start1 = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point time_stop;
    for (int i = 0; i < coords.size(0); i++)
    {
        std::vector<double> t {
                static_cast<double>(c1[i][0].item().toFloat()),
                static_cast<double>(c1[i][1].item().toFloat()),
                static_cast<double>(c1[i][2].item().toFloat())
        };
        space->set({
                             static_cast<unsigned int>(c1[i][0].item().toInt()),
                             static_cast<unsigned int>(c1[i][1].item().toInt()),
                             static_cast<unsigned int>(c1[i][2].item().toInt())
                     },
                     std::make_shared<std::vector<double>>(t)
        );
        if (i % 100000 == 99999) {
            time_stop = std::chrono::steady_clock::now();
            const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
            std::cout << i + 1 << " inserted." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    time_stop = std::chrono::steady_clock::now();
    const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
    std::cout << coords.size(0) % 100000 << " inserted." << " Elapsed: " << duration_set.count() << " s" << std::endl;

    auto iter = space->begin();
    unsigned int count = 0;
    const std::chrono::steady_clock::time_point time_start2 = std::chrono::steady_clock::now();
    while (iter != space->end())
    {
        // std::cout << *iter << "(USE_COUNT: " << (*iter)->size() << ") :" << **iter << std::endl;
        iter++;
        count++;
    }
    const std::chrono::steady_clock::time_point time_end = std::chrono::steady_clock::now();
    const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_end - time_start2);
    std::cout << "Time elapsed of accessing all voxels: " << duration.count() << " s" << std::endl;
    std::cout << "Count: " << count << std::endl;
    return 0;
}
