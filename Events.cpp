#include "Events.h"
#include <chrono>
#include <thread>

void Chest::openBox(shared_ptr<Hero>& h) {
    int coins = static_cast<int>(round(makeRand(0, h->getlevel() * 100)));
    //viewTxtOpenBox
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
void DescriptionVisitor::visitBuyItems(BuyItems event) {
    cout << "Buy some items" << endl;
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


void Event::Action() {}


EndPoint::EndPoint(shared_ptr<Hero>& hero) {
    h = hero;
}
void EndPoint::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEndPoint(*this);
}

void EndPoint::Action() {
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

EnterToMonsterRoom::EnterToMonsterRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToMonsterRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToMonsterRoom(*this);
}
void EnterToMonsterRoom::Action() {
    cout << "You have entered the room with the monster" << endl;
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}

Fight::Fight(shared_ptr<Hero>& hero, shared_ptr<monster> monster) {
    h = hero;
    _monster = monster;
}
void Fight::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitFight(*this);
}
void Fight::Action() {
    shared_ptr<Character> ch(_monster);
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

RunAway::RunAway(shared_ptr<Hero>& hero) {
    h = hero;
}
void RunAway::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitRunAway(*this);
}
void RunAway::Action() {
    int chance = static_cast<int>(round(makeRand(0, 10)));

    if (chance < 3) {
        cout << "While escaping you got hit by a monster" << endl;
        h->getDamage(static_cast<int>(h->getcurrentHealth() * 0.2));
        cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
    }
    else
        cout << "You escaped the monster" << endl;
}

CheckChest::CheckChest(shared_ptr<Hero>& hero, shared_ptr<Chest>& chest) {
    h = hero;
    _chest = move(chest);
}
void CheckChest::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitCheckChest(*this);
}
void CheckChest::Action() {
    char decision;
    while (true) {
        cout << "You found mystery box. Do you want to open it? (Y/N)" << endl;
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'Y') {
            _chest->openBox(h);
            break;
        }
        else if (decision == 'N')
            break;
        else
            cout << "Character not recognized, please retype" << endl;
    }
}

EnterToTrapRoom::EnterToTrapRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToTrapRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToTrapRoom(*this);
}
void EnterToTrapRoom::Action() {
    cout << "You enter a chamber that appears to be empty..." << endl;
}

ActiveTheTrap::ActiveTheTrap(shared_ptr<Hero>& hero) {
    h = hero;
}
void ActiveTheTrap::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitActiveTheTrap(*this);
    cout << "Active the trap" << endl;
}
void ActiveTheTrap::Action() {
    cout << "There was a trap in the room that has hurted you" << endl;
    h->getDamage(static_cast<int>(h->getmaxHealth() * 0.2));
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}

EnterToPotionRoom::EnterToPotionRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToPotionRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToPotionRoom(*this);
}
void EnterToPotionRoom::Action() {
    cout << "You have entered to room and saw a mysterious potion on the table" << endl;
}

DrinkPotion::DrinkPotion(shared_ptr<Hero>& hero) {
    h = hero;
}
void DrinkPotion::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitDrinkPotion(*this);
    cout << "Drink the potion" << endl;
}
void DrinkPotion::Action() {
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

EnterToTreasureRoom::EnterToTreasureRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToTreasureRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToTreasureRoom(*this);
}
void EnterToTreasureRoom::Action() {
    cout << "You have entered to room and saw a chest by the wall" << endl;
}

EnterToHealthRoom::EnterToHealthRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToHealthRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToHealthRoom(*this);
}
void EnterToHealthRoom::Action() {
    cout << "Upon entering the room, the Ancient Fountain of Life appeared before your eyes" << endl;
}

HealthYourself::HealthYourself(shared_ptr<Hero>& hero) {
    h = hero;
}
void HealthYourself::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitHealthYourself(*this);
}
void HealthYourself::Action() {
    cout << "After drinking the magic water you regain all health points" << endl;
    h->setcurrentHealth(h->getmaxHealth());
    cout << "Your current health is: " << h->getcurrentHealth() << "/" << h->getmaxHealth() << endl;
}

