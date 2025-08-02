#pragma once

#include "item.h"


#include <unordered_map>


using CellNumber = uint32_t;


// class Composite
class Inventory: public Item {
private:
    std::unordered_map<CellNumber, ItemPtr> inventory_;
public:
    
    

};

