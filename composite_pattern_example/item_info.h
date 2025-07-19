#pragma once

#include <optional>
#include <string>
#include <cstdint>
#include <iostream>


struct ItemInfo {
    std::string name_ = "";
    uint32_t amount_ = 0;
    std::optional<uint32_t> durability_ = std::nullopt;
    bool is_stackable_ = false;
    bool is_selected_ = false;
};


inline std::ostream& operator<<(std::ostream& out, const ItemInfo& info) {
    
    out << "Name: " << info.name_ << '\n';
    out << "Amount: " << info.amount_ << '\n';
    if (info.durability_.has_value()) {
        out << "Durability: " << info.durability_.value() << '\n';
    }
    
    return out;
}
