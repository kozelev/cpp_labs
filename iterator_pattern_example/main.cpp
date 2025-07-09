#include "simple_container.h"
#include <ostream>


void PrintContainterWithIterator(const Container& c) {
    
    std::cout << "Print Containter With Pattern Iterator:" << std::endl;
    auto it = c.CreateIterator();
    for (it->First(); !it->IsDone(); it->Next()) {
        std::cout << it->CurrentItem() << ' ';;
    }
    delete it;
}


int main() {

    Container c(5);
    c.Push(1);
    c.Push(2);
    c.Push(3);
    c.Push(4);
    c.Push(5);

    std::cout << "Print Containter With std::cout:\n";
    std::cout << c << std::endl;
    
    PrintContainterWithIterator(c);
    std::cout << std::endl;

    return 0;
}
