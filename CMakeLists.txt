cmake_minimum_required(VERSION 3.6)
project(TPGrupal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        clientMain.cpp
        commonDicc.h
        commonHeap.h
        commonParser.cpp commonParser.h
        commonException.cpp commonException.h
        commonSocket.cpp commonSocket.h
        commonThreads.cpp commonThreads.h
        commonLock.cpp commonLock.h
        commonQueue.h


        serverSettings.cpp serverSettings.h
        serverMain.cpp
        server.cpp server.h
        serverMap.cpp serverMap.h

        serverUnit.cpp serverUnit.h
        serverRobot.cpp serverRobot.h
        serverGrunt.cpp serverGrunt.h
        serverTough.cpp serverTough.h
        serverSniper.cpp serverSniper.h
        serverPsycho.cpp serverPsycho.h
        serverPyro.cpp serverPyro.h
        serverRobotLaser.cpp serverRobotLaser.h
        serverVehicle.cpp serverVehicle.h
        serverJeep.cpp serverJeep.h
        serverLightTank.cpp serverLightTank.h
        serverMediumTank.cpp serverMediumTank.h
        serverHeavyTank.cpp serverHeavyTank.h
        serverMML.cpp serverMML.h

        serverArmament.cpp serverArmament.h
        serverBullets.cpp serverBullets.h
        serverHighCaliberProjectiles.cpp serverHighCaliberProjectiles.h
        serverMissiles.cpp serverMissiles.h
        serverFlamethrower.cpp serverFlamethrower.h
        serverArmamentLaser.cpp serverArmamentLaser.h

        serverPlayer.cpp serverPlayer.h
        serverGlobal.cpp
        serverGame.cpp serverGame.h

        serverTask.cpp serverTask.h
        serverTaskCreateGrunt.cpp serverTaskCreateGrunt.h
        serverTaskCreateTough.cpp serverTaskCreateTough.h
        serverTaskCreateSniper.cpp serverTaskCreateSniper.h
        serverTaskCreatePsycho.cpp serverTaskCreatePsycho.h
        serverTaskCreatePyro.cpp serverTaskCreatePyro.h
        serverTaskCreateLaser.cpp serverTaskCreateLaser.h
        serverTaskCreateJeep.cpp serverTaskCreateJeep.h
        serverTaskCreateLightTank.cpp serverTaskCreateLightTank.h
        serverTaskCreateMediumTank.cpp serverTaskCreateMediumTank.h
        serverTaskCreateHeavyTank.cpp serverTaskCreateHeavyTank.h
        serverTaskCreateMML.cpp serverTaskCreateMML.h
        serverTaskMove.cpp serverTaskMove.h
        serverTaskAttackUnit.cpp serverTaskAttackUnit.h
        serverTaskAttackObject.cpp serverTaskAttackObject.h
        serverTaskShoot.cpp serverTaskShoot.h
        serverTaskMoveMunition.cpp serverTaskMoveMunition.h
        serverTaskShootUnit.cpp serverTaskShootUnit.h
        serverTaskShootObject.cpp serverTaskShootObject.h

        serverStateAttack.cpp serverStateAttack.h

        serverState.cpp serverState.h
        serverStateMoving.cpp serverStateMoving.h
        serverStateStill.cpp serverStateStill.h
        serverStateAttackingUnit.cpp serverStateAttackingUnit.h
        serverStateAttackingObject.cpp serverStateAttackingObject.h
        serverStateDead.cpp serverStateDead.h
        serverStateBroken.cpp serverStateBroken.h

        serverNodePath.cpp serverNodePath.h
        serverTeam.cpp serverTeam.h

        serverTerritories.cpp serverTerritories.h

        serverNode.cpp serverNode.h
        serverLava.cpp serverLava.h
        serverEarthPrairieSnow.cpp serverEarthPrairieSnow.h
        serverDust.cpp serverDust.h
        serverGrass.cpp serverGrass.h
        serverSnow.cpp serverSnow.h
        serverWaterSwamp.cpp serverWaterSwamp.h
        serverWater.cpp serverWater.h
        serverSwamp.cpp serverSwamp.h
        serverRoadAsphaltRoad.cpp serverRoadAsphaltRoad.h
        serverRoad.cpp serverRoad.h
        serverAsphaltRoad.cpp serverAsphaltRoad.h

        serverObject.cpp serverObject.h
        serverFlag.cpp serverFlag.h
        serverBuildings.cpp serverBuildings.h
        serverFort.cpp serverFort.h
        serverVehicleFactorie.cpp serverVehicleFactorie.h
        serverRobotFactorie.cpp serverRobotFactorie.h
        serverBridges.cpp serverBridges.h
        serverWoodenBridge.cpp serverWoodenBridge.h
        serverConcreteBridge.cpp serverConcreteBridge.h
        serverSolids.cpp serverSolids.h
        serverStone.cpp serverStone.h
        serverIceBlock.cpp serverIceBlock.h

        serverProxyClient.cpp serverProxyClient.h
        serverInterpreter.cpp serverInterpreter.h

        client_WoodBridge.cpp client_WoodBridge.h
        client_WalkAction.cpp client_WalkAction.h
        client_Vehicle.cpp client_Vehicle.h
        client_Unit.cpp client_Unit.h
        client_Tile.cpp client_Tile.h
        client_Territory.cpp client_Territory.h
        client_TerrainObject.cpp client_TerrainObject.h
        client_SwampTile.cpp client_SwampTile.h
        client_Robot.cpp client_Robot.h
        client_Map.cpp client_Map.h
        client_GrassTile.cpp client_GrassTile.h
        client_GameObject.cpp client_GameObject.h
        client_Frame.cpp client_Frame.h
        client_Fort.cpp client_Fort.h
        client_Flag.cpp client_Flag.h
        client_Building.cpp client_Building.h
        client_BuildingInterface.cpp client_BuildingInterface.h
        client_Button.cpp client_Button.h
        client_CreateButton.cpp client_CreateButton.h
        client_FortInterface.cpp client_FortInterface.h
        client_LightTank.cpp client_LightTank.h
        client_UnitAction.cpp client_UnitAction.h
        client_ShootAction.cpp client_ShootAction.h
        client_MouseEventHandler.cpp client_MouseEventHandler.h
        client_LaserAmmo.cpp client_LaserAmmo.h
        client_Grunt.cpp client_Grunt.h
        client_Laser.cpp client_Laser.h
        client_Ammo.cpp client_Ammo.h
        client_Camera.cpp client_Camera.h
        client_CreateGruntButton.cpp client_CreateGruntButton.h
        client_CreateLaserButton.cpp client_CreateLaserButton.h
        client_CreateLightTankButton.cpp client_CreateLightTankButton.h
        client_DieAction.cpp client_DieAction.h
        client_StandStillAction.cpp client_StandStillAction.h
        client_ConcreteBridge.cpp client_ConcreteBridge.h
        client_CreateHeavyTankButton.cpp client_CreateHeavyTankButton.h
        client_CreateMediumTankButton.cpp client_CreateMediumTankButton.h
        client_CreateMMLButton.cpp client_CreateMMLButton.h
        client_CreatePsychoButton.cpp client_CreatePsychoButton.h
        client_CreateJeepButton.cpp client_CreateJeepButton.h
        client_CreatePyroButton.cpp client_CreatePyroButton.h
        client_CreateSniperButton.cpp client_CreateSniperButton.h
        client_CreateToughButton.cpp client_CreateToughButton.h
        client_DustTile.cpp client_DustTile.h
        client_HighWayTile.cpp client_HighWayTile.h
        client_IceBlock.cpp client_IceBlock.h
        client_LavaTile.cpp client_LavaTile.h
        client_RFactory.cpp client_RFactory.h
        client_RFactoryInterface.cpp client_RFactoryInterface.h
        client_RoadAsphaltTile.cpp client_RoadAsphaltTile.h
        client_Rock.cpp client_Rock.h
        client_SnowTile.cpp client_SnowTile.h
        client_VFactory.cpp client_VFactory.h
        client_VFactoryInterface.cpp client_VFactoryInterface.h
        client_WaterTile.cpp client_WaterTile.h
        client_BigExplosion.cpp client_BigExplosion.h
        client_BulletAmmo.cpp client_BulletAmmo.h
        client_Explosion.cpp client_Explosion.h
        client_HeavyTank.cpp client_HeavyTank.h
        client_HighCaliberAmmo.cpp client_HighCaliberAmmo.h
        client_Jeep.cpp client_Jeep.h
        client_LittleExplosion.cpp client_LittleExplosion.h
        client_MediumTank.cpp client_MediumTank.h
        client_MissileAmmo.cpp client_MissileAmmo.h
        client_MML.cpp client_MML.h
        client_Psycho.cpp client_Psycho.h
        client_Pyro.cpp client_Pyro.h
        client_PyroAmmo.cpp client_PyroAmmo.h
        client_Sniper.cpp client_Sniper.h
        client_Tough.cpp client_Tough.h
        client_OutcomeWindow.cpp client_OutcomeWindow.h
        client_KeyboardEventHandler.cpp client_KeyboardEventHandler.h

        clientProxyGame.cpp clientProxyGame.h
        clientInterpreter.cpp clientInterpreter.h
        clientProxyMunition.cpp clientProxyMunition.h
        clientProxyUnit.cpp clientProxyUnit.cpp
        clientProxyNode.cpp clientProxyNode.h
        clientProxyTerritories.cpp clientProxyTerritories.h
        clientProxyObject.cpp clientProxyObject.h
        clientCommunicator.cpp clientCommunicator.h
        clientPlayer.cpp clientPlayer.h client.cpp client.h)
add_executable(TPGrupal ${SOURCE_FILES})