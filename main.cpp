#include <iostream>
#include <functional>
class Server{
public:
    void connection(int k,int m){
        std::cout<<"yes"<<std::endl;
    }
private:

};
int main() {
    std::cout << "Hello, World!" << std::endl;
    Server s;
    std::function<void(int,int)> f = std::bind(&Server::connection,&s);
    return 0;
}