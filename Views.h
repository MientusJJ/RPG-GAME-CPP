#pragma once
#ifndef VIEWS_H
#define VIEWS_H
class View {
public:
    //game
    virtual void OneOptionToMoveOn();
    virtual void TwoOpitonsToMoveOn();


    //chambers
    virtual void OptionsForGoNext();
    virtual void NotRecognizedCharacter();


    //events
    virtual void GoldFoundInChets();
    virtual void ItemFoundInChest();
    virtual void ShowItemToChange();
    virtual void DecisiontToReplaceItem();

    virtual void CheckStatisticsOrEquipment();

    virtual void EnteredToMonsterRoom();
    virtual void ShowCurrentHealth();
    virtual void MonsterDefeated();
    virtual void LevelUp();
    virtual void EscapeWithBeingHit();
    virtual void EscapeWithoutBeingHit();
    virtual void ChestFound();

    virtual void EnteredToTrapRoom();
    virtual void HurtedByTrap();

    virtual void EnteredToPotionRoom();
    virtual void HealthRestoredByPotion();
    virtual void HealthLostByPoisonedPotion();

    virtual void EnteredToTreasureRoom();

    virtual void EnteredToHealthRoom();
    virtual void HealthRestoredByMagicFountain();

    virtual void EnteredToTraderRoom();
    virtual void ShowMerchantItemsWithPrices();
    virtual void ShowGoldBalance();
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
    virtual void AlmostFairPriceOfferForItem();
    virtual void ShowFinalPrice();


    //character (character1, character2);
    virtual void ShowCourseOfRound();
    virtual void ShowCurrentHealthAfterRound();
    virtual void DodgedHit();
    virtual void BlockedHit();

    virtual void ShowPossibleClassesToChoose();
    virtual void IncorrectNumber();
    virtual void ShowChoosenClass();

    virtual void WriteHeroName();

    virtual void ShowEqiupment();
    virtual void ShowStatistics();

    virtual void ShowOneItem();

    virtual void CompletedEqChanging();
};

class TXTView : View {
public:
    //chambers
    void OptionsForGoNext() override;
    void NotRecognizedCharacter() override;


    //events
    void GoldFoundInChets() override;
    void ItemFoundInChest() override;
    void ShowItemToChange() override;
    void DecisiontToReplaceItem() override;

    void CheckStatisticsOrEquipment() override;

    void EnteredToMonsterRoom() override;
    void ShowCurrentHealth() override;
    void MonsterDefeated() override;
    void LevelUp() override;
    void EscapeWithBeingHit() override;
    void EscapeWithoutBeingHit() override;
    void ChestFound() override;

    void EnteredToTrapRoom() override;
    void HurtedByTrap() override;

    void EnteredToPotionRoom() override;
    void HealthRestoredByPotion() override;
    void HealthLostByPoisonedPotion() override;

    void EnteredToTreasureRoom() override;

    void EnteredToHealthRoom() override;
    void HealthRestoredByMagicFountain() override;

    void EnteredToTraderRoom() override;
    void ShowMerchantItemsWithPrices() override;
    void ShowGoldBalance() override;
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
    void AlmostFairPriceOfferForItem() override;
    void ShowFinalPrice() override;


    //character (character1, character2);
    void ShowCourseOfRound() override;
    void ShowCurrentHealthAfterRound() override;
    void DodgedHit() override;
    void BlockedHit() override;

    void ShowPossibleClassesToChoose() override;
    void IncorrectNumber() override;
    void ShowChoosenClass() override;

    void WriteHeroName() override;

    void ShowEqiupment() override;
    void ShowStatistics() override;

    void ShowOneItem() override;

    void CompletedEqChanging() override;
};
#endif
