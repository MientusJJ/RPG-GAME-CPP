#pragma once
#ifndef VIEWS_H
#define VIEWS_H
#include <string>
class View {
public:
    //game
    virtual void OneOptionToMoveOn() = 0;
    virtual void TwoOpitonsToMoveOn() = 0;


    //chambers
    virtual void OptionsForGoNext(int i) = 0;
    virtual void NotRecognizedCharacter() = 0;
    virtual void GameSuccesfullFinished() = 0;
    virtual void GameAlmostFinished() = 0;


    //events
    virtual void DescriptionEndPoint() = 0;
    virtual void DescriptionEnterToMonsterRoom() = 0;
    virtual void DescriptionFight() = 0;
    virtual void DescriptionRunAway() = 0;
    virtual void DescriptionCheckChest() = 0;
    virtual void DescriptionEnterToTrapRoom() = 0;
    virtual void DescriptionActiveTheTrap() = 0;
    virtual void DescriptionEnterToPotionRoom() = 0;
    virtual void DescriptionDrinkPotion() = 0;
    virtual void DescriptionEnterToTreasureRoom() = 0;
    virtual void DescriptionEnterToHealthRoom() = 0;
    virtual void DescriptionHealthYourself() = 0;
    virtual void DescriptionEnterToTraderRoom() = 0;
    virtual void DescriptionSeeItems() = 0;
    virtual void DescriptionEnterToEmptyRoom() = 0;
    virtual void DescriptionEnterToStartingRoom() = 0;
    virtual void DescriptionEnterToBossRoom() = 0;
    virtual void DescriptionBossFight() = 0;



    virtual void GoldFoundInChest(int i) = 0;
    virtual void ItemFoundInChest() = 0;
    virtual void ShowItemToChange() = 0;
    virtual void DecisiontToReplaceItem() = 0;

    virtual void CheckStatisticsOrEquipment() = 0;

    virtual void EnteredToMonsterRoom() = 0;
    virtual void ShowCurrentHealth(int curr, int max) = 0;
    virtual void MonsterDefeated() = 0;
    virtual void RemainingHealth(int curr) = 0;
    virtual void LevelUp(int lvl) = 0;
    virtual void EscapeWithBeingHit() = 0;
    virtual void EscapeWithoutBeingHit() = 0;
    virtual void ChestFound() = 0;

    virtual void EnteredToTrapRoom() = 0;
    virtual void HurtedByTrap() = 0;

    virtual void EnteredToPotionRoom() = 0;
    virtual void HealthRestoredByPotion() = 0;
    virtual void HealthLostByPoisonedPotion(int lost) = 0;

    virtual void EnteredToTreasureRoom() = 0;

    virtual void EnteredToHealthRoom() = 0;
    virtual void HealthRestoredByMagicFountain() = 0;

    virtual void EnteredToTraderRoom() = 0;
    virtual void ShowMerchantItemWithPrice(int num, int price) = 0;
    virtual void ShowGoldBalance(int bal) = 0;
    virtual void DecisionToBuySomething() = 0;
    virtual void SelectNumberOfItemToBuy() = 0;
    virtual void SelectedItemHasAlreadyBeenBought() = 0;
    virtual void InvalidItemNumber() = 0;
    virtual void DecisionToBuyingAnotherItem() = 0;
    virtual void AllItemsHaveAlreadyBeenBought() = 0;
    virtual void DecisionToNegotiateItemPrice() = 0;
    virtual void PriceOfferForItem() = 0;

    virtual void EnteredToEmptyRoom() = 0;

    virtual void EnteredToStartingRoom() = 0;

    virtual void EnteredToBossRoom() = 0;
    virtual void BossDefeated() = 0;
    virtual void HeroDefeatedByBoss() = 0;


    //items
    virtual void InvalidClassValue() = 0;


    //strategy
    virtual void NotEnoughtGoldToBuyItem() = 0;
    virtual void MuchTooLowOfferForItem() = 0;
    virtual void FairPriceOfferForItem() = 0;
    virtual void AlmostFairPriceOfferForItem(int offer) = 0;
    virtual void ShowFinalPrice(int price) = 0;


    //character (character1, character2);
    virtual void ShowCourseOfRound(string ch1, string ch2, int damage) = 0;
    virtual void ShowCurrentHealthAfterRound(string ch, int currH) = 0;
    virtual void DodgedHit(string ch1, string ch2) = 0;
    virtual void BlockedHit(string ch1, string ch2) = 0;

    virtual void ShowPossibleClassesToChoose(string name) = 0;
    virtual void IncorrectNumber(int min, int max) = 0;
    virtual void ShowChoosenClass(int ch) = 0;

    virtual void WriteHeroName() = 0;

