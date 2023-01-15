using namespace std;
#include "Views.h"
#include <iostream>
#include <thread>

TXTView::TXTView() {}

void TXTView::OneOptionToMoveOn() {
    cout << "There is only one way out of this room..." << endl;
    cout << "Type L or R to go next" << endl;
}

void TXTView::TwoOpitonsToMoveOn() {
    cout << "You see two passages - which way do you want to go?" << endl;
    cout << "[L] left" << endl;
    cout << "[R] right" << endl;
}

void TXTView::OptionsForGoNext(int i) {
    cout << "Option [" << i << "]: ";
};

void TXTView::NotRecognizedCharacter() {
    cout << "Character not recognized, please retype" << endl;
};

void TXTView::DescriptionEndPoint () {
    cout << "Get out of the room" << endl;
};

void TXTView::DescriptionEnterToMonsterRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionFight () {
    cout << "Fight with the monster" << endl;
};

void TXTView::DescriptionRunAway () {
    cout << "Run away" << endl;
};

void TXTView::DescriptionCheckChest () {
    cout << "Check the chest" << endl;
};

void TXTView::DescriptionEnterToTrapRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionActiveTheTrap () {
    cout << "Active the trap" << endl;
};

void TXTView::DescriptionEnterToPotionRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionDrinkPotion () {
    cout << "Drink the potion" << endl;
};

void TXTView::DescriptionEnterToTreasureRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionEnterToHealthRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionHealthYourself () {
    cout << "Drink some water from the Fountain" << endl;
};

void TXTView::DescriptionEnterToTraderRoom () {

};

void TXTView::DescriptionSeeItems () {
    cout << "See items" << endl;
};

void TXTView::DescriptionEnterToEmptyRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionEnterToStartingRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionEnterToBossRoom () {
    cout << "" << endl;
};

void TXTView::DescriptionBossFight () {
    cout << "Final fight with BOSS" << endl;
};

void TXTView::GoldFoundInChest(int i) {
    cout << "You found " << i << " gold in the chest" << endl;
};

void TXTView::ItemFoundInChest() {
    cout << "There is also an item in chest: " << endl;
};

void TXTView::ShowItemToChange() {
    cout << "Your current item: " << endl;
};

void TXTView::DecisiontToReplaceItem() {
    cout << "Do you want to replace your item with a new found one? (Y/N)" << endl;
};

void TXTView::CheckStatisticsOrEquipment() {
    cout << "Do you want to check your Statistics (S), Equipment (E), or do nothing (N)?" << endl;
};

void TXTView::EnteredToMonsterRoom() {
    cout << "You have entered the room with the monster" << endl;
};

void TXTView::ShowCurrentHealth(int curr, int max) {
    cout << "Your current health is: " << curr << "/" << max << endl;
};

void TXTView::MonsterDefeated() {
    cout << "You have defeated a monster" << endl;
};

void TXTView::RemainingHealth(int curr) {
    cout << "Remaining health points: " << curr << endl << endl;
}

void TXTView::LevelUp(int lvl) {
    cout << "You have leveled up. Your current level is: " << lvl << endl;
};

void TXTView::EscapeWithBeingHit() {
    cout << "While escaping you got hit by a monster" << endl;
};

void TXTView::EscapeWithoutBeingHit() {
    cout << "You escaped the monster" << endl;
};

void TXTView::ChestFound() {
    cout << "You found mystery box. Do you want to open it? (Y/N)" << endl;
};

void TXTView::EnteredToTrapRoom() {
    cout << "You enter a chamber that appears to be empty..." << endl;
};

void TXTView::HurtedByTrap() {
    cout << "There was a trap in the room that has hurted you" << endl;
};

void TXTView::EnteredToPotionRoom() {
    cout << "You have entered to room and saw a mysterious potion on the table" << endl;
};

void TXTView::HealthRestoredByPotion() {
    cout << "Your health has been restored" << endl;
};

void TXTView::HealthLostByPoisonedPotion(int lost) {
    cout << "The potion was poisoned. You lost " << lost << " health" << endl;
};

void TXTView::EnteredToTreasureRoom() {
    cout << "You have entered to room and saw a chest by the wall" << endl;
};

