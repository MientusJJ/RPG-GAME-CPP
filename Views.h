#pragma once
#ifndef VIEWS_H
#define VIEWS_H
#include <string>
class View {
public:
    //game
    virtual void OneOptionToMoveOn();
    virtual void TwoOpitonsToMoveOn();


    //chambers
    virtual void OptionsForGoNext(int i);
    virtual void NotRecognizedCharacter();


    //events
    virtual void DescriptionEndPoint();
    virtual void DescriptionEnterToMonsterRoom();
    virtual void DescriptionFight();
    virtual void DescriptionRunAway();
    virtual void DescriptionCheckChest();
    virtual void DescriptionEnterToTrapRoom();
    virtual void DescriptionActiveTheTrap();
    virtual void DescriptionEnterToPotionRoom();
    virtual void DescriptionDrinkPotion();
    virtual void DescriptionEnterToTreasureRoom();
    virtual void DescriptionEnterToHealthRoom();
    virtual void DescriptionHealthYourself();
    virtual void DescriptionEnterToTraderRoom();
    virtual void DescriptionSeeItems();
    virtual void DescriptionEnterToEmptyRoom();
    virtual void DescriptionEnterToStartingRoom();
    virtual void DescriptionEnterToBossRoom();
    virtual void DescriptionBossFight();



    virtual void GoldFoundInChest(int i);
    virtual void ItemFoundInChest();
    virtual void ShowItemToChange();
    virtual void DecisiontToReplaceItem();

    virtual void CheckStatisticsOrEquipment();

    virtual void EnteredToMonsterRoom();
    virtual void ShowCurrentHealth(int curr, int max);
    virtual void MonsterDefeated();
    virtual void RemainingHealth(int curr);
    virtual void LevelUp(int lvl);
    virtual void EscapeWithBeingHit();
    virtual void EscapeWithoutBeingHit();
    virtual void ChestFound();

    virtual void EnteredToTrapRoom();
    virtual void HurtedByTrap();

    virtual void EnteredToPotionRoom();
    virtual void HealthRestoredByPotion();
    virtual void HealthLostByPoisonedPotion(int lost);

    virtual void EnteredToTreasureRoom();

    virtual void EnteredToHealthRoom();
    virtual void HealthRestoredByMagicFountain();

    virtual void EnteredToTraderRoom();
    virtual void ShowMerchantItemWithPrice(int num, int price);
    virtual void ShowGoldBalance(int bal);
    virtual void DecisionToBuySomething();
    virtual void SelectNumberOfItemToBuy();
    virtual void SelectedItemHasAlreadyBeenBought();
    virtual void InvalidItemNumber();
    virtual void DecisionToBuyingAnotherItem();
    virtual void AllItemsHaveAlreadyBeenBought();
    virtual void DecisionToNegotiateItemPrice();
    virtual void PriceOfferForItem();

    virtual void EnteredToEmptyRoom();

    virtual void EnteredToStartingRoom();

    virtual void EnteredToBossRoom();
    virtual void BossDefeated();
    virtual void HeroDefeatedByBoss();


    //items
    virtual void InvalidClassValue();


    //strategy
    virtual void NotEnoughtGoldToBuyItem();
    virtual void MuchTooLowOfferForItem();
    virtual void FairPriceOfferForItem();
    virtual void AlmostFairPriceOfferForItem(int offer);
    virtual void ShowFinalPrice(int price);


    //character (character1, character2);
    virtual void ShowCourseOfRound(string ch1, string ch2, int damage);
    virtual void ShowCurrentHealthAfterRound(string ch, int currH);
    virtual void DodgedHit(string ch1, string ch2);
    virtual void BlockedHit(string ch1, string ch2);

    virtual void ShowPossibleClassesToChoose(string name);
    virtual void IncorrectNumber(int min, int max);
    virtual void ShowChoosenClass(int ch);

    virtual void WriteHeroName();

    virtual void ShowEqiupment(string prof, string weaponName, int minDamage, int maxDamage, string mainStateName, int weaponMainStat, int weaponValue
        , string talismanName, string talismanMainStatName, int talismanMainStat, int talismanCrit, int talismanValue
        , string armorName, int armorDef, int armorHealth, int armorValue
        , string headGearName, int headGearDef, int headGearVal, int headgearValue, string headGearMainstat
        , string shieldName, int shieldDef, int shieldBlockChance, int shieldValue);
    virtual void ShowStatistics(string name, string prof, string mainStatName, string skill, int level, int mainStat, int maxHealth, int currHealth, int minAttack,
        int maxAttack, double crit, int def, int money, double block = 0.);

