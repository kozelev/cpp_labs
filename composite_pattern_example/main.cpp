#include "log.h"
#include "sword.h"
#include "dirt.h"



int main() {

    Item* l = new Log(LogType::OAK, 123);
    l->select();
    std::cout << "------------------------------------------------\n";
    std::cout << "Before using:\n";
    l->print_info();

    std::cout << std::endl;

    std::cout << "After using:\n";
    l->use();
    l->print_info();
    delete l;
    std::cout << "------------------------------------------------\n";

    std::cout << "------------------------------------------------\n";
    Item* s = new Sword(SwordType::NETHERITE, 1);
    s->select();
    std::cout << "Before using:\n";
    s->print_info();
    
    std::cout << std::endl;

    std::cout << "After using\n";
    s->use();
    s->print_info();
    delete s;
    std::cout << "------------------------------------------------\n";

    std::cout << "------------------------------------------------\n";
    Item* d = new Dirt(32);
    d->select();
    std::cout << "Before using:\n";
    d->print_info();
    
    std::cout << std::endl;

    std::cout << "After using\n";
    d->use();
    d->print_info();
    delete d;
    std::cout << "------------------------------------------------\n";
    

    return 0;
}
