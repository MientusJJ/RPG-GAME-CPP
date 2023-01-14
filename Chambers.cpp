#include <iostream>
#include "Chambers.h"
using namespace std;


template<typename Derived, typename T>
inline bool instanceof(const shared_ptr<T> ptr) {
    shared_ptr<Derived> d = dynamic_pointer_cast<Derived>(ptr);
    return d != nullptr;
}
ActionVisitor::ActionVisitor(shared_ptr<Hero> h)
{
    this->obs = make_shared<Observer>(h);
    this->obs->addToObserver();
}
void ActionVisitor::eventTransitionFunction(shared_ptr<EventNode> &start, shared_ptr<Hero> &h) {
    shared_ptr<EventNode> curr = start;
    while (true)
    {
        curr->current->Action(h);

        if (this->obs->check())
            break;

        int numOfNexts = curr->AllNexts.size();

        if (numOfNexts == 1)
            curr = curr->AllNexts[0];
        else {
            int i = 1;
            vector <shared_ptr<EventNode>> options = curr->AllNexts;
            shared_ptr<DescriptionVisitor> visitor(new DescriptionVisitor());

            for (vector <shared_ptr<EventNode>>::iterator it = options.begin(); it != options.end(); it++) {
                cout << "Option [" << i << "]: ";
                (*it)->current->DisplayDescription(*visitor);
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
            curr->current->Action(h);
            break;
        }

    }
}

void ActionVisitor::visitMonsterRoom(MonsterRoom room) {
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitTrapRoom(TrapRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitPotionRoom(PotionRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitTreasureRoom(TreasureRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitHealthRoom(HealthRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitTraderRoom(TraderRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitEmptyRoom(EmptyRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitStartingRoom(StartingRoom room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);
}

void ActionVisitor::visitBossRoom(BossChamber room)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h);

    if (h->getcurrentHealth() > 0)
        cout << "Congratulations! You finished the game" << endl;
    else
        cout << "It was very close..." << endl;
}



void BossChamber::action(ActionVisitor visitor) {
    visitor.visitBossRoom(*this);
}
shared_ptr<EventNode> BossChamber::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToBossRoom>());
    shared_ptr<EventNode> bossFight = make_shared<EventNode>(make_shared<BossFight>());
    bossFight->AllNexts.reserve(1);
    start->AllNexts.reserve(1);
    start->AllNexts.emplace_back(bossFight);
    bossFight->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void MonsterRoom::action(ActionVisitor visitor) {
    visitor.visitMonsterRoom(*this);
}
shared_ptr<EventNode> MonsterRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToMonsterRoom>());
    shared_ptr<EventNode> fight = make_shared<EventNode>(make_shared<Fight>());
    shared_ptr<EventNode> runAway = make_shared<EventNode>(make_shared<RunAway>());
    shared_ptr<EventNode> openBox = make_shared<EventNode>(make_unique<CheckChest>());
    start->AllNexts.reserve(2);
    fight->AllNexts.reserve(2);
    openBox->AllNexts.reserve(1);
    runAway->AllNexts.reserve(1);
    start->AllNexts.emplace_back(fight);
    start->AllNexts.emplace_back(runAway);
    fight->AllNexts.emplace_back(openBox);
    fight->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    openBox->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    runAway->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TrapRoom::action(ActionVisitor visitor) {
    visitor.visitTrapRoom(*this);
}
shared_ptr<EventNode> TrapRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTrapRoom>());
    start->AllNexts.reserve(1);
    shared_ptr<EventNode> trap = make_shared<EventNode>(make_shared<ActiveTheTrap>());
    trap->AllNexts.reserve(1);
    start->AllNexts.emplace_back(trap);
    trap->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void PotionRoom::action(ActionVisitor visitor) {
    visitor.visitPotionRoom(*this);
}
shared_ptr<EventNode> PotionRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToPotionRoom>());
    start->AllNexts.reserve(1);
    shared_ptr<EventNode> potion = make_shared<EventNode>(make_shared<DrinkPotion>());
    potion->AllNexts.reserve(1);
    start->AllNexts.emplace_back(potion);
    potion->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TreasureRoom::action(ActionVisitor visitor) {
    visitor.visitTreasureRoom(*this);
}
shared_ptr<EventNode> TreasureRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTreasureRoom>());
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> chestEvent = make_shared<EventNode>(make_shared<CheckChest>());
    chestEvent->AllNexts.reserve(1);
    start->AllNexts.emplace_back(chestEvent);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    chestEvent->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void HealthRoom::action(ActionVisitor visitor) {
    visitor.visitHealthRoom(*this);
}
shared_ptr<EventNode> HealthRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToHealthRoom>());
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> health = make_shared<EventNode>(make_shared<HealthYourself>());
    health->AllNexts.reserve(1);
    start->AllNexts.emplace_back(health);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    health->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TraderRoom::action(ActionVisitor visitor) {
    visitor.visitTraderRoom(*this);
}
shared_ptr<EventNode> TraderRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToTraderRoom>());
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> see = make_shared<EventNode>(make_shared<SeeItems>());
    see->AllNexts.reserve(1);

    start->AllNexts.emplace_back(see);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    see->AllNexts.push_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void EmptyRoom::action(ActionVisitor visitor) {
    visitor.visitEmptyRoom(*this);
}
shared_ptr<EventNode> EmptyRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToEmptyRoom>());
    start->AllNexts.reserve(1);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void StartingRoom::action(ActionVisitor visitor) {
    visitor.visitStartingRoom(*this);
}
shared_ptr<EventNode> StartingRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start= make_shared<EventNode>(make_shared<EnterToStartingRoom>());
    start->AllNexts.reserve(1);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}



ChamberNode::ChamberNode(shared_ptr<Chamber> curr) {
	current = curr;
	option1 = nullptr;
	option2 = nullptr;
}