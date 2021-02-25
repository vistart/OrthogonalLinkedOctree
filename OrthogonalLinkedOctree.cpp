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

#include "file_format/plyfile/PlyFile.h"
#include "orthogonal_linked/orthogonal_linked_octree/LinkedOctree.h"
#include <torch/torch.h>
#include "file_format/point_cloud_base_presentation/Point.h"
//#include "orthogonal_linked/orthogonal_linked_octree_with_torch/LinkedOctree.h"
#ifdef _DEBUG
#include <chrono>
#endif

using namespace std;

int main(int argc, char* argv[])
{

	if (argc < 2)
	{
		cout << "Invalid File Path!" << endl;
		return 0;
	}
	string file_path(argv[1]);
	unsigned char depth = 8;
	if (argc > 2)
	{
		istringstream str1(argv[2]);
		unsigned int received = 0;
		str1 >> received;
		depth = received & 0xFF;
	}

	// This statement (construct the PlyFile) will read the ply file.
	cout << "Reading the ply file: " << file_path << endl;
	const auto plyfile = make_shared<vistart::point_cloud_base_presentation::PlyFile>(file_path);
	cout << endl;
    if (plyfile->GetIsValid()) {
        const auto point_list = plyfile->GetPointList();
        cout << "The last point is: " << *point_list->GetPoints()->back() << endl;

        cout << "Construct the Octree of Point Cloud: " << endl;
        vistart::orthogonal_linked_octree::LinkedOctree<vistart::point_cloud_base_presentation::PlyVertexList, vistart::point_cloud_base_presentation::PlyVertex, vistart::point_cloud_base_presentation::PlyFile> o(point_list, depth);
//#ifdef _DEBUG
        const chrono::steady_clock::time_point time_start = chrono::steady_clock::now();
//#endif
        cout << o.GetAllSizes() << endl;
//#ifdef _DEBUG
        const chrono::steady_clock::time_point time_end_read_header = chrono::steady_clock::now();
        const chrono::duration<double> duration_read_header = chrono::duration_cast<chrono::duration<double>>(time_end_read_header - time_start);
        cout << "Time elapsed of getting all sizes: " << duration_read_header.count() << " s" << endl;
//#endif
    } else
	cout << "Invalid file!\n";
     /*
#ifdef _DEBUG
    const chrono::steady_clock::time_point time_start = chrono::steady_clock::now();
#endif
    for (int i = 0; i < 10; i++) {
        const auto& r1 = at::rand({3, 0x10000});
        const unsigned int total = 6;
        const auto octree = std::make_shared<vistart::orthogonal_linked_octree_with_torch::LinkedOctree<vistart::point_cloud_base_presentation::Point>>(r1.transpose(0, 1), total);
        unsigned int count = 0;
        for (unsigned int a = 0; a < pow(2, total); a++)
            for (unsigned int b = 0; b < pow(2, total); b++)
                for (unsigned int c = 0; c < pow(2, total); c++)
                {
                    const auto& c2 = std::vector({ a, b, c});
                    const auto& p = octree->get(c2);
                    if (p) {
                        //std::cout << "(" << c2[0] << "," << c2[1] << "," << c2[2] << "): " << p->size() << std::endl;
                        count++;
                    }
                }
        std::cout << count << std::endl;
        std::cout << octree->GetAllSizes() << std::endl;
    }

#ifdef _DEBUG
    const chrono::steady_clock::time_point time_end_read_header = chrono::steady_clock::now();
    const chrono::duration<double> duration_read_header = chrono::duration_cast<chrono::duration<double>>(time_end_read_header - time_start);
    cout << "Time elapsed of 10 times: " << duration_read_header.count() << " s" << endl;
#endif*/
    return 0;
}
