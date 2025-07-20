#pragma once

#include "item_info.h"

// abstracte base class, which represents 
// item's interface
class Item {
protected:
    ItemInfo info_;

protected:
    Item(ItemInfo info): info_(info) {}

public:
    void select() {
        info_.is_selected_ = true;
    }
    
    void deselect() {
        info_.is_selected_ = false;
    }

    virtual void print_info() const = 0;
    virtual void use() = 0;
    
    // virtual dtor
    virtual ~Item() = default;
};

