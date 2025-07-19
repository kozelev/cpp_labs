#include "log.h"
#include "sword.h"



int main() {

    Item* l = new Log(LogType::OAK, 123);
    l->select();
    std::cout << "------------------------------------------------";
    std::cout << "\nBefore using:\n";
    l->print_info();
    l->use();
    std::cout << "\nAfter using\n";
    l->print_info();
    delete l;
    std::cout << "------------------------------------------------";

    std::cout << "------------------------------------------------";
    Item* s = new Sword(SwordType::NETHERITE, 1);
    s->select();
    std::cout << "\nBefore using:\n";
    s->print_info();
    s->use();
    std::cout << "\nAfter using\n";
    s->print_info();
    delete s;
    std::cout << "------------------------------------------------";

    return 0;
}
