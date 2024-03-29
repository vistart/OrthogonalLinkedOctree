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

#include "../file_format/plyfile/PlyFile.h"
#include "../orthogonal_linked/orthogonal_linked_octree/LinkedOctree.h"
#include <torch/torch.h>
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
    return 0;
}
