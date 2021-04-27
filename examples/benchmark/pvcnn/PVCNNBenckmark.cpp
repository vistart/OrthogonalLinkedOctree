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
#include "voxelization/vox.hpp"
#include "ball_query/ball_query.hpp"
#include <torch/torch.h>
#include <chrono>
void PVCNNBenchmark(const at::Tensor& c1, const at::Tensor& c2, unsigned int depth = 12)
{
    const auto c1_size = c1.size(0);
    std::chrono::steady_clock::time_point time_start1 = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point time_stop;
    ball_query_forward(c1.cuda(), c2.cuda(), 1, 100);
    time_stop = std::chrono::steady_clock::now();
    const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
    std::cout << "1 queried." << " Elapsed: " << duration.count() << " s" << std::endl;
    time_start1 = std::chrono::steady_clock::now();
}
int main(int argc, char* argv[])
{
	std::cout << "PVCNNBenchmark: " << std::endl;
    unsigned int num_pointers = 262144;
    unsigned int batch = 240;
    unsigned int mode = 3;
    if (argc > 1)
    {
        mode = atoi(argv[1]);
    }
    if (argc > 2)
    {
        num_pointers = atoi(argv[2]);
    }
    if (argc > 3)
    {
        batch = atoi(argv[3]);
    }
    if (num_pointers < 100000 || batch < 4) {
        std::cout << "The total of pointers should not be less than 100000, and the batch should not be less than 4." << std::endl;
        return 0;
    }
    torch::manual_seed(1);
    const at::Tensor coords = at::rand({batch, 3, num_pointers / batch});
    const auto& c1 = torch::clamp(torch::round(coords * pow(2, 12)), 0, pow(2, 12) - 1);
    const at::Tensor coords_to_be_compared = at::rand({batch, 3, num_pointers / batch});
    const auto& c2 = torch::clamp(torch::round(coords_to_be_compared * pow(2, 12)), 0, pow(2, 12) - 1);
    PVCNNBenchmark(c1, c2);
	return 0;
}