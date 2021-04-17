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
#include "../orthogonal_linked/orthogonal_linked_octree/LinkedOctree.h"
#include "../orthogonal_linked/orthogonal_linked_list/Coordinate.h"
#include "../file_format/plyfile/PlyVertexList.h"
#include "../file_format/plyfile/PlyVertex.h"
#include "../file_format/plyfile/PlyFile.h"
#include <chrono>


using namespace std;

void orthogonal_linked_octree_benchmark(const at::Tensor& c1, const at::Tensor& c2, unsigned int depth = 12)
{
    std::cout << "To insert " << c1.size(0) << " pointers into the orthogonal linked space with the depth of " << depth << ":" << std::endl;
    std::shared_ptr<vistart::orthogonal_linked_list::LinkedCoordinate<3,std::vector<double>>> space = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<3,std::vector<double>>>();

    // Inserting
    const auto c1_size = c1.size(0);
    std::chrono::steady_clock::time_point time_start1 = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point time_stop;
    for (int i = 0; i < c1_size; i++)
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
            std::cout << (i + 1) / 1000 << "k inserted." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    if (c1_size % 100000) {
        time_stop = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
        std::cout << c1_size % 100000 << " inserted." << " Elapsed: " << duration_set.count() << " s" << std::endl;
    }

    // Iterating
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

    // Checking if exists
    std::cout << "Checking if exists: " << std::endl;
    const auto c2_size = c2.size(0);
    time_start1 = std::chrono::steady_clock::now();
    for(int i=0; i < c2_size; i++)
    {
        std::vector<double> t{
                static_cast<double>(c2[i][0].item().toFloat()),
                static_cast<double>(c2[i][1].item().toFloat()),
                static_cast<double>(c2[i][2].item().toFloat())
        };
        space->exists(
                {static_cast<unsigned int>(c2[i][0].item().toInt()),
                 static_cast<unsigned int>(c2[i][1].item().toInt()),
                 static_cast<unsigned int>(c2[i][2].item().toInt())}
        );
        if (i % 100000 == 99999) {
            time_stop = std::chrono::steady_clock::now();
            const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
            std::cout << (i + 1) / 1000 << "k checked." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    if (c2_size % 100000) {
        time_stop = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
        std::cout << c2_size % 100000 << " checked." << " Elapsed: " << duration_set.count() << " s" << std::endl;
    }

    // Getting Tensor
    std::cout << "Getting Tensors (radius: 2): " << std::endl;
    const auto radius = 2;

    namespace vp = vistart::point_cloud_base_presentation;

    std::shared_ptr<vistart::orthogonal_linked_octree::LinkedOctree<
            vp::PlyVertexList,
            vp::PlyVertex,
            vp::PlyFile>> pl;
    iter = space->begin();
    time_start1 = std::chrono::steady_clock::now();
    while (iter != space->end())
    {
        //std::cout << **iter << std::endl;
        std::vector<unsigned int> c0({
            static_cast<unsigned int>((**iter)[0]),
            static_cast<unsigned int>((**iter)[1]),
            static_cast<unsigned int>((**iter)[2])});
        auto result = space->get_tensor(c0, radius);
        iter++;
    }

    // Erasing
    std::cout << "Erasing all voxels: " << std::endl;
    time_start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < c1_size; i++)
    {
        std::vector<double> t {
                static_cast<double>(c1[i][0].item().toFloat()),
                static_cast<double>(c1[i][1].item().toFloat()),
                static_cast<double>(c1[i][2].item().toFloat())
        };
        space->erase({
                             static_cast<unsigned int>(c1[i][0].item().toInt()),
                             static_cast<unsigned int>(c1[i][1].item().toInt()),
                             static_cast<unsigned int>(c1[i][2].item().toInt())
                     }
        );
        if (i % 100000 == 99999) {
            time_stop = std::chrono::steady_clock::now();
            const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
            std::cout << (i + 1) / 1000 << "k erased." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    if (c1_size % 100000) {
        time_stop = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
        std::cout << c1_size % 100000 << " erased." << " Elapsed: " << duration_set.count() << " s" << std::endl;
    }
    std::cout << "The remaining voxel(s): " << space->size() << std::endl;
}

void coordinated_octree_benchmark(const at::Tensor& c1, const at::Tensor& c2, unsigned int depth = 12)
{
    std::cout << "To insert " << c1.size(0) << " pointers into the coordinated space with the depth of " << depth << ":" << std::endl;
    std::shared_ptr<vistart::orthogonal_linked_list::Coordinate<3,std::vector<double>>> space = std::make_shared<vistart::orthogonal_linked_list::LinkedCoordinate<3,std::vector<double>>>();

    // Inserting
    const auto c1_size = c1.size(0);
    std::chrono::steady_clock::time_point time_start1 = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point time_stop;
    for (int i = 0; i < c1_size; i++)
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
            std::cout << (i + 1) / 1000 << "k inserted." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    if (c1_size % 100000) {
        time_stop = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
        std::cout << c1_size % 100000 << " inserted." << " Elapsed: " << duration_set.count() << " s" << std::endl;
    }

    // Checking if exists
    std::cout << "Checking if exists: " << std::endl;
    const auto c2_size = c2.size(0);
    time_start1 = std::chrono::steady_clock::now();
    for(int i=0; i< c2_size; i++)
    {
        std::vector<double> t{
                static_cast<double>(c2[i][0].item().toFloat()),
                static_cast<double>(c2[i][1].item().toFloat()),
                static_cast<double>(c2[i][2].item().toFloat())
        };
        space->exists(
                {static_cast<unsigned int>(c2[i][0].item().toInt()),
                 static_cast<unsigned int>(c2[i][1].item().toInt()),
                 static_cast<unsigned int>(c2[i][2].item().toInt())}
        );
        if (i % 100000 == 99999) {
            time_stop = std::chrono::steady_clock::now();
            const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
            std::cout << (i + 1) / 1000 << "k checked." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    if (c2_size % 100000) {
        time_stop = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
        std::cout << c2_size % 100000 << " checked." << " Elapsed: " << duration_set.count() << " s" << std::endl;
    }

    // Erasing
    std::cout << "Erasing all voxels: " << std::endl;
    time_start1 = std::chrono::steady_clock::now();
    for (int i = 0; i < c1_size; i++)
    {
        std::vector<double> t {
                static_cast<double>(c1[i][0].item().toFloat()),
                static_cast<double>(c1[i][1].item().toFloat()),
                static_cast<double>(c1[i][2].item().toFloat())
        };
        space->erase({
                             static_cast<unsigned int>(c1[i][0].item().toInt()),
                             static_cast<unsigned int>(c1[i][1].item().toInt()),
                             static_cast<unsigned int>(c1[i][2].item().toInt())
                     }
        );
        if (i % 100000 == 99999) {
            time_stop = std::chrono::steady_clock::now();
            const std::chrono::duration<double> duration = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
            std::cout << (i + 1) / 1000 << "k erased." << " Elapsed: " << duration.count() << " s" << std::endl;
            time_start1 = std::chrono::steady_clock::now();
        }
    }
    if (c1_size % 100000) {
        time_stop = std::chrono::steady_clock::now();
        const std::chrono::duration<double> duration_set = std::chrono::duration_cast<std::chrono::duration<double>>(time_stop - time_start1);
        std::cout << c1_size % 100000 << " erased." << " Elapsed: " << duration_set.count() << " s" << std::endl;
    }
    std::cout << "The remaining voxel(s): " << space->size() << std::endl;
}

int main(int argc, char* argv[])
{
    unsigned int num_pointers = 262144;
    unsigned int depth = 12;
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
        depth = atoi(argv[3]);
    }
    if (num_pointers < 100000 || depth < 4) {
        std::cout << "The total of pointers should not be less than 100000, and the depth should not be less than 4." << std::endl;
        return 0;
    }
    torch::manual_seed(1);
    const at::Tensor coords = at::rand({num_pointers, 3});
    const auto& c1 = torch::clamp(torch::round(coords * pow(2, depth)), 0, pow(2, depth) - 1);
    const at::Tensor coords_to_be_compared = at::rand({num_pointers, 3});
    const auto& c2 = torch::clamp(torch::round(coords_to_be_compared * pow(2, depth)), 0, pow(2, depth) - 1);

    if (mode & 1 == 1) coordinated_octree_benchmark(c1, c2, depth);
    if (mode & 2 == 2) orthogonal_linked_octree_benchmark(c1, c2, depth);
    return 0;
}
