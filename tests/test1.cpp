
#include <algorithm>
#include <iostream>

#include "morphsnakes.h"

std::ostream& operator<<(std::ostream& ostr, const morphsnakes::Position<2>& pos)
{
    ostr << pos.offset << "(" << pos.coord[0] << ", " << pos.coord[1] << ")";
    return ostr;
}

int main()
{
    int data[100];
    std::fill(data, data+100, 0);
    
    std::array<int, 2> shape = {10, 10};
    std::array<int, 2> strides = {sizeof(int) * 10, sizeof(int)};
    
    data[45] = 1;
    
    morphsnakes::NDImage<int, 2> image(data, shape, strides);
    
    // for(auto aux : image)
    // {
    //     std::cout << aux << " " << image[aux.offset] << std::endl;
    //     if(morphsnakes::isBoundary<2>(aux, image.shape))
    //         continue;
    //
    //     for(auto n : image.neighborhood(aux))
    //         std::cout << "\t" << n << " " << image[n] << std::endl;
    // }
    
    // morphsnakes::CellMap cellMap = createCellMap(image);
    // std::cout << cellMap << std::endl;
    morphsnakes::NarrowBand<2> narrowBand(image);
    auto cellMap = narrowBand.getCellMap();
    
    for(auto c : narrowBand.getCellMap())
    {
        if(c.first.offset == 180)
            narrowBand.toggleCell(c.first);
        
        std::cout << c.first << " " << c.second.toggle << " " << image[c.first] << std::endl;
    }
    
    std::cout << std::endl;
    
    morphsnakes::morph_op(morphsnakes::curv_operator_2d, true, narrowBand);
    
    // narrowBand.flush();
    // for(auto c : narrowBand.getCellMap())
    // {
    //     std::cout << c.first << " " << c.second.toggle << " " << image[c.first] << std::endl;
    // }
    //
    // std::cout << std::endl;
    //
    // narrowBand.prune();
    // for(auto c : narrowBand.getCellMap())
    // {
    //     std::cout << c.first << " " << c.second.toggle << " " << image[c.first] << std::endl;
    // }
    
    return 0;
}
