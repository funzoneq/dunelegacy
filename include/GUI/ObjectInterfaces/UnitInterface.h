/*
 *  This file is part of Dune Legacy.
 *
 *  Dune Legacy is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Dune Legacy is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Dune Legacy.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEFAULTUNITINTERFACE_H
#define DEFAULTUNITINTERFACE_H

#include "DefaultObjectInterface.h"

#include <globals.h>

#include <FileClasses/GFXManager.h>
#include <FileClasses/TextManager.h>

#include <GUI/TextButton.h>
#include <GUI/SymbolButton.h>
#include <GUI/HBox.h>
#include <GUI/VBox.h>

#include <units/UnitBase.h>
#include <units/MCV.h>
#include <units/Harvester.h>
#include <units/Devastator.h>

class UnitInterface : public DefaultObjectInterface {
public:
	static UnitInterface* create(int objectID) {
		UnitInterface* tmp = new UnitInterface(objectID);
		tmp->pAllocated = true;
		return tmp;
	}

protected:
	UnitInterface(int objectID) : DefaultObjectInterface(objectID) {
        Uint32 color = SDL2RGB(palette[houseColor[pLocalHouse->getHouseID()]]);

		mainHBox.addWidget(HSpacer::create(4));

		buttonVBox.addWidget(VSpacer::create(6));

        moveButton.setSymbol(pGFXManager->getUIGraphic(UI_CursorMove_Zoomlevel0), false);
		moveButton.setTooltipText(_("Move to a position (Hotkey: M)"));
		moveButton.setToggleButton(true);
		moveButton.setOnClick(std::bind(&UnitInterface::onMove, this));
		actionHBox.addWidget(&moveButton);

		actionHBox.addWidget(HSpacer::create(2));

		attackButton.setSymbol(pGFXManager->getUIGraphic(UI_CursorAttack_Zoomlevel0), false);
		attackButton.setTooltipText(_("Attack a unit, structure or position (Hotkey: A)"));
		attackButton.setToggleButton(true);
		attackButton.setOnClick(std::bind(&UnitInterface::onAttack, this));
		actionHBox.addWidget(&attackButton);

        actionHBox.addWidget(HSpacer::create(2));

        carryallDropButton.setSymbol(pGFXManager->getUIGraphic(UI_CursorCarryallDrop_Zoomlevel0), false);
        carryallDropButton.setTooltipText(_("Request Carryall drop to a position (Hotkey: D)"));
		carryallDropButton.setToggleButton(true);
		carryallDropButton.setOnClick(std::bind(&UnitInterface::onCarryallDrop, this));
		actionHBox.addWidget(&carryallDropButton);

		actionHBox.addWidget(HSpacer::create(2));

        captureButton.setSymbol(pGFXManager->getUIGraphic(UI_CursorCapture_Zoomlevel0), false);
        captureButton.setTooltipText(_("Capture a building (Hotkey: C)"));
        captureButton.setVisible((itemID == Unit_Soldier) || (itemID == Unit_Trooper));
		captureButton.setToggleButton(true);
		captureButton.setOnClick(std::bind(&UnitInterface::onCapture, this));
		actionHBox.addWidget(&captureButton);

		buttonVBox.addWidget(&actionHBox, 26);

		buttonVBox.addWidget(VSpacer::create(2));

        returnButton.setSymbol(pGFXManager->getUIGraphic(UI_ReturnIcon), false);
        returnButton.setTooltipText(_("Return harvester to refinery (Hotkey: H)"));
        returnButton.setVisible( (itemID == Unit_Harvester) );
		returnButton.setOnClick(std::bind(&UnitInterface::onReturn, this));
		commandHBox.addWidget(&returnButton);

		commandHBox.addWidget(HSpacer::create(2));

		deployButton.setSymbol(pGFXManager->getUIGraphic(UI_DeployIcon), false);
		deployButton.setTooltipText(_("Build a new construction yard"));
        deployButton.setVisible( (itemID == Unit_MCV) );
		deployButton.setOnClick(std::bind(&UnitInterface::onDeploy, this));
		commandHBox.addWidget(&deployButton);

        commandHBox.addWidget(HSpacer::create(2));

        destructButton.setSymbol(pGFXManager->getUIGraphic(UI_DestructIcon), false);
        destructButton.setTooltipText(_("Self-destruct this unit"));
		destructButton.setVisible( (itemID == Unit_Devastator) );
		destructButton.setOnClick(std::bind(&UnitInterface::onDestruct, this));
		commandHBox.addWidget(&destructButton);

        commandHBox.addWidget(HSpacer::create(2));

        sendToRepairButton.setSymbol(pGFXManager->getUIGraphic(UI_SendToRepairIcon), false);
        sendToRepairButton.setTooltipText(_("Repair this unit (Hotkey: R)"));
		sendToRepairButton.setOnClick(std::bind(&UnitInterface::OnSendToRepair, this));
		commandHBox.addWidget(&sendToRepairButton);

		buttonVBox.addWidget(&commandHBox, 26);

		buttonVBox.addWidget(VSpacer::create(6));

        guardButton.setText(_("Guard"));
        guardButton.setTextColor(color+3);
		guardButton.setTooltipText(_("Unit will not move from location"));
		guardButton.setToggleButton(true);
		guardButton.setOnClick(std::bind(&UnitInterface::onGuard, this));
		buttonVBox.addWidget(&guardButton, 26);

		buttonVBox.addWidget(VSpacer::create(6));

		areaGuardButton.setText(_("Area Guard"));
        areaGuardButton.setTextColor(color+3);
		areaGuardButton.setTooltipText(_("Unit will engage any unit within guard range"));
		areaGuardButton.setToggleButton(true);
		areaGuardButton.setOnClick(std::bind(&UnitInterface::onAreaGuard, this));
		buttonVBox.addWidget(&areaGuardButton, 26);

		buttonVBox.addWidget(VSpacer::create(6));

		stopButton.setText(_("Stop"));
        stopButton.setTextColor(color+3);
		stopButton.setTooltipText(_("Unit will not move, nor attack"));
		stopButton.setToggleButton(true);
		stopButton.setOnClick(std::bind(&UnitInterface::onStop, this));
		buttonVBox.addWidget(&stopButton, 26);

		buttonVBox.addWidget(VSpacer::create(6));

        ambushButton.setText(_("Ambush"));
        ambushButton.setTextColor(color+3);
		ambushButton.setTooltipText(_("Unit will not move until enemy unit spotted"));
		ambushButton.setToggleButton(true);
		ambushButton.setOnClick(std::bind(&UnitInterface::onAmbush, this));
		buttonVBox.addWidget(&ambushButton, 26);

		buttonVBox.addWidget(VSpacer::create(6));

        huntButton.setText(_("Hunt"));
        huntButton.setTextColor(color+3);
		huntButton.setTooltipText(_("Unit will immediately start to engage an enemy unit"));
		huntButton.setToggleButton(true);
		huntButton.setOnClick(std::bind(&UnitInterface::onHunt, this));
		buttonVBox.addWidget(&huntButton, 26);

		buttonVBox.addWidget(VSpacer::create(6));

		retreatButton.setText(_("Retreat"));
        retreatButton.setTextColor(color+3);
		retreatButton.setTooltipText(_("Unit will retreat back to base"));
		retreatButton.setToggleButton(true);
		retreatButton.setOnClick(std::bind(&UnitInterface::onRetreat, this));
		buttonVBox.addWidget(&retreatButton, 26);

		buttonVBox.addWidget(VSpacer::create(6));
		buttonVBox.addWidget(Spacer::create());
		buttonVBox.addWidget(VSpacer::create(6));

		mainHBox.addWidget(&buttonVBox);
		mainHBox.addWidget(HSpacer::create(5));

		update();
	}

    void onMove() {
        currentGame->currentCursorMode = Game::CursorMode_Move;
	}

	void onAttack() {
        currentGame->currentCursorMode = Game::CursorMode_Attack;
	}

    void onCapture() {
        currentGame->currentCursorMode = Game::CursorMode_Capture;
	}

    void onCarryallDrop() {
        currentGame->currentCursorMode = Game::CursorMode_CarryallDrop;
	}

    void OnSendToRepair() {
        ObjectBase* pObject = currentGame->getObjectManager().getObject(objectID);
        GroundUnit* pGroundUnit = dynamic_cast<GroundUnit*>(pObject);
        if((pGroundUnit != NULL) && (pGroundUnit->getHealth() < pGroundUnit->getMaxHealth())) {
            pGroundUnit->handleSendToRepairClick();
        }
	}

	void onReturn() {
		ObjectBase* pObject = currentGame->getObjectManager().getObject(objectID);
		Harvester* pHarvester = dynamic_cast<Harvester*>(pObject);
		if(pHarvester != NULL) {
			pHarvester->handleReturnClick();
		}
	}

	void onDeploy() {
		ObjectBase* pObject = currentGame->getObjectManager().getObject(objectID);
		MCV* pMCV = dynamic_cast<MCV*>(pObject);
		if(pMCV != NULL) {
			pMCV->handleDeployClick();
		}
	}

	void onDestruct() {
		ObjectBase* pObject = currentGame->getObjectManager().getObject(objectID);
		Devastator* pDevastator = dynamic_cast<Devastator*>(pObject);
		if(pDevastator != NULL) {
			pDevastator->handleStartDevastateClick();
		}
	}

    void onGuard() {
		setAttackMode(GUARD);
	}

	void onAreaGuard() {
		setAttackMode(AREAGUARD);
	}

    void onStop() {
		setAttackMode(STOP);
	}

	void onAmbush() {
		setAttackMode(AMBUSH);
	}

    void onHunt() {
		setAttackMode(HUNT);
	}

	void onRetreat(){
        setAttackMode(RETREAT);
	}

	void setAttackMode(ATTACKMODE newAttackMode) {
		ObjectBase* pObject = currentGame->getObjectManager().getObject(objectID);
		UnitBase* pUnit = dynamic_cast<UnitBase*>(pObject);

		if(pUnit != NULL) {
			pUnit->handleSetAttackModeClick(newAttackMode);
			pUnit->playConfirmSound();

			update();
		}
	}

	/**
		This method updates the object interface.
		If the object doesn't exists anymore then update returns false.
		\return true = everything ok, false = the object container should be removed
	*/
	virtual bool update() {
	    ObjectBase* pObject = currentGame->getObjectManager().getObject(objectID);
		if(pObject == NULL) {
			return false;
		}


        moveButton.setToggleState(currentGame->currentCursorMode == Game::CursorMode_Move);
		attackButton.setToggleState(currentGame->currentCursorMode == Game::CursorMode_Attack);
		attackButton.setVisible(pObject->canAttack());
		captureButton.setToggleState(currentGame->currentCursorMode == Game::CursorMode_Capture);
		carryallDropButton.setToggleState(currentGame->currentCursorMode == Game::CursorMode_CarryallDrop);
		carryallDropButton.setVisible(currentGame->getGameInitSettings().getGameOptions().manualCarryallDrops && pObject->getOwner()->hasCarryalls() > 0);
        sendToRepairButton.setVisible(pObject->getHealth() < pObject->getMaxHealth());

		UnitBase* pUnit = dynamic_cast<UnitBase*>(pObject);
		if(pUnit != NULL) {
			ATTACKMODE AttackMode = pUnit->getAttackMode();

			guardButton.setToggleState( AttackMode == GUARD );
            areaGuardButton.setToggleState( AttackMode == AREAGUARD );
            stopButton.setToggleState( AttackMode == STOP );
            ambushButton.setToggleState( AttackMode == AMBUSH );
            huntButton.setToggleState( AttackMode == HUNT );
            retreatButton.setToggleState( AttackMode == RETREAT );
		}

		return true;
	}

	HBox		    buttonHBox;
	VBox		    buttonVBox;
	HBox            actionHBox;
	HBox            commandHBox;

	SymbolButton    moveButton;
	SymbolButton    attackButton;
    SymbolButton    captureButton;
    SymbolButton    returnButton;
    SymbolButton    deployButton;
    SymbolButton    destructButton;
    SymbolButton    sendToRepairButton;
    SymbolButton    carryallDropButton;

    TextButton	    guardButton;
	TextButton	    areaGuardButton;
	TextButton      stopButton;
	TextButton	    ambushButton;
	TextButton      huntButton;
	TextButton      retreatButton;

};

#endif //DEFAULTUNITINTERFACE_H
