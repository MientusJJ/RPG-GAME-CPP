#include <iostream>
#include "Chambers.h"
using namespace std;
int chambersWithoutMonsters;
int chambersWithoutTrader;

ItemType getRandomItemType( shared_ptr<Hero>&h) {
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
Chest::Chest(shared_ptr<Hero>& h) {
	const ItemType itemType = getRandomItemType(h);
	item = ItemFactory::createItem(h->getlevel(), itemType, h->getProf());
}


void ActionVisitor::visitMonsterRoom(MonsterRoom room) {
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<Chest> chest = room.getChest();
    shared_ptr<monster> normal_monster = room.getMonster();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToMonsterRoom>(h));
    shared_ptr<EventNode> fight = make_shared<EventNode>(make_shared<Fight>(h,normal_monster));
    shared_ptr<EventNode> runAway = make_shared<EventNode>(make_shared<RunAway>(h));
    shared_ptr<EventNode> openBox = make_shared<EventNode>(make_unique<CheckChest>(h, chest));
    start->AllNexts.reserve(2);
    fight->AllNexts.reserve(2);
    openBox->AllNexts.reserve(1);
    runAway->AllNexts.reserve(1);
    start->AllNexts.emplace_back(fight);
    start->AllNexts.emplace_back(runAway);
    fight->AllNexts.emplace_back(openBox);
    fight->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    openBox->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    runAway->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitTrapRoom(TrapRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTrapRoom>(h));
    start->AllNexts.reserve(1);
    shared_ptr<EventNode> trap = make_shared<EventNode>(make_shared<ActiveTheTrap>(h));
    trap->AllNexts.reserve(1);
    start->AllNexts.emplace_back(trap);
    trap->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitPotionRoom(PotionRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToPotionRoom>(h));
    start->AllNexts.reserve(1);
    shared_ptr<EventNode> potion = make_shared<EventNode>(make_shared<DrinkPotion>(h));
    potion->AllNexts.reserve(1);
    start->AllNexts.emplace_back(potion);
    potion->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitTreasureRoom(TreasureRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<Chest> chest = room.getChest();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTreasureRoom>(h));
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> chestEvent = make_shared<EventNode>(make_shared<CheckChest>(h,chest));
    chestEvent->AllNexts.reserve(1);
    start->AllNexts.emplace_back(chestEvent);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    chestEvent->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitHealthRoom(HealthRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToHealthRoom>(h));
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> health = make_shared<EventNode>(make_shared<HealthYourself>(h));
    health->AllNexts.reserve(1);
    start->AllNexts.emplace_back(health);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    health->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitTraderRoom(TraderRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<Item> item1 = room.getItem1();
    shared_ptr<Item> item2 = room.getItem2();
    shared_ptr<Item> item3 = room.getItem3();
    shared_ptr<Strategy> _buyingstrategy = room.getStrategy();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTraderRoom>(h));
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> see = make_shared<EventNode>(make_shared<SeeItems>(h,item1,item2,item3));
    see->AllNexts.reserve(2);
    shared_ptr<EventNode> buy = make_shared<EventNode>(make_shared<BuyItems>(h, item1, item2, item3,_buyingstrategy));
    buy->AllNexts.reserve(1);
    start->AllNexts.emplace_back(see);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    see->AllNexts.emplace_back(buy);
    see->AllNexts.push_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    buy->AllNexts.push_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitEmptyRoom(EmptyRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToEmptyRoom>(h));
    start->AllNexts.reserve(1);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitStartingRoom(StartingRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start= make_shared<EventNode>(make_shared<EnterToStartingRoom>(h));
    start->AllNexts.reserve(1);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));

    room.eventTransitionFunction(start, h);
}

void ActionVisitor::visitBossRoom(BossChamber room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<monster> boss_monster = room.getMonster();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToBossRoom>(h));
    shared_ptr<EventNode> bossfight = make_shared<EventNode>(make_shared<Fight>(h, boss_monster));
    bossfight->AllNexts.reserve(1);
    start->AllNexts.reserve(2);
    start->AllNexts.emplace_back(bossfight);
    bossfight->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>(h)));
    room.eventTransitionFunction(start, h);
    if (h->getcurrentHealth() > 0)
        cout << "Congratulations! You finished the game" << endl;
    else
        cout << "It was very close..." << endl;
}



Chamber::Chamber(shared_ptr<Hero>&h)
{
	chamber_ID = static_cast<int>(makeRand(1,1000));
	hero = h->getInstance();
}

string Chamber::getName() {
	return name;
}

template<typename Derived, typename T>
inline bool instanceof(const shared_ptr<T> ptr) {
	shared_ptr<Derived> d = dynamic_pointer_cast<Derived>(ptr);
	return d != nullptr;
}

