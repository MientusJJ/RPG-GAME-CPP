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
void ActionVisitor::eventTransitionFunction(shared_ptr<EventNode> &start, shared_ptr<Hero> &h, shared_ptr<View> view) {
    shared_ptr<EventNode> curr = start;
    while (true)
    {
        curr->current->Action(h, view);

        if (this->obs->check(view))
            break;

        int numOfNexts = curr->AllNexts.size();

        if (numOfNexts == 1)
            curr = curr->AllNexts[0];
        else {
            int i = 1;
            vector <shared_ptr<EventNode>> options = curr->AllNexts;
            shared_ptr<DescriptionVisitor> visitor(new DescriptionVisitor());

            for (vector <shared_ptr<EventNode>>::iterator it = options.begin(); it != options.end(); it++) {
                view->OptionsForGoNext(i);
                (*it)->current->DisplayDescription(*visitor, view);
                i++;
            }

            int choice;
            cin >> choice;
            while (choice < 1 || choice > numOfNexts) {
                view->NotRecognizedCharacter();
                cin >> choice;

            }

            curr = curr->AllNexts[choice - 1];
        }

        if (instanceof<EndPoint>(curr->current))
        {
            curr->current->Action(h, view);
            break;
        }

    }
}

void ActionVisitor::visitMonsterRoom(MonsterRoom room, shared_ptr<View> view) {
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitTrapRoom(TrapRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitPotionRoom(PotionRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitTreasureRoom(TreasureRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitHealthRoom(HealthRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitTraderRoom(TraderRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitEmptyRoom(EmptyRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitStartingRoom(StartingRoom room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);
}

void ActionVisitor::visitBossRoom(BossChamber room, shared_ptr<View> view)
{
    shared_ptr<Hero> h = Hero::getInstance();
    shared_ptr<EventNode> start = room.prepareEventsGraph();

    eventTransitionFunction(start, h, view);

    if (h->getcurrentHealth() > 0)
        view->GameSuccesfullFinished();
    else
        view->GameAlmostFinished();
}



void BossChamber::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitBossRoom(*this, view);
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


void MonsterRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitMonsterRoom(*this, view);
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


void TrapRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitTrapRoom(*this, view);
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


void PotionRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitPotionRoom(*this, view);
}
shared_ptr<EventNode> PotionRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToPotionRoom>());
    start->AllNexts.reserve(2);
    shared_ptr<EventNode> potion = make_shared<EventNode>(make_shared<DrinkPotion>());
    potion->AllNexts.reserve(1);
    start->AllNexts.emplace_back(potion);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));
    potion->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void TreasureRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitTreasureRoom(*this, view);
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


void HealthRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitHealthRoom(*this, view);
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


void TraderRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitTraderRoom(*this, view);
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


void EmptyRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEmptyRoom(*this, view);
}
shared_ptr<EventNode> EmptyRoom::prepareEventsGraph() {
    shared_ptr<Hero> h = Hero::getInstance();

    shared_ptr<EventNode> start = make_shared<EventNode>(make_shared<EnterToEmptyRoom>());
    start->AllNexts.reserve(1);
    start->AllNexts.emplace_back(make_shared<EventNode>(make_shared<EndPoint>()));

    return start;
}


void StartingRoom::action(ActionVisitor visitor, shared_ptr<View> view) {
    visitor.visitStartingRoom(*this, view);
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