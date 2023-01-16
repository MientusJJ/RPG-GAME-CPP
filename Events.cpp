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


void Chest::openBox(shared_ptr<Hero>& h, shared_ptr<View> view) {
    const ItemType itemType = getRandomItemType(h);
    shared_ptr<Item> item = ItemFactory::createItem(h->getlevel(), itemType, h->getProf());

    int coins = static_cast<int>(round(makeRand(0, h->getlevel() * 100)));

    view->GoldFoundInChest(coins);
    h->setMoney(h->getMoney() + coins);

    view->ItemFoundInChest();
    showItemDetails(item, h->getProf(), view);

    view->ShowItemToChange();
    h->showOneItem(item->getType(), h->getProf(), view);

    view->DecisiontToReplaceItem();

    char decision;
    while (true) {
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'Y')
            h->ChangeEQ(item, view);

        if (decision == 'Y' || decision == 'N')
            break;
        else
            view->NotRecognizedCharacter();
    }
}


void DescriptionVisitor::visitEndPoint(EndPoint event, shared_ptr<View> view) {
    view->DescriptionEndPoint();
}
void DescriptionVisitor::visitEnterToMonsterRoom(EnterToMonsterRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToMonsterRoom();
}
void DescriptionVisitor::visitFight(Fight event, shared_ptr<View> view) {
    view->DescriptionFight();
}
void DescriptionVisitor::visitRunAway(RunAway event, shared_ptr<View> view) {
    view->DescriptionRunAway();
}
void DescriptionVisitor::visitCheckChest(CheckChest event, shared_ptr<View> view) {
    view->DescriptionCheckChest();
}
void DescriptionVisitor::visitEnterToTrapRoom(EnterToTrapRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToTrapRoom();
}
void DescriptionVisitor::visitActiveTheTrap(ActiveTheTrap event, shared_ptr<View> view) {
    view->DescriptionActiveTheTrap();
}
void DescriptionVisitor::visitEnterToPotionRoom(EnterToPotionRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToPotionRoom();
}
void DescriptionVisitor::visitDrinkPotion(DrinkPotion event, shared_ptr<View> view) {
    view->DescriptionDrinkPotion();
}
void DescriptionVisitor::visitEnterToTreasureRoom(EnterToTreasureRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToTreasureRoom();
}
void DescriptionVisitor::visitEnterToHealthRoom(EnterToHealthRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToHealthRoom();
}
void DescriptionVisitor::visitHealthYourself(HealthYourself event, shared_ptr<View> view) {
    view->DescriptionHealthYourself();
}
void DescriptionVisitor::visitEnterToTraderRoom(EnterToTraderRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToTraderRoom();
}
void DescriptionVisitor::visitSeeItems(SeeItems event, shared_ptr<View> view) {
    view->DescriptionSeeItems();
}
void DescriptionVisitor::visitEnterToEmptyRoom(EnterToEmptyRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToEmptyRoom();
}
void DescriptionVisitor::visitEnterToStartingRoom(EnterToStartingRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToStartingRoom();
}
void DescriptionVisitor::visitEnterToBossRoom(EnterToBossRoom event, shared_ptr<View> view) {
    view->DescriptionEnterToBossRoom();
}
void DescriptionVisitor::visitBossFight(BossFight event, shared_ptr<View> view) {
    view->DescriptionBossFight();
}


void Event::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {}

Event::Event() {}


void EndPoint::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEndPoint(*this, view);
}
void EndPoint::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    char decision;
    while (true) {
        view->CheckStatisticsOrEquipment();
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'E') {
            h->showEQ(view);
        }
        else if(decision == 'S')
        {
            h->showStatistics(view);
        }
        else if (decision == 'N')
            break;
        else
            view->NotRecognizedCharacter();
    }
}


void EnterToMonsterRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToMonsterRoom(*this, view);
}
void EnterToMonsterRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToMonsterRoom();
    view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
}


void Fight::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitFight(*this, view);
}
void Fight::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    shared_ptr<monster> normal_monster = make_shared<monster>(h->getlevel(), 0);
    shared_ptr<Character> ch(normal_monster);
	h->fight(ch, 0, view);
    if (h->getcurrentHealth() > 0)
    {
        view->MonsterDefeated();
        view->RemainingHealth(h->getcurrentHealth());
        h->levelup();
        view->LevelUp(h->getlevel());
        view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
    }
}


void RunAway::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitRunAway(*this, view);
}
void RunAway::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    int chance = static_cast<int>(round(makeRand(0, 10)));

    if (chance < 3) {
        view->EscapeWithBeingHit();
        h->getDamage(static_cast<int>(h->getcurrentHealth() * 0.2));
        view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
    }
    else
        view->EscapeWithoutBeingHit();
}


void CheckChest::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitCheckChest(*this, view);
}
void CheckChest::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    shared_ptr<Chest> chest = make_unique<Chest>();

    char decision;
    while (true) {
        view->ChestFound();
        cin >> decision;
        decision = makeBig(decision);
        if (decision == 'Y') {
            chest->openBox(h, view);
            break;
        }
        else if (decision == 'N')
            break;
        else
            view->NotRecognizedCharacter();
    }
}


void EnterToTrapRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToTrapRoom(*this, view);
}
void EnterToTrapRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->DescriptionEnterToTrapRoom();
}


void ActiveTheTrap::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitActiveTheTrap(*this, view);
}
void ActiveTheTrap::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->HurtedByTrap();
    h->getDamage(static_cast<int>(h->getmaxHealth() * 0.2));
    view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
}


void EnterToPotionRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToPotionRoom(*this, view);
}
void EnterToPotionRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToPotionRoom();
}


