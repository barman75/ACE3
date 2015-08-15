#define REFUEL_ACTION_DISTANCE 4.5
#define MACRO_REFUEL_ACTIONS \
        class ACE_Actions : ACE_Actions { \
            class ACE_MainActions : ACE_MainActions { \
                class GVAR(TakeNozzle) { \
                    displayName = CSTRING(TakeNozzle); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE([ARR_2(_player,_target)] call FUNC(canTakeNozzle)); \
                    statement = QUOTE([ARR_3(_player,_target,objNull)] call FUNC(TakeNozzle)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
                class GVAR(CheckFuel) { \
                    displayName = CSTRING(CheckFuel); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE(([ARR_2(_player,_target)] call FUNC(getFuel) >= 0) && {(_target distance _player) < REFUEL_ACTION_DISTANCE}); \
                    statement = QUOTE([ARR_2(_player,_target)] call FUNC(checkFuel)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
                class GVAR(connect) { \
                    displayName = CSTRING(Return); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE([ARR_1(_player)] call FUNC(canConnectNozzle)); \
                    statement = QUOTE([ARR_2(_player,_target)] call DFUNC(connectNozzle)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
            }; \
        }; 
#define MACRO_CONNECT_ACTIONS \
        class ACE_Actions { \
            class ACE_MainActions { \
                displayName = ECSTRING(interaction,MainAction); \
                selection = ""; \
                distance = 10; \
                condition = "true"; \
                class GVAR(connect) { \
                    displayName = CSTRING(connect); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE([ARR_1(_player)] call FUNC(canConnectNozzle)); \
                    statement = QUOTE([ARR_2(_player,_target)] call DFUNC(connectNozzle)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
                class GVAR(Disconnect) { \
                    displayName = CSTRING(Disconnect); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE([ARR_2(_player,_target)] call FUNC(canDisconnect)); \
                    statement = QUOTE([ARR_2(_player,_target)] call DFUNC(disconnect)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
                class GVAR(TurnOff) { \
                    displayName = CSTRING(TurnOff); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE([ARR_2(_player,_target)] call FUNC(canTurnOff)); \
                    statement = QUOTE([ARR_2(_player,_target)] call DFUNC(turnOff)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
            }; \
        }; 

// does not work
#define MACRO_NOZZLE_ACTIONS \
        class ACE_Actions { \
            class ACE_MainActions { \
                displayName = ECSTRING(interaction,MainAction); \
                selection = ""; \
                distance = 2; \
                condition = "true"; \
                class GVAR(TakeNozzle) { \
                    displayName = CSTRING(TakeNozzle); \
                    distance = REFUEL_ACTION_DISTANCE; \
                    condition = QUOTE([ARR_2(_player,_target)] call FUNC(canTakeNozzle)); \
                    statement = QUOTE([ARR_3(_player,_target,_target)] call FUNC(TakeNozzle)); \
                    exceptions[] = {"isNotInside"}; \
                    icon = PATHTOF(ui\icon_refuel_interact.paa); \
                }; \
            }; \
        };
        
class CfgVehicles {
    class ACE_Module;
    class ACE_moduleRefuelSettings : ACE_Module {
        scope = 2;
        displayName = CSTRING(RefuelSettings_Module_DisplayName);
        icon = QUOTE(PATHTOF(ui\icon_module_refuel.paa));
        category = "ACE";
        function = QUOTE(DFUNC(moduleRefuelSettings));
        functionPriority = 1;
        isGlobal = 0;
        isTriggerActivated = 0;
        author = ECSTRING(common,ACETeam);
        class Arguments {
            class rate {
                displayName = CSTRING(RefuelSettings_speed_DisplayName);
                description = CSTRING(RefuelSettings_speed_Description);
                typeName = "NUMBER";
                class values {
                    class fast {
                        name = CSTRING(RefuelSettings_basic);
                        value = 10;
                    };
                    class realistic  {
                        name = CSTRING(RefuelSettings_advanced);
                        value = 1;
                        default = 1;
                    };
                };
            };
        };
    };
    
    class Sign_Sphere10cm_F;
    
    class ACE_refuel_fuelNozzle : Sign_Sphere10cm_F { 
        // TODO replace with custom model
    };

    class All;
    
    class Static : All {};
    
    class Building : Static {
        class ACE_Actions {
            class ACE_MainActions {
                displayName = ECSTRING(interaction,MainAction);
                selection = "";
                distance = 10;
                condition = "true";
            };
        };
    };
    
    class NonStrategic : Building {};
    
    class House_Base : NonStrategic {};
    
    class House : House_Base {};
    
    class House_F : House {};
    
    class House_Small_F : House_F {};
    
    class Strategic : Building {};
    
    class AllVehicles : All {
        GVAR(flowRate) = 1;
    };
    class Land : AllVehicles {};
    class LandVehicle : Land {};
    class Car : LandVehicle {
        MACRO_CONNECT_ACTIONS
    };

    class Tank : LandVehicle {
        MACRO_CONNECT_ACTIONS
    };
    
    class StaticWeapon : LandVehicle {
        MACRO_CONNECT_ACTIONS
    };

    class Air : AllVehicles {
        GVAR(flowRate) = 8;
    };
    
    class Helicopter : Air {
        MACRO_CONNECT_ACTIONS
        GVAR(fuelCapacity) = 1500;
    };
    
    class Helicopter_Base_F : Helicopter {};
    
    class Helicopter_Base_H : Helicopter_Base_F {
        GVAR(fuelCapacity) = 3000;
    };

    class Plane : Air {
        MACRO_CONNECT_ACTIONS
        GVAR(fuelCapacity) = 2000;
        GVAR(flowRate) = 16;
    };
    
    class Plane_Base_F : Plane {};

    class Ship : AllVehicles {};
    
    class Ship_F : Ship {
        MACRO_CONNECT_ACTIONS
        GVAR(fuelCapacity) = 2000;
    };

    class Boat_Civil_01_base_F : Ship_F {
        GVAR(fuelCapacity) = 200;
    };
    
    class Boat_F : Ship_F {};
    
    class Boat_Armed_01_base_F : Boat_F {
        GVAR(fuelCapacity) = 1000;
    };
    class Rubber_duck_base_F : Boat_F  {
        GVAR(fuelCapacity) = 30;
    };
    class SDV_01_base_F : Boat_F {
        // SDV is using electrical propulsion
        GVAR(fuelCapacity) = 0;
    };
   
    class Car_F : Car {
        // Assuming large vehicle tank
        GVAR(fuelCapacity) = 60;
    };
    
    class Kart_01_Base_F : Car_F {
        GVAR(fuelCapacity) = 8;
    };
    
    class Offroad_01_base_F: Car_F {};
    
    class Wheeled_APC_F: Car_F {
        // Assuming average APC tank
        GVAR(fuelCapacity) = 300;
    };
    
    class Hatchback_01_base_F: Car_F {
        // Assume normal vehicle tank
        GVAR(fuelCapacity) = 50;
    };
    
    class Quadbike_01_base_F : Car_F {
        // Assuming usual Yamaha quad
        GVAR(fuelCapacity) = 10;
    };
    
    class MRAP_01_base_F: Car_F {
        // M-ATV
        // No data, assuming similar to Fennek
        GVAR(fuelCapacity) = 230;
    };

    class MRAP_02_base_F: Car_F {
        // Punisher
        // No data, assuming similar to Fennek
        GVAR(fuelCapacity) = 230;
    };

    class MRAP_03_base_F: Car_F {
        // Fennek
        GVAR(fuelCapacity) = 230;
    };
    
    class APC_Wheeled_01_base_F: Wheeled_APC_F {
        // Patria = LAV
        GVAR(fuelCapacity) = 269;
    };

    class Truck_F : Car_F {
        GVAR(fuelCapacity) = 400;
    };
    
    class Truck_01_base_F: Truck_F {
        // HEMTT
        GVAR(fuelCapacity) = 583;
    };
    
    class B_Truck_01_transport_F : Truck_01_base_F {};
    
    class B_Truck_01_mover_F: B_Truck_01_transport_F {};
    
    class Truck_02_base_F: Truck_F {
        // KamAZ
        // Assuming similar to Ural
        GVAR(fuelCapacity) = 400;
    };
    
    class Truck_03_base_F: Truck_F {
        // Tempest
        // Assuming heavier than KamAZ
        GVAR(fuelCapacity) = 600;
    };
    
    class Van_01_base_F : Truck_F {
        // Small Truck
        // Assuming 80L as in Ford Transit
        GVAR(fuelCapacity) = 80;
    };
    
    class Van_01_fuel_base_F : Van_01_base_F {
        transportFuel = 0; //1k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 2000;
    };
    
    class Tank_F : Tank {
        GVAR(fuelCapacity) = 1200; 
    };
    
    class APC_Tracked_01_base_F: Tank_F {
        // Namer
        // Assuming Merkava fuel
        GVAR(fuelCapacity) = 1400; 
    };
    
    class B_APC_Tracked_01_base_F: APC_Tracked_01_base_F {};
    
    class B_APC_Tracked_01_CRV_F : B_APC_Tracked_01_base_F {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 1000;
    };
    
    class APC_Tracked_02_base_F: Tank_F {
        // BM-2T
        // Assuming 1 L/km
        GVAR(fuelCapacity) = 1000;
    };
    
    class APC_Tracked_03_base_F: Tank_F {
        // FV 510
        // Assuming 1 L/km
        GVAR(fuelCapacity) = 660;
    };
    
    class MBT_01_base_F: Tank_F {
        // Merkava IV
        GVAR(fuelCapacity) = 1400;
    };

    class MBT_02_base_F: Tank_F {
        // T100 Black Eagle
        // Assuming T80
        GVAR(fuelCapacity) = 1100;
    };
    
    class MBT_03_base_F: Tank_F {
        // Leopard
        GVAR(fuelCapacity) = 1160;
    };
    
    class MBT_01_arty_base_F : MBT_01_base_F {
        // Assuming similar 2S3
        GVAR(fuelCapacity) = 830;
    };
    
    class MBT_02_arty_base_F : MBT_02_base_F {
        // Assuming similar 2S3
        GVAR(fuelCapacity) = 830;
    };
    
    class Heli_Attack_01_base_F : Helicopter_Base_F {
        // Commanche
    };
    
    class Heli_Attack_02_base_F : Helicopter_Base_F {
        // Mi-48 Kajman
    };
    
    class Heli_Light_01_base_F : Helicopter_Base_H {
        // MH-6
        GVAR(fuelCapacity) = 242;
    };
    
    class Heli_Light_02_base_F : Helicopter_Base_H {
        // Ka-60 Kasatka
        GVAR(fuelCapacity) = 1450;
    };
    
    class Heli_light_03_base_F : Helicopter_Base_F {
        // AW159
        GVAR(fuelCapacity) = 1004;
    };
    
    class Heli_Transport_01_base_F : Helicopter_Base_H  {
        // Ghost Hawk
        // Assuming similar UH60
        GVAR(fuelCapacity) = 1360;
    };
    
    class Heli_Transport_02_base_F : Helicopter_Base_H {
        // AW101
        GVAR(fuelCapacity) = 3222;
    };
    
    class Heli_Transport_03_base_F : Helicopter_Base_H {
        // Chinook 47I
        GVAR(fuelCapacity) = 3914;
    };
    
    class Heli_Transport_04_base_F : Helicopter_Base_H {
        // Mi-290 Taru
        GVAR(fuelCapacity) = 3914;
    };
    
    class Plane_CAS_01_base_F : Plane_Base_F {
        // Assuming similar to A10
        GVAR(fuelCapacity) = 6223;
    }
    
    class Plane_CAS_02_base_F : Plane_Base_F {
        // Yak-130
        GVAR(fuelCapacity) = 2099;
    };
    
    class UAV_01_base_F : Helicopter_Base_F {
        // Darter is electrical
        GVAR(fuelCapacity) = 0;
    };
    
    class UAV : Plane {};
    
    class UAV_02_base_F : UAV {
        // Assuming similar YAHBON-R2
        GVAR(fuelCapacity) = 270;
    };
    
    class UGV_01_base_F : Car_F {
        // Stomper
        GVAR(fuelCapacity) = 100;
    };
    
    class Plane_Fighter_03_base_F : Plane_Base_F {
        // L-159 ALCA
        GVAR(fuelCapacity) = 1914;
    };
    
    // Vanilla fuel vehicles
    class I_Truck_02_fuel_F : Truck_02_base_F {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };
    
    class O_Truck_02_fuel_F : Truck_02_base_F {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };
    
    class B_Truck_01_fuel_F : B_Truck_01_mover_F {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };
    
    class O_Truck_03_fuel_F : Truck_03_base_F {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };
    
    class ReammoBox_F;
    
    class Slingload_01_Base_F : ReammoBox_F {
        class ACE_Actions { 
            class ACE_MainActions {
                displayName = ECSTRING(interaction,MainAction);
                selection = "";
                distance = 10;
                condition = "true";
            }; 
        };
    };
    
    class B_Slingload_01_Fuel_F : Slingload_01_Base_F  {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };
    
    class O_Heli_Transport_04_fuel_F : Heli_Transport_04_base_F  {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };
    
    class Pod_Heli_Transport_04_base_F : StaticWeapon {};
    
    class Land_Pod_Heli_Transport_04_fuel_F : Pod_Heli_Transport_04_base_F {
        transportFuel = 0; //3k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = 10000;
    };

    // Vanilla buildings
    class Land_Fuelstation_Feed_F : House_Small_F {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_fs_feed_F : House_Small_F {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class FuelStation : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_Fuelstation : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_Fuelstation_army : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_Benzina_schnell : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_A_FuelStation_Feed : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_Ind_FuelStation_Feed_EP1 : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    class Land_FuelStation_Feed_PMC : Strategic {
        transportFuel = 0; //50k
        MACRO_REFUEL_ACTIONS
        GVAR(hooks[]) = {{0,0,0}};
        GVAR(fuelCargo) = -1;
    };
    
    /*  // Barrels from rhs?
        BarrelHelper : Misc_thing 100
        BarrelBase : BarrelHelper 100
        Barrels : BarrelBase 400
        Barrel1 : BarrelBase 100
        Barrel2 : BarrelBase 100
        Barrel3 : BarrelBase 100
        Barrel4 : BarrelBase 100
        Barrel5 : BarrelBase 100
        Barrel6 : BarrelBase 100
        Wooden_barrel : BarrelBase 100
        Wooden_barrels : Wooden_barrel 400
        
        // Warfare points
        Base_WarfareBVehicleServicePoint : WarfareBBaseStructure 3000
        Land_StorageBladder_01_F : StorageBladder_base_F 60000
        Land_FlexibleTank_01_F : FlexibleTank_base_F  300
        
        // Mods
        rhsusf_M978A2_usarmy_wd : rhsusf_M977A2_usarmy_wd 10000
        rhsusf_M978A2_CPK_usarmy_wd : rhsusf_M978A2_usarmy_wd 10000
        RHS_Ural_Fuel_MSV_01 : RHS_Ural_Support_MSV_Base_01 10000
        RHS_Ural_Fuel_VDV_01 : RHS_Ural_Fuel_MSV_01 10000
        RHS_Ural_Fuel_VMF_01 : RHS_Ural_Fuel_MSV_01 10000
        RHS_Ural_Fuel_VV_01 : RHS_Ural_Fuel_MSV_01 10000
        LOP_UA_Ural_fuel : RHS_Ural_Fuel_VV_01 10000
    */
    
    // Trucks
    // Src: HEMTT http://www.inetres.com/gp/military/cv/eng/M977.html 583L > 483km
    // Src: https://en.wikipedia.org/wiki/Heavy_Expanded_Mobility_Tactical_Truck 587L > 483km
    // Src: https://en.wikipedia.org/wiki/Kamaz_Typhoon ? > 1200km
    // Src: https://en.wikipedia.org/wiki/Humvee 95L
    // Src: https://en.wikipedia.org/wiki/RG-33 80 gal = 302
    // Src: MTVR http://oshkoshdefense.com/wp-content/uploads/2013/08/MTVR_StndCargo_SS_6-13-11.pdf 295L
    // Src: M1078 http://tarakia.weebly.com/ta-vehicles.html 219L
    // Src: https://en.wikipedia.org/wiki/Ural-4320 360L
    // Src: http://www.automobile-catalog.com/car/2012/1024400/gaz_233011_tigr.html 138L
    // Src: https://en.wikipedia.org/wiki/UAZ-469 78L
    // Src: https://en.wikipedia.org/wiki/GAZ-66 210L
    
    // Tracked IFV
    // Src: https://en.wikipedia.org/wiki/Marder_%28IFV%29 652L > 520km
    // Src: https://en.wikipedia.org/wiki/Tanque_Argentino_Mediano ~250L > 500km (200L additional tank for 400km range boost)
    // Src: https://en.wikipedia.org/wiki/ACEC_Cobra 309L > 600km
    // Src: https://en.wikipedia.org/wiki/Egyptian_Infantry_Fighting_Vehicle 454L > 482km
    // Src: https://en.wikipedia.org/wiki/Lazika 400L > 400-450km
    // Src: https://en.wikipedia.org/wiki/Type_73_Armored_Personnel_Carrier 450L > 300km
    // Src: https://en.wikipedia.org/wiki/BMP-1 462L > 500-600km
    // Src: http://www.inetres.com/gp/military/cv/inf/BMP-1.html 460L > 600km
    // Src: http://www.inetres.com/gp/military/cv/inf/BMP-2.html 460L > 600km
    // Src: http://www.inetres.com/gp/military/cv/inf/M2.html  662L > 483-402km
    // Src: https://en.wikipedia.org/wiki/2T_Stalker ? > 1000km
    // Src: https://en.wikipedia.org/wiki/Namer ? > 500km
    // Src: https://en.wikipedia.org/wiki/Warrior_tracked_armoured_vehicle ? > 660km
    // Src: http://www.globalsecurity.org/military/systems/ground/m113-specs.htm 360L
    // Src: http://afvdb.50megs.com/usa/m2bradley.html 746L
    // Src: https://en.wikipedia.org/wiki/BMD-1 300L
    // Trend: 1-2 L/km
    
    // Wheeled IFV/APC
    // Src: https://en.wikipedia.org/wiki/BTR-60 290L > 500km
    // Src: http://www.inetres.com/gp/military/cv/inf/BTR-70.html 350L > 600km
    // Src: http://www.inetres.com/gp/military/cv/inf/BTR-80.html 300L > 600km
    // Src: https://en.wikipedia.org/wiki/Mowag_Piranha 4x4 200L > 700km
    // Src: https://en.wikipedia.org/wiki/Mowag_Piranha 6x6 200L > 500km
    // Src: https://en.wikipedia.org/wiki/ERC_90_Sagaie 242L > 700km
    // Src: https://en.wikipedia.org/wiki/V%C3%A9hicule_de_l%27Avant_Blind%C3%A9 310L > 1200km
    // Src: https://en.wikipedia.org/wiki/Panhard_M3 165L > 600km
    // Src: https://fr.wikipedia.org/wiki/V%C3%A9hicule_blind%C3%A9_de_combat_d%27infanterie 400L > 750km
    // Src: https://de.wikipedia.org/wiki/Sp%C3%A4hwagen_Fennek 230L > 460-1000km
    // Src: http://www.inetres.com/gp/military/cv/inf/LAV.html 269L > 660km
    // Src: http://www.inetres.com/gp/military/cv/inf/M1126.html 200L > 531km
    // Src: https://en.wikipedia.org/wiki/Patria_AMV ? > 600-850km
    // Src: https://en.wikipedia.org/wiki/Otokar_Arma ? > 700km
    // Trend: 0.3-0.6 L/km
    
    // MBT
    // Src: http://www.inetres.com/gp/military/cv/tank/Leopard2.html 1200L > 550km
    // Src: http://www.inetres.com/gp/military/cv/tank/M1.html 1909L > 479km
    // Src: https://en.wikipedia.org/wiki/T-80 1100L > 335km
    // Src: https://en.wikipedia.org/wiki/T-72 1200L > 490km
    // Trend: 2-4 L/km
    
    // Artillery
    // Src: http://www.inetres.com/gp/military/cv/arty/M109.html 511L > 349km
    // Src: https://en.wikipedia.org/wiki/2S3_Akatsiya 830L > 500km
    
    // Other
    // https://en.wikipedia.org/wiki/ZSU-23-4 515L
    
    // Helicopter
    // Src: http://www.bga-aeroweb.com/Defense/UH-1Y-Venom.html 1172kg / 0.81 kg/L = 1447L
    // Src: http://www.bga-aeroweb.com/Defense/AH-1Z-Viper.html 1296kg / 0.81 kg/L = 1600L
    // Src: http://www.army-technology.com/projects/black_hawk/ 1360L
    // Src: http://www.bga-aeroweb.com/Defense/CH-47-Chinook.html 3914L
    // Src: http://helicopters.axlegeeks.com/l/61/Boeing-AH-64-Apache 375 gal = 1420L
    // Src: https://en.wikipedia.org/wiki/Mil_Mi-8 3700l
    // Src: Google Ka-52 1870L
    // Src: http://www.airforce-technology.com/projects/hind/ 1500kg / 0.81 L/kg = 1851L
    // Src: https://en.wikipedia.org/wiki/MD_Helicopters_MH-6_Little_Bird 242L
    // Src: http://www.globalsecurity.org/military/world/europe/aw159-specs.htm 1004L
    // Src: https://en.wikipedia.org/wiki/AgustaWestland_AW101 3 * 1074L = 3222L
    // Src: http://www.aviastar.org/helicopters_eng/ka-62.php 1450L
    
    // Planes
    // Src: http://www.theaviationzone.com/factsheets/c130j.asp 20820kg / 0.81 kg/L = 25704L
    // Src: http://www.avialogs.com/viewer/avialogs-documentviewer.php?id=3298  p29  1644 gal = 6223L
    // Src: http://www.airforce-technology.com/projects/su25/ 3600L
    // Src: http://www.thaitechnics.com/aircraft/L159.html 1551kg / 0.81 kg/L = 1914L
    // Src: https://en.wikipedia.org/wiki/Yakovlev_Yak-130 1700kg / 0.81 kg/L = 2099L
    // Src: http://www.adcom-systems.com/ENG/UAV/YAHBON-R2/Overview.html 270L
    
    // BWMod
    class BWA3_Puma_base: Tank_F {
        // Assuming 1 L/km
        GVAR(fuelCapacity) = 700;
    };
    
    class BWA3_Leopard_base: Tank_F {
        GVAR(fuelCapacity) = 1160;
    };
    
    // RHS
    class RHS_UH1_Base : Heli_light_03_base_F {
        GVAR(fuelCapacity) = 1447;
    };
    
    class RHS_UH60_Base : Heli_Transport_01_base_F {
        GVAR(fuelCapacity) = 1360;
    };
    
    class RHS_CH_47F_base : Heli_Transport_02_base_F {
        GVAR(fuelCapacity) = 3914;
    };
    
    class RHS_AH1Z_base : Heli_Attack_01_base_F {
        GVAR(fuelCapacity) = 1600;
    };
    class RHS_AH64_base : Heli_Attack_01_base_F {
        GVAR(fuelCapacity) = 1420;
    };
    
    class rhsusf_m1a1tank_base : MBT_01_base_F {
        GVAR(fuelCapacity) = 1909;
    };
    
    class rhsusf_m109tank_base : MBT_01_arty_base_F {
        GVAR(fuelCapacity) = 511;
    };
    
    class rhsusf_hmmwe_base : MRAP_01_base_F {
        GVAR(fuelCapacity) = 95;
    };
    
    class rhsusf_rg33_base : MRAP_01_base_F {
        GVAR(fuelCapacity) = 302;
    };
    
    class rhsusf_fmtv_base : Truck_01_base_F {
        GVAR(fuelCapacity) = 219;
    };
    
    class rhsusf_m113_tank_base : APC_Tracked_02_base_F {
        GVAR(fuelCapacity) = 360;
    };
    
    class RHS_M2A2_Base : APC_Tracked_03_base_F {
        GVAR(fuelCapacity) = 746;
    };
    
    class RHS_A10 : Plane_CAS_01_base_F {
        GVAR(fuelCapacity) = 6223;
    };
    
    class RHS_C130J_Base : Plane_Base_F {
        GVAR(fuelCapacity) = 25704;
    };
    
    class O_Plane_CAS_02_F : Plane_CAS_02_base_F {};
    class RHS_su25_base : O_Plane_CAS_02_F {
        GVAR(fuelCapacity) = 3600;
    };
    
    class RHS_Mi8_base : Heli_Light_02_base_F {
        GVAR(fuelCapacity) = 3700;
    };
    
    class RHS_Ka52_base : Heli_Attack_02_base_F {
        GVAR(fuelCapacity) = 1870;
    };
    
    class RHS_Mi24_base : Heli_Attack_02_base_F {
        GVAR(fuelCapacity) = 1851;
    };
    
    class rhs_bmp3tank_base : Tank_F {
        // Assuming same as BMP1/2
        GVAR(fuelCapacity) = 460;
    };
    
    class a3t72tank_base : Tank_F {
        GVAR(fuelCapacity) = 1200;
    };
    
    class rhs_tank_base : Tank_F {
        GVAR(fuelCapacity) = 1200;
    };
    class rhs_t80b : rhs_tank_base {
        GVAR(fuelCapacity) = 1100;
    };
    
    class RHS_Ural_BaseTurret : Truck_F {
        GVAR(fuelCapacity) = 360;
    };
    
    class rhs_tigr_base : MRAP_02_base_F {
        GVAR(fuelCapacity) = 138;
    };
    
    class RHS_UAZ_Base : Offroad_01_base_f {
        GVAR(fuelCapacity) = 78;
    };
    
    class rhs_zsutank_base : APC_Tracked_02_base_F {
        GVAR(fuelCapacity) = 515;
    };
    
    class rhs_bmp1tank_base : Tank_F {
        GVAR(fuelCapacity) = 460;
    };
    
    class rhs_truck : Truck_F {
        GVAR(fuelCapacity) = 210;
    };
    
    class rhs_btr_base : Wheeled_Apc_F {};
    class rhs_btr60_base : rhs_btr_base {
        GVAR(fuelCapacity) = 290;
    };
    class rhs_btr70_vmf : rhs_btr_base {
        GVAR(fuelCapacity) = 350;
    };
    
    class rhs_btr70_msv : rhs_btr70_vmf {};
    
    class rhs_btr80_msv : rhs_btr70_msv {
        GVAR(fuelCapacity) = 300;
    };
    
    class rhs_a3spruttank_base : Tank_F {
        // BMD4 / 2S25
        GVAR(fuelCapacity) = 400;
    };
    
    class rhs_bmd_base : Tank_F {
        GVAR(fuelCapacity) = 300;
    };
    
    class rhs_2s3tank_base : Tank_F {
        GVAR(fuelCapacity) = 830;
    };
    
    class OTR21_Base : Truck_F {
        // No info about ballistic carrier ;-)
        GVAR(fuelCapacity) = 500;
    };
};
