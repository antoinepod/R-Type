#include "serialization/serialization.hpp"

int main() {
    RType::Network::Seria serialization;
    std::pair<std::vector<RType::Network::PlayerObject>, std::vector<RType::Network::EnemyObject>> gameObject = RType::Network::populateObject();

    //serialization.S_erialize(gameObject);
}