    virtual void ShowOneItem(string type, string prof, int value, string name, int val1, int val2, int val3,string mainStatName);

    virtual void CompletedEqChanging();
};

class TXTView : View {
public:
    //game
    void OneOptionToMoveOn() override;
    void TwoOpitonsToMoveOn() override;


    //chambers
    void OptionsForGoNext(int i) override;
    void NotRecognizedCharacter() override;


    //events
    void DescriptionEndPoint() override;
    void DescriptionEnterToMonsterRoom() override;
    void DescriptionFight() override;
    void DescriptionRunAway() override;
    void DescriptionCheckChest() override;
    void DescriptionEnterToTrapRoom() override;
    void DescriptionActiveTheTrap() override;
    void DescriptionEnterToPotionRoom() override;
    void DescriptionDrinkPotion() override;
    void DescriptionEnterToTreasureRoom() override;
    void DescriptionEnterToHealthRoom() override;
    void DescriptionHealthYourself() override;
    void DescriptionEnterToTraderRoom() override;
    void DescriptionSeeItems() override;
    void DescriptionEnterToEmptyRoom() override;
    void DescriptionEnterToStartingRoom() override;
    void DescriptionEnterToBossRoom() override;
    void DescriptionBossFight() override;

    void GoldFoundInChest(int i) override;
    void ItemFoundInChest() override;
    void ShowItemToChange() override;
    void DecisiontToReplaceItem() override;

    void CheckStatisticsOrEquipment() override;

    void EnteredToMonsterRoom() override;
    void ShowCurrentHealth(int curr, int max) override;
    void MonsterDefeated() override;
    void RemainingHealth(int curr) override;
    void LevelUp(int lvl) override;
    void EscapeWithBeingHit() override;
    void EscapeWithoutBeingHit() override;
    void ChestFound() override;

    void EnteredToTrapRoom() override;
    void HurtedByTrap() override;

    void EnteredToPotionRoom() override;
    void HealthRestoredByPotion() override;
    void HealthLostByPoisonedPotion(int lost) override;

    void EnteredToTreasureRoom() override;

    void EnteredToHealthRoom() override;
    void HealthRestoredByMagicFountain() override;

    void EnteredToTraderRoom() override;
    void ShowMerchantItemWithPrice(int num, int price) override;
    void ShowGoldBalance(int bal) override;
    void DecisionToBuySomething() override;
    void SelectNumberOfItemToBuy() override;
    void SelectedItemHasAlreadyBeenBought() override;
    void InvalidItemNumber() override;
    void DecisionToBuyingAnotherItem() override;
    void AllItemsHaveAlreadyBeenBought() override;
    void DecisionToNegotiateItemPrice() override;
    void PriceOfferForItem() override;

    void EnteredToEmptyRoom() override;

    void EnteredToStartingRoom() override;

    void EnteredToBossRoom() override;
    void BossDefeated() override;
    void HeroDefeatedByBoss() override;


    //items
    void InvalidClassValue() override;


    //strategy
    void NotEnoughtGoldToBuyItem() override;
    void MuchTooLowOfferForItem() override;
    void FairPriceOfferForItem() override;
    void AlmostFairPriceOfferForItem(int offer) override;
    void ShowFinalPrice(int price) override;


    //character (character1, character2);
    void ShowCourseOfRound(string ch1, string ch2, int damage) override;
    void ShowCurrentHealthAfterRound(string ch, int currH) override;
    void DodgedHit(string ch1, string ch2) override;
    void BlockedHit(string ch1, string ch2) override;

    void ShowPossibleClassesToChoose(string name) override;
    void IncorrectNumber(int min, int max) override;
    void ShowChoosenClass(int ch) override;

    void WriteHeroName() override;

    void ShowEqiupment(string prof, string weaponName, int minDamage, int maxDamage, string mainStateName, int weaponMainStat, int weaponValue,
        string talismanName, string talismanMainStatName, int talismanMainStat, int talismanCrit, int talismanValue,
        string armorName, int armorDef, int armorHealth, int armorValue,
        string headGearName, int headGearDef, int headGearVal, int headgearValue, string headGearMainstat="",
        string shieldName="", int shieldDef = 0, int shieldBlockChance = 0, int shieldValue = 0) override;
    void ShowStatistics(string name, string prof, string mainStatName, string skill, int level, int mainStat, int maxHealth, int currHealth, int minAttack,
        int maxAttack, double crit, int def, int money, double block = 0.) override;

    void ShowOneItem(string type, string prof, int value, string name, int val1=0, int val2=0, int val3=0, string mainStatName="") override;

    void CompletedEqChanging() override;
};
#endif
