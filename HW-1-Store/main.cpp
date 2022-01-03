#include "MyStore.hpp"

int main() {
    MyStore my_store;
    int W, C;
    std::cin >> W >> C;
    //std::vector<Client*> clients_list;
    my_store.init(W, 0, 0);
    for(int i = 0; i < C; i++) {
        int arrive_min, banana, schweppes, max_wait;
        std::cin >> arrive_min;
        std::cin >> banana;
        std::cin >> schweppes;
        std::cin >> max_wait;

        Client *cl = new Client{arrive_min, banana, schweppes, max_wait};
        //clients_list.push_back(cl);
        my_store.addClients(cl,1);
        delete cl;
    }

    my_store.advanceTo(200);
}