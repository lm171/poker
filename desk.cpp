#include "desk.h"

desk::desk()
{
    std::ifstream file("/root/poker/poker/CardLibrary");
    if (!file.is_open()) {
        std::cerr << "牌库加载失败!" << endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        people::poker Poker;
        iss >> Poker.num >> Poker.name >> Poker.color;
        library.push_back(Poker);
    }
    file.close();

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(library.begin(), library.end(), g);

    p1 = new people;
    p2 = new people;
    p3 = new people;
}

void desk::touchCard() //从牌库中抽取一张牌加入到手牌
{
    std::vector<people::poker> p1Hand;
    std::vector<people::poker> p2Hand;
    std::vector<people::poker> p3Hand;
    for (int i = 0; i < 17; i++) {
        if (library.begin() == library.end()) {
            cout << "No poker in it." << endl;
            return;
        }
        auto c = library.begin();
        p1Hand.push_back(*c);
        library.erase(library.begin());
        p2Hand.push_back(*c);
        library.erase(library.begin());
        p3Hand.push_back(*c);
        library.erase(library.begin());
    }
    p1->setHand(p1Hand);
    p2->setHand(p2Hand);
    p3->setHand(p3Hand);
}