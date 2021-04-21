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
#include "../../orthogonal_linked/orthogonal_linked_list/Coordinate.h"
#include <chrono>

using namespace std;

void coordinate_benchmark_dimension_2(const at::Tensor& c1, const at::Tensor& c2, unsigned int const depth = 12)
{
    std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<2 ,std::vector<double>>> space = std::make_shared<vistart::orthogonal_linked_list::Coordinate<2, std::vector<double>>>();
}

void coordinate_benckmark(const at::Tensor& c1, const at::Tensor& c2, unsigned int const dimension = 2, unsigned int const depth = 12)
{
    std::cout << "To insert " << c1.size(0) << " pointers into the coordinated space with the depth of " << depth << ":" << std::endl;
    if (dimension == 2) {
        coordinate_benchmark_dimension_2(c1, c2, depth);
    }
}

int main(int argc, char* argv[])
{
    unsigned int num_pointers = 262144;
    unsigned int depth = 12;
    unsigned int dimension = 2;
    if (argc > 1)
    {
        //dimension = atoi(argv[1]);
    }
    if (argc > 2)
    {
        num_pointers = atoi(argv[2]);
    }
    if (argc > 3)
    {
        depth = atoi(argv[3]);
    }
    if (num_pointers < 100000 || depth < 4) {
        std::cout << "The total of pointers should not be less than 100000, and the depth should not be less than 4." << std::endl;
        return 0;
    }
    torch::manual_seed(1);
    const at::Tensor coords = at::rand({num_pointers, dimension});
    const at::Tensor coords_n = at::rand({num_pointers, dimension});
    const auto& c1 = torch::clamp(torch::round(coords * pow(2, depth)), 0, pow(2, depth) - 1);
    const auto& c1_n = torch::clamp(torch::round(coords_n * pow(2, depth)), 0, pow(2, depth) - 1);
    const at::Tensor coords_to_be_compared = at::rand({num_pointers, dimension});
    const at::Tensor coords_to_be_compared_n = at::randn({num_pointers, dimension});
    const auto& c2 = torch::clamp(torch::round(coords_to_be_compared * pow(2, depth)), 0, pow(2, depth) - 1);
    const auto& c2_n = torch::clamp(torch::round(coords_to_be_compared_n * pow(2, depth)), 0, pow(2, depth) - 1);

    coordinate_benckmark(c1, c2, dimension, depth);

    return 0;
}