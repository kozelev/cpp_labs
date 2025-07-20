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
    
    out << "Item information:\n";
    out << "{\n";
    out << "\tName: " << info.name_ << '\n';
    out << "\tAmount: " << info.amount_ << '\n';
    if (info.durability_.has_value()) {
        out << "\tDurability: " << info.durability_.value() << '\n';
    }
    out << (info.is_stackable_ ? "\tStackable" : "\tNot stackable") << '\n';
    out << (info.is_selected_ ? "\tSelected" : "\tNot selected") << '\n';
    out << "}\n";
    
    return out;
}
