#include "Events.h"
#include <chrono>
#include <thread>

ItemType getRandomItemType(shared_ptr<Hero>&h) {
    int type = static_cast<int>(round(makeRand(0, 3)));

    if (h->getProf() == warrior) {
        type += static_cast<int>(round(makeRand(0, 1)));
    }

    ItemType itemType;
    if (type == 0)
        itemType = weapon;
    else if (type == 1)
        itemType = armor;
    else if (type == 2)
        itemType = headgear;
    else if (type == 3)
        itemType = talisman;
    else
        itemType = shield;

    return itemType;
}


void Chest::openBox(shared_ptr<Hero>& h) {
    const ItemType itemType = getRandomItemType(h);
    shared_ptr<Item> item = ItemFactory::createItem(h->getlevel(), itemType, h->getProf());

    int coins = static_cast<int>(round(makeRand(0, h->getlevel() * 100)));

    cout << "You found " << coins << " gold in the chest" << endl;
    h->setMoney(h->getMoney() + coins);

    cout << "There is also an item in chest: " << endl;
    showItemDetails(item, h->getProf());
    cout << endl;
    cout << "Your current item: " << endl;
    h->showOneItem(item->getType(), h->getProf());
    cout << endl;

    cout << "Do you want to replace your item with a new found one? (Y/N)" << endl;

    char decision;
    while (true) {
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'Y')
            h->ChangeEQ(item);

        if (decision == 'Y' || decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}


// do dopisania w TXTView
void DescriptionVisitor::visitEndPoint(EndPoint event) {
    cout << "Get out of the room" << endl;
}
void DescriptionVisitor::visitEnterToMonsterRoom(EnterToMonsterRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitFight(Fight event) {
    cout << "Fight with the monster" << endl;
}
void DescriptionVisitor::visitRunAway(RunAway event) {
    cout << "Run away" << endl;
}
void DescriptionVisitor::visitCheckChest(CheckChest event) {
    cout << "Check the chest" << endl;
}
void DescriptionVisitor::visitEnterToTrapRoom(EnterToTrapRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitActiveTheTrap(ActiveTheTrap event) {
    cout << "Active the trap" << endl;
}
void DescriptionVisitor::visitEnterToPotionRoom(EnterToPotionRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitDrinkPotion(DrinkPotion event) {
    cout << "Drink the potion" << endl;
}
void DescriptionVisitor::visitEnterToTreasureRoom(EnterToTreasureRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitEnterToHealthRoom(EnterToHealthRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitHealthYourself(HealthYourself event) {
    cout << "Drink some water from the Fountain" << endl;
}
void DescriptionVisitor::visitEnterToTraderRoom(EnterToTraderRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitSeeItems(SeeItems event) {
    cout << "See items" << endl;
}
void DescriptionVisitor::visitEnterToEmptyRoom(EnterToEmptyRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitEnterToStartingRoom(EnterToStartingRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitEnterToBossRoom(EnterToBossRoom event) {
    cout << "" << endl;
}
void DescriptionVisitor::visitBossFight(BossFight event) {
    cout << "Final fight with BOSS" << endl;
}


void Event::Action(shared_ptr<Hero> &h) {}

Event::Event() {}


void EndPoint::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEndPoint(*this);
}
void EndPoint::Action(shared_ptr<Hero> &h) {
    char decision;
    while (true) {
        cout << "Do you want to check your Statistics (S), Equipment (E), or do nothing (N)?" << endl;
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'E') {
            h->showEQ();
        }
        else if(decision == 'S')
        {
            h->showStatistics();
        }
        else if (decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}


void EnterToMonsterRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToMonsterRoom(*this);
}
void EnterToMonsterRoom::Action(shared_ptr<Hero> &h) {
    cout << "You have entered the room with the monster" << endl;
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


void Fight::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitFight(*this);
}
void Fight::Action(shared_ptr<Hero> &h) {
    shared_ptr<monster> normal_monster = make_shared<monster>(h->getlevel(), 0);
    shared_ptr<Character> ch(normal_monster);
	h->fight(ch, 0);
    if (h->getcurrentHealth() > 0)
    {
        cout << "You have defeated a monster" << endl;
        cout << "Remaining health points: " << h->getcurrentHealth() << endl << endl;
        h->levelup();
        cout << "You have leveled up. Your current level is: " << h->getlevel() << endl;
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl << endl;
    }
}


void RunAway::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitRunAway(*this);
}
void RunAway::Action(shared_ptr<Hero> &h) {
    int chance = static_cast<int>(round(makeRand(0, 10)));

    if (chance < 3) {
        cout << "While escaping you got hit by a monster" << endl;
        h->getDamage(static_cast<int>(h->getcurrentHealth() * 0.2));
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
    }
    else
        cout << "You escaped the monster" << endl;
}


void CheckChest::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitCheckChest(*this);
}
void CheckChest::Action(shared_ptr<Hero> &h) {
    shared_ptr<Chest> chest = make_unique<Chest>();

    char decision;
    while (true) {
        cout << "You found mystery box. Do you want to open it? (Y/N)" << endl;
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'Y') {
            chest->openBox(h);
            break;
        }
        else if (decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}


void EnterToTrapRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToTrapRoom(*this);
}
void EnterToTrapRoom::Action(shared_ptr<Hero> &h) {
    cout << "You enter a chamber that appears to be empty..." << endl;
}


void ActiveTheTrap::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitActiveTheTrap(*this);
    cout << "Active the trap" << endl;
}
void ActiveTheTrap::Action(shared_ptr<Hero> &h) {
    cout << "There was a trap in the room that has hurted you" << endl;
    h->getDamage(static_cast<int>(h->getmaxHealth() * 0.2));
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


void EnterToPotionRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToPotionRoom(*this);
}
void EnterToPotionRoom::Action(shared_ptr<Hero> &h) {
    cout << "You have entered to room and saw a mysterious potion on the table" << endl;
}


void DrinkPotion::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitDrinkPotion(*this);
}
void DrinkPotion::Action(shared_ptr<Hero> &h) {
    int drawn_num = static_cast<int>(round(makeRand(0, 1)));

    if (drawn_num == 0) {
        h->setcurrentHealth(h->getmaxHealth());
        cout << "Your health has been restored" << endl;
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
    }
    else {
        h->getDamage(static_cast<int>(h->getmaxHealth() * 0.3));
        cout << "The potion was poisoned. You lost " << int(h->getmaxHealth() * 0.3) << " health" << endl;
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
    }
}


void EnterToTreasureRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToTreasureRoom(*this);
}
void EnterToTreasureRoom::Action(shared_ptr<Hero> &h) {
    cout << "You have entered to room and saw a chest by the wall" << endl;
}


void EnterToHealthRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToHealthRoom(*this);
}
void EnterToHealthRoom::Action(shared_ptr<Hero> &h) {
    cout << "Upon entering the room, the Ancient Fountain of Life appeared before your eyes" << endl;
}


void HealthYourself::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitHealthYourself(*this);
}
void HealthYourself::Action(shared_ptr<Hero> &h) {
    cout << "After drinking the magic water you regain all health points" << endl;
    h->setcurrentHealth(h->getmaxHealth());
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}


void EnterToTraderRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToTraderRoom(*this);
}
void EnterToTraderRoom::Action(shared_ptr<Hero> &h) {
    cout << "You have enter the room and saw the stand of a traveling trader who wants to offer you his items" << endl;
}