EnterToTraderRoom::EnterToTraderRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToTraderRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToTraderRoom(*this);
}
void EnterToTraderRoom::Action() {
    cout << "You have enter the room and saw the stand of a traveling trader who wants to offer you his items" << endl;
}

SeeItems::SeeItems(shared_ptr<Hero>& hero, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3) {
    h = hero;
    _item1 = i1;
    _item2 = i2;
    _item3 = i3;
}
void SeeItems::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitSeeItems(*this);
}
void SeeItems::Action() {
    h->showEQ();
    cout << endl;
    cout << "Merchant items:" << endl;
    cout << "item 1:" << endl;
    showItemDetails(_item1, h->getProf());
    cout << "price: " << _item1->getValue() << endl << endl;

    cout << "item 2:" << endl;
    showItemDetails(_item2, h->getProf());
    cout << "price: " << _item2->getValue() << endl << endl;

    cout << "item 3:" << endl;
    showItemDetails(_item3, h->getProf());
    cout << "price: " << _item3->getValue() << endl << endl;
    cout << "Your balance: " << h->getMoney() << endl;
}

BuyItems::BuyItems(shared_ptr<Hero>& hero, shared_ptr<Item>& i1, shared_ptr<Item>& i2, shared_ptr<Item>& i3, shared_ptr<Strategy>& p_strategy) {
    h = hero;
    _item1 = i1;
    _item2 = i2;
    _item3 = i3;
    _buyingStrategy = p_strategy;
}
void BuyItems::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitBuyItems(*this);
}
void BuyItems::Action() {
    bool wantToBuy = true;
    int num;
    char player_decision;
    bool bought1 = false, bought2 = false, bought3 = false;

    while (wantToBuy)
    {
        cout << "Enter the number of the item you want to buy:" << endl;
        cin >> num;
        num = makeBig(num);
        if (num == 1) {
            if (!bought1) {
                showItemDetails(_item1, h->getProf());
                bought1 = buyOneItem(1);
            }
            else {
                cout << "You have already bought this item" << endl;
            }
        }
        else if (num == 2) {
            if (!bought2) {
                showItemDetails(_item2, h->getProf());
                bought2=buyOneItem(2);
            }
            else {
                cout << "You have already bought this item" << endl;
            }
        }
        else if (num == 3) {
            if (!bought3) {
                showItemDetails(_item3, h->getProf());
                bought3=buyOneItem(3);
               
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
bool BuyItems::buyOneItem(int num)
{
    shared_ptr<Item> _buyingItem;
    bool _flag = false;
    if(num==1)
    {
        _buyingItem = _item1;
    }
    else if(num==2)
    {
        _buyingItem = _item2;
    }
    else if (num==3)
    {
        _buyingItem = _item3;
    }
    _buyingStrategy->setStartingPrice(_buyingItem->getValue());

    while (!_flag)
    {
        char player_decision;

    	cout << "Do you still want to negotiate price of this item: " << _buyingItem->getName() << "? (Y/N)" << endl;
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
        cout << "Enter the price at which you want to buy item: " << endl;
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
EnterToEmptyRoom::EnterToEmptyRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToEmptyRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToEmptyRoom(*this);
}
void EnterToEmptyRoom::Action() {
    cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
}

EnterToStartingRoom::EnterToStartingRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToStartingRoom::DisplayDescription(DescriptionVisitor visitor) {
    cout << "" << endl;
}
void EnterToStartingRoom::Action() {
    cout << "Your adventure begins here" << endl;
}

EnterToBossRoom::EnterToBossRoom(shared_ptr<Hero>& hero) {
    h = hero;
}
void EnterToBossRoom::DisplayDescription(DescriptionVisitor visitor) {
    visitor.visitEnterToBossRoom(*this);
}
void EnterToBossRoom::Action() {
    chrono::milliseconds timespan(1000);
    this_thread::sleep_for(timespan);
    cout << "You have entered the boss's chamber" << endl;
    this_thread::sleep_for(timespan);
    cout << "The last and hardest fight is ahead of you" << endl;
    this_thread::sleep_for(timespan);
}


EventNode::EventNode(shared_ptr<Event>&& curr) {
    current = curr;
}