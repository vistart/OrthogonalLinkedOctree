/*
 *  _   __ __ _____ _____ ___  ____  _____
 * | | / // // ___//_  _//   ||  __||_   _|
 * | |/ // /(__  )  / / / /| || |     | |
 * |___//_//____/  /_/ /_/ |_||_|     |_|
 * @link https://vistart.me/
 * @copyright Copyright (c) 2019 - 2021 vistart
 * @license https://vistart.me/license/
*/
//

#include <iostream>
#include <sstream>
#include <memory>
#include <cmath>

#include <torch/torch.h>
#include "../file_format/point_cloud_base_presentation/Point.h"
#include "../orthogonal_linked/orthogonal_linked_octree_with_torch/LinkedOctree.h"
#ifdef _DEBUG
#include <chrono>
#endif

using namespace std;

int main(int argc, char* argv[])
{
#ifdef _DEBUG
   const chrono::steady_clock::time_point time_start = chrono::steady_clock::now();
#endif
   for (int i = 0; i < 10; i++) {
       const auto& r1 = at::rand({3, 0x10000});
       const unsigned int total = 6;
       const auto octree =
               std::make_shared<vistart::orthogonal_linked_octree_with_torch::LinkedOctree<vistart::point_cloud_base_presentation::Point>>
                       (r1.transpose(0, 1), total);
       unsigned int count = 0;
       unsigned int cout_count = 0;
       for (unsigned int a = 0; a < pow(2, total); a++)
           for (unsigned int b = 0; b < pow(2, total); b++)
               for (unsigned int c = 0; c < pow(2, total); c++)
               {
                   const auto& c2 = std::vector({ a, b, c});
                   const auto& p = octree->get(c2);
                   if (p) {
                       //std::cout << "(" << c2[0] << "," << c2[1] << "," << c2[2] << "): " << p->size() << std::endl;
                       count++;
                       if (cout_count < 10) {
                           std::cout << "reciprocal: " << octree->GetReciprocalOfSize(c2) << std::endl;
                           cout_count++;
                       }
                   }
               }
       std::cout << count << " | size:" << octree->GetAllSizes() << std::endl;
   }

#ifdef _DEBUG
   const chrono::steady_clock::time_point time_end_read_header = chrono::steady_clock::now();
   const chrono::duration<double> duration_read_header = chrono::duration_cast<chrono::duration<double>>(time_end_read_header - time_start);
   cout << "Time elapsed of 10 times: " << duration_read_header.count() << " s" << endl;
#endif
    return 0;
}
