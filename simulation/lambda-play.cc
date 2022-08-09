#include <iostream>


int main() {

    int a = 22;

    auto myLambda = [value = a](int input) {
        std::cout << value + input << std::endl;
    };

    myLambda(3);
    
}