void SeeItems::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitSeeItems(*this);
}
void SeeItems::Action(shared_ptr<Hero> &h) {
    shared_ptr<Item> item1 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
    shared_ptr<Item> item2 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
    shared_ptr<Item> item3 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());

    h->showEQ();
    cout << endl;

    cout << "Merchant items:" << endl;
    cout << "item 1:" << endl;
    showItemDetails(item1, h->getProf());
    cout << "price: " << item1->getValue() << endl << endl;

    cout << "item 2:" << endl;
    showItemDetails(item2, h->getProf());
    cout << "price: " << item2->getValue() << endl << endl;

    cout << "item 3:" << endl;
    showItemDetails(item3, h->getProf());
    cout << "price: " << item3->getValue() << endl << endl;

    cout << "Your balance: " << h->getMoney() << endl;

    char wantToBuy;
    cout << "Do you want to buy something? (Y/N)" << endl;
    cin >> wantToBuy;
    wantToBuy = makeBig(wantToBuy);

    if (wantToBuy == 'Y')
        BuyItems(h, item1, item2, item3);
}
void SeeItems::BuyItems(shared_ptr<Hero> &h, shared_ptr<Item> &i1, shared_ptr<Item> &i2, shared_ptr<Item> &i3) {
    bool wantToBuy = true;
    string l_playerDecision{};
    char player_decision;
    bool bought1 = false, bought2 = false, bought3 = false;

    while (wantToBuy)
    {
        cout << "Enter the number of the item you want to buy:" << endl;
        cin >> l_playerDecision;
        l_playerDecision=makeBig(l_playerDecision);
        int num{ 0 };
        try
        {
            num = stoi(l_playerDecision);
        }
        catch(exception &e)
        {
	        
        }
        if (num == 1) {
            if (!bought1) {
                showItemDetails(i1, h->getProf());
                bought1 = buyOneItem(h, i1);
            }
            else {
                cout << "You have already bought this item" << endl;
            }
        }
        else if (num == 2) {
            if (!bought2) {
                showItemDetails(i2, h->getProf());
                bought2 = buyOneItem(h, i2);
            }
            else {
                cout << "You have already bought this item" << endl;
            }
        }
        else if (num == 3) {
            if (!bought3) {
                showItemDetails(i3, h->getProf());
                bought3 = buyOneItem(h, i3);
               
            }
            else {
                cout << "You have already bought this item" << endl;
            }
        }
        else {
            cout << "Invalid item number, try again" << endl;
        }

        if (!bought1 || !bought2 || !bought3) {
            cout << "Your balance: " << h->getMoney() << endl;
            cout << "Do you want to buy anything else? (Y/N)" << endl;

            while (true) {
                cin >> player_decision;
                player_decision = makeBig(player_decision);
                if (player_decision == 'N')
                    wantToBuy = false;

                if (player_decision == 'Y' || player_decision == 'N')
                    break;
                else
                    cout << "Character not recognized, please retype" << endl;
            }
        }
        else {
            cout << "You already bought all items from the merchant..." << endl;
            wantToBuy = false;
        }
    }
}
bool SeeItems::buyOneItem(shared_ptr<Hero> &h, shared_ptr<Item> &item) {
    shared_ptr<Item> _buyingItem = item;
    bool _flag = false;

    shared_ptr<Strategy> _buyingStrategy = make_unique<StandardStrategy>(h);
    _buyingStrategy->setStartingPrice(_buyingItem->getValue());

    while (!_flag)
    {
        char player_decision;

    	cout << "Do you want to negotiate price of this item? (Y/N)" << endl;
        while (true) {
            cin >> player_decision;
            player_decision = makeBig(player_decision);
            if (player_decision == 'Y' || player_decision == 'N')
                break;
            else
                cout << "Character not recognized, please retype" << endl;
        }
        if(player_decision=='N')
        {
            break;
        }
        cout << "Enter the price at which you would like to buy item: " << endl;
        int price;
        cin >> price;
        _flag = _buyingStrategy->buyingProcess(price);
    }
    if(_flag)
    {
        h->ChangeEQ(_buyingItem);
    }
    return _flag;
	
}


void EnterToEmptyRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToEmptyRoom(*this);
}
void EnterToEmptyRoom::Action(shared_ptr<Hero> &h) {
    cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
}


void EnterToStartingRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToStartingRoom(*this);
}
void EnterToStartingRoom::Action(shared_ptr<Hero> &h) {
    cout << "Your adventure begins here" << endl;
}


void EnterToBossRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToBossRoom(*this);
}
void EnterToBossRoom::Action(shared_ptr<Hero> &h) {
    chrono::milliseconds timespan(1000);
    this_thread::sleep_for(timespan);
    cout << "You have entered the boss's chamber" << endl;
    this_thread::sleep_for(timespan);
    cout << "The last and hardest fight is ahead of you" << endl;
    this_thread::sleep_for(timespan);
}


void BossFight::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitBossFight(*this);
}
void BossFight::Action(shared_ptr<Hero> &h) {
    shared_ptr<monster> boss_monster = make_shared<monster>(h->getlevel(), 1);
    shared_ptr<Character> ch(boss_monster);
    h->fight(ch, 1);
    if (h->getcurrentHealth() > 0)
    {
        cout << "Congratulations. You have defeated a boss!" << endl;
        cout << "Game is over" << endl;
    }
}


EventNode::EventNode(shared_ptr<Event>&& curr) {
    current = curr;
}