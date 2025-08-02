#include "log.h"
#include "sword.h"
#include "dirt.h"
#include  "inventory.h"


int main() {

    ItemPtr oak_logs = std::make_unique<Log>(LogType::OAK, 123);
    ItemPtr netherite_sword = std::make_unique<Sword>(SwordType::NETHERITE, 1);
    ItemPtr dirt = std::make_unique<Dirt>(32);

    InventoryPtr inventory = std::make_unique<Inventory>();
    inventory->add_item(std::move(oak_logs));
    inventory->add_item(std::move(netherite_sword));
    

    ItemPtr acacia_logs = std::make_unique<Log>(LogType::ACACIA, 12);
    ItemPtr spruce_logs = std::make_unique<Log>(LogType::SPRUCE, 48);
    ItemPtr diamond_sword = std::make_unique<Sword>(SwordType::DIAMOND, 128);
    ItemPtr one_more_dirt = std::make_unique<Dirt>(64);
    ItemPtr wooden_sword = std::make_unique<Sword>(SwordType::WOODEN, 16);
    ItemPtr still_one_more_dirt = std::make_unique<Dirt>(128);

    InventoryPtr shulker = std::make_unique<Inventory>();
    shulker->add_item(std::move(acacia_logs));
    shulker->add_item(std::move(spruce_logs));
    shulker->add_item(std::move(diamond_sword));
    shulker->add_item(std::move(one_more_dirt));
    shulker->add_item(std::move(wooden_sword));
    shulker->add_item(std::move(still_one_more_dirt));


    inventory->add_item(std::move(shulker));
    inventory->add_item(std::move(dirt));
    std::cout << "Print with all unselected items:\n";
    // all items are unselected
    inventory->print_info();
    
    std::cout << std::endl;
    
    // select and print selected items
    inventory->select();
    std::cout << "Print with all selected items:\n";
    inventory->print_info();

    return 0;
}