    virtual void ShowEqiupment(string prof, string weaponName, int minDamage, int maxDamage, string mainStateName, int weaponMainStat, int weaponValue
        , string talismanName, string talismanMainStatName, int talismanMainStat, int talismanCrit, int talismanValue
        , string armorName, int armorDef, int armorHealth, int armorValue,
        string headGearName, int headGearDef, int headGearVal, int headgearValue, string headGearMainstat,
        string shieldName, int shieldDef, int shieldBlockChance, int shieldValue) = 0;
    virtual void ShowStatistics(string name, string prof, string mainStatName, string skill, int level, int mainStat, int maxHealth, int currHealth, int minAttack,
        int maxAttack, double crit, int def, int money, double block = 0.) = 0;

    virtual void ShowOneItem(string type, string prof, int value, string name, int val1, int val2, int val3,string mainStatName) = 0;

    virtual void CompletedEqChanging() = 0;
    virtual void BreakLine() = 0;
    virtual void EndGameMessage() = 0;
};

class TXTView : public View {
public:
    TXTView();

    //game
    void OneOptionToMoveOn();
    void TwoOpitonsToMoveOn();


    //chambers
    void OptionsForGoNext(int i);
    void NotRecognizedCharacter();
    void GameSuccesfullFinished() ;
    void GameAlmostFinished();


    //events
    void DescriptionEndPoint();
    void DescriptionEnterToMonsterRoom();
    void DescriptionFight();
    void DescriptionRunAway();
    void DescriptionCheckChest();
    void DescriptionEnterToTrapRoom();
    void DescriptionActiveTheTrap();
    void DescriptionEnterToPotionRoom();
    void DescriptionDrinkPotion();
    void DescriptionEnterToTreasureRoom();
    void DescriptionEnterToHealthRoom();
    void DescriptionHealthYourself();
    void DescriptionEnterToTraderRoom();
    void DescriptionSeeItems();
    void DescriptionEnterToEmptyRoom();
    void DescriptionEnterToStartingRoom();
    void DescriptionEnterToBossRoom();
    void DescriptionBossFight();

    void GoldFoundInChest(int i);
    void ItemFoundInChest();
    void ShowItemToChange();
    void DecisiontToReplaceItem();

    void CheckStatisticsOrEquipment();

    void EnteredToMonsterRoom();
    void ShowCurrentHealth(int curr, int max);
    void MonsterDefeated();
    void RemainingHealth(int curr);
    void LevelUp(int lvl);
    void EscapeWithBeingHit();
    void EscapeWithoutBeingHit();
    void ChestFound();

    void EnteredToTrapRoom();
    void HurtedByTrap();

    void EnteredToPotionRoom();
    void HealthRestoredByPotion();
    void HealthLostByPoisonedPotion(int lost);

    void EnteredToTreasureRoom();

    void EnteredToHealthRoom();
    void HealthRestoredByMagicFountain();

    void EnteredToTraderRoom();
    void ShowMerchantItemWithPrice(int num, int price);
    void ShowGoldBalance(int bal);
    void DecisionToBuySomething();
    void SelectNumberOfItemToBuy();
    void SelectedItemHasAlreadyBeenBought();
    void InvalidItemNumber();
    void DecisionToBuyingAnotherItem();
    void AllItemsHaveAlreadyBeenBought();
    void DecisionToNegotiateItemPrice();
    void PriceOfferForItem();

    void EnteredToEmptyRoom();

    void EnteredToStartingRoom();

    void EnteredToBossRoom();
    void BossDefeated();
    void HeroDefeatedByBoss();


    //items
    void InvalidClassValue();


    //strategy
    void NotEnoughtGoldToBuyItem();
    void MuchTooLowOfferForItem();
    void FairPriceOfferForItem();
    void AlmostFairPriceOfferForItem(int offer);
    void ShowFinalPrice(int price);


    //character (character1, character2);
    void ShowCourseOfRound(string ch1, string ch2, int damage);
    void ShowCurrentHealthAfterRound(string ch, int currH);
    void DodgedHit(string ch1, string ch2);
    void BlockedHit(string ch1, string ch2);

    void ShowPossibleClassesToChoose(string name);
    void IncorrectNumber(int min, int max);
    void ShowChoosenClass(int ch);

    void WriteHeroName();

    void ShowEqiupment(string prof, string weaponName, int minDamage, int maxDamage, string mainStateName, int weaponMainStat, int weaponValue,
        string talismanName, string talismanMainStatName, int talismanMainStat, int talismanCrit, int talismanValue,
        string armorName, int armorDef, int armorHealth, int armorValue,
        string headGearName, int headGearDef, int headGearVal=0, int headgearValue=0, string headGearMainstat="",
        string shieldName="", int shieldDef = 0, int shieldBlockChance = 0, int shieldValue = 0);
    void ShowStatistics(string name, string prof, string mainStatName, string skill, int level, int mainStat, int maxHealth, int currHealth, int minAttack,
        int maxAttack, double crit, int def, int money, double block = 0.);

    void ShowOneItem(string type, string prof, int value, string name, int val1=0, int val2=0, int val3=0, string mainStatName="");

    void CompletedEqChanging();
    void BreakLine();
    void EndGameMessage();
};
#endif