void TXTView::EnteredToHealthRoom() {
    cout << "Upon entering the room, the Ancient Fountain of Life appeared before your eyes" << endl;
};

void TXTView::HealthRestoredByMagicFountain() {
    cout << "After drinking the magic water you regain all health points" << endl;
};

void TXTView::EnteredToTraderRoom() {
    cout << "You have enter the room and saw the stand of a traveling trader who wants to offer you his items" << endl;
};

void TXTView::ShowMerchantItemWithPrice(int num, int price) {
    if (num == 1)
        cout << "Merchant items:" << endl;

    cout << "item " << num << ":" << endl;
    cout << "price: " << price << endl << endl;
};

void TXTView::ShowGoldBalance(int bal) {
    cout << "Your balance: " << bal << endl;
};

void TXTView::DecisionToBuySomething() {
    cout << "Do you want to buy something? (Y/N)" << endl;
}

void TXTView::SelectNumberOfItemToBuy() {
    cout << "Enter the number of the item you want to buy:" << endl;
};

void TXTView::SelectedItemHasAlreadyBeenBought() {
    cout << "You have already bought this item" << endl;
};

void TXTView::InvalidItemNumber() {
    cout << "Invalid item number, try again" << endl;
};

void TXTView::DecisionToBuyingAnotherItem() {
    cout << "Do you want to buy anything else? (Y/N)" << endl;
};

void TXTView::AllItemsHaveAlreadyBeenBought() {
    cout << "You already bought all items from the merchant..." << endl;
};

void TXTView::DecisionToNegotiateItemPrice() {
    cout << "Do you want to negotiate price of this item? (Y/N)" << endl;
};

void TXTView::PriceOfferForItem() {
    cout << "Enter the price at which you would like to buy item: " << endl;
};

void TXTView::EnteredToEmptyRoom() {
    cout << "The room is completely empty, you have nothing to do here, so keep walking" << endl;
};

void TXTView::EnteredToStartingRoom() {
    cout << "Your adventure begins here" << endl;
};

void TXTView::EnteredToBossRoom() {
    chrono::milliseconds timespan(1000);
    this_thread::sleep_for(timespan);
    cout << "You have entered the boss's chamber" << endl;
    this_thread::sleep_for(timespan);
    cout << "The last and hardest fight is ahead of you" << endl;
    this_thread::sleep_for(timespan);
};

void TXTView::BossDefeated() {
    cout << "Congratulations. You have defeated a boss!" << endl;
    cout << "Game is over" << endl;
};

void TXTView::HeroDefeatedByBoss() {
    cout << "That was so close..." << endl;
};

void TXTView::InvalidClassValue() {
    cout << "Wrong class value" << endl;
};

void TXTView::NotEnoughtGoldToBuyItem() {
    cout << "You don't have that amount of money" << endl;
};

void TXTView::MuchTooLowOfferForItem() {
    cout << "I won't sell this item for nothing!!!!" << endl;
};

void TXTView::FairPriceOfferForItem() {
    cout << "This price is fair. I can sell you this item" << endl;
};

void TXTView::AlmostFairPriceOfferForItem(int offer) {
    cout << "This price is too low, but I can propose: " << offer << endl;
};

void TXTView::ShowFinalPrice(int price) {
    cout << "Current price: " << price << endl;
};

void TXTView::ShowCourseOfRound(string ch1, string ch2, int damage) {
    cout << ch1 << " dealt " << damage << " damage to " << ch2 << endl;
};

void TXTView::ShowCurrentHealthAfterRound(string ch, int currH) {
    cout << "Current health of " << ch << " is " << currH << endl;
};

void TXTView::DodgedHit(string ch1, string ch2) {
    cout << ch1 << " dodged the hit from " << ch2 << endl;
};

void TXTView::BlockedHit(string ch1, string ch2) {
    cout << ch1 << " blocked the hit from " << ch2 << endl;
};

void TXTView::ShowPossibleClassesToChoose(string name) {
    cout << "Choose class of " << name << " \nWrite 1 if you want warrior \nWrite 2 if you want scout \nWrite 3 if you want mage \n";
};

void TXTView::IncorrectNumber(int min,int max) {
    cout << "Bad Number. Choose number between " << min << " and " << max << endl;
};