void DrinkPotion::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitDrinkPotion(*this, view);
}
void DrinkPotion::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    int drawn_num = static_cast<int>(round(makeRand(0, 1)));

    if (drawn_num == 0) {
        h->setcurrentHealth(h->getmaxHealth());
        view->HealthRestoredByPotion();
        view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
    }
    else {
        int poison = h->getmaxHealth() * 0.3;
        h->getDamage(poison);
        view->HealthLostByPoisonedPotion(poison);
        view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
    }
}


void EnterToTreasureRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToTreasureRoom(*this, view);
}
void EnterToTreasureRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToTreasureRoom();
}


void EnterToHealthRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToHealthRoom(*this, view);
}
void EnterToHealthRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToHealthRoom();
}


void HealthYourself::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitHealthYourself(*this, view);
}
void HealthYourself::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->HealthRestoredByMagicFountain();
    h->setcurrentHealth(h->getmaxHealth());
    view->ShowCurrentHealth(h->getcurrentHealth(), h->getmaxHealth());
}


void EnterToTraderRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToTraderRoom(*this, view);
}
void EnterToTraderRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToTraderRoom();
}


void SeeItems::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitSeeItems(*this, view);
}
void SeeItems::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    shared_ptr<Item> item1 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
    shared_ptr<Item> item2 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());
    shared_ptr<Item> item3 = ItemFactory::createItem(h->getlevel(), getRandomItemType(h), h->getProf());

    h->showEQ(view);

    view->ShowMerchantItemWithPrice(1, item1->getValue());
    showItemDetails(item1, h->getProf(), view);

    view->ShowMerchantItemWithPrice(2, item2->getValue());
    showItemDetails(item2, h->getProf(), view);

    view->ShowMerchantItemWithPrice(3, item3->getValue());
    showItemDetails(item3, h->getProf(), view);

    view->ShowGoldBalance(h->getMoney());

    char wantToBuy;
    view->DecisionToBuySomething();
    cin >> wantToBuy;
    wantToBuy = makeBig(wantToBuy);

    if (wantToBuy == 'Y')
        BuyItems(h, item1, item2, item3, view);
}
void SeeItems::BuyItems(shared_ptr<Hero> &h, shared_ptr<Item> &i1, shared_ptr<Item> &i2, shared_ptr<Item> &i3, shared_ptr<View> view) {
    bool wantToBuy = true;
    string l_playerDecision{};
    char player_decision;
    bool bought1 = false, bought2 = false, bought3 = false;

    while (wantToBuy)
    {
        view->SelectNumberOfItemToBuy();
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
                showItemDetails(i1, h->getProf(), view);
                bought1 = buyOneItem(h, i1, view);
            }
            else {
                view->SelectedItemHasAlreadyBeenBought();
            }
        }
        else if (num == 2) {
            if (!bought2) {
                showItemDetails(i2, h->getProf(), view);
                bought2 = buyOneItem(h, i2, view);
            }
            else {
                view->SelectedItemHasAlreadyBeenBought();
            }
        }
        else if (num == 3) {
            if (!bought3) {
                showItemDetails(i3, h->getProf(), view);
                bought3 = buyOneItem(h, i3, view);
            }
            else {
                view->SelectedItemHasAlreadyBeenBought();
            }
        }
        else {
            view->InvalidItemNumber();
        }

        if (!bought1 || !bought2 || !bought3) {
            view->ShowGoldBalance(h->getMoney());
            view->DecisionToBuyingAnotherItem();

            while (true) {
                cin >> player_decision;
                player_decision = makeBig(player_decision);
                if (player_decision == 'N')
                    wantToBuy = false;

                if (player_decision == 'Y' || player_decision == 'N')
                    break;
                else
                    view->NotRecognizedCharacter();
            }
        }
        else {
            view->AllItemsHaveAlreadyBeenBought();
            wantToBuy = false;
        }
    }
}
bool SeeItems::buyOneItem(shared_ptr<Hero> &h, shared_ptr<Item> &item, shared_ptr<View> view) {
    shared_ptr<Item> _buyingItem = item;
    bool _flag = false;

    shared_ptr<Strategy> _buyingStrategy = make_unique<StandardStrategy>(h);
    _buyingStrategy->setStartingPrice(_buyingItem->getValue());

    while (!_flag)
    {
        char player_decision;

    	view->DecisionToNegotiateItemPrice();
        while (true) {
            cin >> player_decision;
            player_decision = makeBig(player_decision);
            if (player_decision == 'Y' || player_decision == 'N')
                break;
            else
                view->NotRecognizedCharacter();
        }
        if(player_decision=='N')
        {
            break;
        }
        view->PriceOfferForItem();
        int price;
        cin >> price;
        _flag = _buyingStrategy->buyingProcess(price, view);
    }
    if(_flag)
    {
        h->ChangeEQ(_buyingItem, view);
    }
    return _flag;
	
}


void EnterToEmptyRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToEmptyRoom(*this, view);
}
void EnterToEmptyRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToEmptyRoom();
}


void EnterToStartingRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToStartingRoom(*this, view);
}
void EnterToStartingRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToStartingRoom();
}


void EnterToBossRoom::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitEnterToBossRoom(*this, view);
}
void EnterToBossRoom::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    view->EnteredToBossRoom();
}


void BossFight::DisplayDescription(DescriptionVisitor visitor, shared_ptr<View> view) {
    visitor.visitBossFight(*this, view);
}
void BossFight::Action(shared_ptr<Hero> &h, shared_ptr<View> view) {
    shared_ptr<monster> boss_monster = make_shared<monster>(h->getlevel(), 1);
    shared_ptr<Character> ch(boss_monster);
    h->fight(ch, 1, view);
    if (h->getcurrentHealth() > 0)
        view->BossDefeated();
}


EventNode::EventNode(shared_ptr<Event>&& curr) {
    current = curr;
}