// do Controller
void Chamber::eventTransitionFunction(shared_ptr<EventNode>& start, shared_ptr<Hero>& h) {
	shared_ptr<EventNode> curr = start;
	while (true)
	{
		curr->current->Action();

		if (h->getcurrentHealth() == 0)
			break;

		int numOfNexts = curr->AllNexts.size();

       
		if (numOfNexts == 1)
			curr = curr->AllNexts[0];
		else {
            int i = 1;
            vector <shared_ptr<EventNode>> options = curr->AllNexts;

            for (vector <shared_ptr<EventNode>>::iterator it = options.begin(); it != options.end(); it++) {
                cout << "Option [" << i << "]: ";
                (*it)->Description();
                cout << endl;
                i++;
            }

			int choice;
			cin >> choice;
			while (choice < 1 || choice > numOfNexts) {
				cout << "Character not recognized, please retype" << endl;
				cin >> choice;
				
			}

			curr = curr->AllNexts[choice - 1];
		}

		if (instanceof<EndPoint>(curr->current))
		{
			curr->current->Action();
			break;
		}
			
	}
}

BossChamber::BossChamber(shared_ptr<Hero>&h) : Chamber(h) {
	int lvl = h->getlevel() * 2;
	boss_monster = make_shared<monster>(lvl, "Great BOSS");
}

shared_ptr<monster> BossChamber::getMonster() {
    return boss_monster;
}

void BossChamber::action(ActionVisitor visitor) {
    visitor.visitBossRoom(*this);
}


PassageChamber::PassageChamber(shared_ptr<Hero>&h) : Chamber(h) {}

NormalChamber::NormalChamber(shared_ptr<Hero>&h) : PassageChamber(h) {}

SafeChamber::SafeChamber(shared_ptr<Hero>&h) : PassageChamber(h) {}


MonsterRoom::MonsterRoom(shared_ptr<Hero>&h) : NormalChamber(h) {
    chambersWithoutMonsters = 0;
    chambersWithoutTrader++;
	chest = make_unique<Chest>(h);
	normal_monster = make_shared<monster>(h->getlevel(), 0);
}

shared_ptr<Chest> MonsterRoom::getChest() {
    return chest;
}

shared_ptr<monster> MonsterRoom::getMonster() {
    return normal_monster;
}

void MonsterRoom::action(ActionVisitor visitor) {
    visitor.visitMonsterRoom(*this);
}


TrapRoom::TrapRoom(shared_ptr<Hero>&h) : NormalChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

void TrapRoom::action(ActionVisitor visitor) {
    visitor.visitTrapRoom(*this);
}


PotionRoom::PotionRoom(shared_ptr<Hero>&h) : NormalChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

void PotionRoom::action(ActionVisitor visitor) {
    visitor.visitPotionRoom(*this);
}


TreasureRoom::TreasureRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
	chest = make_unique<Chest>(h);
}

shared_ptr<Chest> TreasureRoom::getChest() {
    return chest;
}

void TreasureRoom::action(ActionVisitor visitor) {
    visitor.visitTreasureRoom(*this);
}


HealthRoom::HealthRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

void HealthRoom::action(ActionVisitor visitor) {
    visitor.visitHealthRoom(*this);
}


TraderRoom::TraderRoom(shared_ptr<Hero>&h) : SafeChamber(h) {chambersWithoutMonsters++;
	chambersWithoutTrader = 0;
	item1 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item2 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	item3 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
	_buyingstrategy = make_unique<StandardStrategy>(h);
};

shared_ptr<Item> TraderRoom::getItem1() {
    return item1;
}
shared_ptr<Item> TraderRoom::getItem2() {
    return item2;
}
shared_ptr<Item> TraderRoom::getItem3() {
    return item3;
}
shared_ptr<Strategy> TraderRoom::getStrategy() {
    return _buyingstrategy;
}

void TraderRoom::action(ActionVisitor visitor) {
    visitor.visitTraderRoom(*this);
}


EmptyRoom::EmptyRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters++;
    chambersWithoutTrader++;
}

void EmptyRoom::action(ActionVisitor visitor) {
    visitor.visitEmptyRoom(*this);
}


StartingRoom::StartingRoom(shared_ptr<Hero>&h) : SafeChamber(h) {
    chambersWithoutMonsters = 0;
    chambersWithoutTrader = 0;
}

void StartingRoom::action(ActionVisitor visitor) {
    visitor.visitStartingRoom(*this);
}



ChamberNode::ChamberNode(shared_ptr<Chamber> curr) {
	current = curr;
	option1 = nullptr;
	option2 = nullptr;
}