void TXTView::ShowChoosenClass(int ch) {
    cout << "Your class for the whole game is: ";
    if (ch == 1)
        cout << "Warrior\n";
    else if (ch == 2)
        cout << "Scout\n";
    else if(ch==3)
        cout << "Mage\n";
};

void TXTView::WriteHeroName() {
    cout << "Write name of your hero:" << endl;
};

void TXTView::ShowEqiupment(string prof,string weaponName,int minDamage,int maxDamage,string mainStateName,int weaponMainStat,int weaponValue
    ,string talismanName,string talismanMainStatName,int talismanMainStat,int talismanCrit,int talismanValue
    ,string armorName,int armorDef,int armorHealth,int armorValue
	,string headGearName,int headGearDef,int headGearVal,int headgearValue,string headGearMainstat
    ,string shieldName,int shieldDef,int shieldBlockChance,int shieldValue) {
    cout << endl << "Equipment of your hero:" << endl;
    this->ShowOneItem("weapon", prof, weaponValue, weaponName, minDamage, maxDamage, weaponMainStat, mainStateName);
    this->ShowOneItem("talisman", prof, talismanValue, talismanName, talismanMainStat, talismanCrit,0,talismanMainStatName);
    if(prof=="warrior")
    {
        this->ShowOneItem("shield", prof, shieldValue, shieldName, shieldDef, shieldBlockChance);
    }
    this->ShowOneItem("armor", prof, armorValue, armorName, armorDef, armorHealth);
    this->ShowOneItem("headgear", prof, headgearValue, headGearName, headGearDef, headGearVal, 0, headGearMainstat);
};

void TXTView::ShowStatistics(string name,string prof,string mainStatName,string skill,int level,int mainStat,int maxHealth,int currHealth,int minAttack,int maxAttack,double crit,int def,int money,double block) {
    cout << endl << "Statistics of your hero:" << endl;
    cout << "Name: " << name << endl;
    cout << "Class: " << prof << endl;
    cout << "Main Stat name: " << mainStatName << endl;
    cout << "Skill: " << skill << endl;
    cout << "Level: " << level << endl;
    cout << "Main Stat: " << mainStat;
    cout << "Max health: " << maxHealth << endl;
    cout << "Current health: " << currHealth << endl;
    cout << "Minimal damage: " << maxHealth << endl;
    cout << "Maximal damage: " << maxAttack << endl;
    cout << "Critical chance: " << crit << "%" << endl;
    cout << "Defense: " << def << endl;
    if (prof == "warrior")
    {
        cout << "Block Chance: " << block << "%" << endl;
    }
    cout << "Amount of money: " << money << endl;
    return;
};

void TXTView::ShowOneItem(string type,string prof,int value,string name,int val1,int val2,int val3,string mainStatName) {
    if (type == "weapon")
    {
        cout << "Weapon:\n\t name: " << name << "\n\t minimal Damage: " << val1
    	<< "\n\t maximal Damage: " << val2
    	<< "\n\t " << mainStatName << ": " << val3
    	<< "\n\t value: " << value << endl;
    }
    else if (type == "talisman")
    {
        cout << "Talisman:\n\t name: " << name << "\n\t " << mainStatName
    	<< ": " << val1 << "\n\t Critical Chance: " << val2
    	<< "\n\t value: " << value << endl;
    }
    else if (type == "shield")
    {
        cout << "Shield:\n\t name: " << name << "\n\t Defense: "
    	<< val1 << "\n\t Block Chance: " << val2
    	<< "\n\t value: " << value << endl;
    }
    else if (type == "armor")
    {
        cout << "Armor:\n\t name: " << name << "\n\t Defense: "
    	<< val1 << "\n\t Health: " << val2
    	<< "\n\t value: " << value << endl;
    }
    else if (type == "headgear")
    {
        cout << "Headgear:\n\t name: " << name
            << "\n\t Defense: " << val1;
        if (prof == "mage")
        {
            cout << "\n\t " << mainStatName << ": " << val2;
        }
        else
        {
            cout << ":\n\t Health: " << val2;
        }
        cout << "\n\t value: " << value << endl;
    }
};

void TXTView::CompletedEqChanging() {
    cout << "Changing equipment completed" << endl;
};