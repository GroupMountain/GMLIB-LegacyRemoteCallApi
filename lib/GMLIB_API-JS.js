/** LRCA导出接口 */
const GMLIB_API = {
    /** 创建悬浮字 @type {function(FloatPos,string,boolean):number} */
    createFloatingText: ll.imports("GMLIB_API", "createFloatingText"),
    /** 删除悬浮字 @type {function(number):boolean} */
    deleteFloatingText: ll.imports("GMLIB_API", "deleteFloatingText"),
    /** 设置悬浮字文本 @type {function(number,string):boolean} */
    setFloatingTextData: ll.imports("GMLIB_API", "setFloatingTextData"),
    /** 发送悬浮字给玩家 @type {function(number,Player):boolean} */
    sendFloatingTextToPlayer: ll.imports("GMLIB_API", "sendFloatingTextToPlayer"),
    /** 发送悬浮字给所有玩家 @type {function(number):boolean} */
    sendFloatingText: ll.imports("GMLIB_API", "sendFloatingText"),
    /** 删除玩家的悬浮字 @type {function(number,Player):boolean} */
    removeFloatingTextFromPlayer: ll.imports("GMLIB_API", "removeFloatingTextFromPlayer"),
    /** 删除所有玩家悬浮字 @type {function(number):boolean} */
    removeFloatingText: ll.imports("GMLIB_API", "removeFloatingText"),
    /** 更新玩家的悬浮字 @type {function(number,Player):boolean} */
    updateClientFloatingTextData: ll.imports("GMLIB_API", "updateClientFloatingTextData"),
    /** 更新所有玩家的悬浮字 @type {function(number):boolean} */
    updateAllClientsFloatingTextData: ll.imports("GMLIB_API", "updateAllClientsFloatingTextData"),
    /** 获取服务器Mspt @type {function():number} */
    getServerMspt: ll.imports("GMLIB_API", "getServerMspt"),
    /** 获取服务器当前tps @type {function():number} */
    getServerCurrentTps: ll.imports("GMLIB_API", "getServerCurrentTps"),
    /** 获取服务器平均tps @type {function():number} */
    getServerAverageTps: ll.imports("GMLIB_API", "getServerAverageTps"),
    /** 获取存档内所有玩家的uuid @type {function():Array<string>} */
    getAllPlayerUuids: ll.imports("GMLIB_API", "getAllPlayerUuids"),
    /** 获取玩家NBT @type {function(string):NbtCompound} */
    getPlayerNbt: ll.imports("GMLIB_API", "getPlayerNbt"),
    /** 设置玩家NBT @type {function(string,NbtCompound,boolean):boolean} */
    setPlayerNbt: ll.imports("GMLIB_API", "setPlayerNbt"),
    /** 覆盖玩家的特定nbtTags @type {function(string,NbtCompound,Array.<string>):boolean} */
    setPlayerNbtTags: ll.imports("GMLIB_API", "setPlayerNbtTags"),
    /** 删除玩家所有的NBT @type {function(string):boolean} */
    deletePlayerNbt: ll.imports("GMLIB_API", "deletePlayerNbt"),
    /** 使用特定语言翻译资源包文本 @type {function(string,Array.<string>,string):string} */
    resourcePackTranslate: ll.imports("GMLIB_API", "resourcePackTranslate"),
    /** 使用默认语言翻译资源包文本 @type {function(string,Array.<string>):string} */
    resourcePackDefaultTranslate: ll.imports("GMLIB_API", "resourcePackDefaultTranslate"),
    /** 获取资源包默认语言 @type {function():string} */
    getResourcePackI18nLanguage: ll.imports("GMLIB_API", "getResourcePackI18nLanguage"),
    /** 设置资源包默认语言 @type {function(string):void} */
    chooseResourcePackI18nLanguage: ll.imports("GMLIB_API", "chooseResourcePackI18nLanguage"),
    /** 启用教育版内容 @type {function():void} */
    setEducationFeatureEnabled: ll.imports("GMLib_ServerAPI", "setEducationFeatureEnabled"),
    /** 注册Ability命令 @type {function():void} */
    registerAbilityCommand: ll.imports("GMLib_ServerAPI", "registerAbilityCommand"),
    /** 启用Xbox成就 @type {function():void} */
    setEnableAchievement: ll.imports("GMLib_ServerAPI", "setEnableAchievement"),
    /** 信任所有玩家皮肤 @type {function():void} */
    setForceTrustSkins: ll.imports("GMLib_ServerAPI", "setForceTrustSkins"),
    /** 资源包双端共存 @type {function():void} */
    enableCoResourcePack: ll.imports("GMLib_ServerAPI", "enableCoResourcePack"),
    /** 获取存档名字 @type {function():string} */
    getLevelName: ll.imports("GMLib_ServerAPI", "getLevelName"),
    /** 设置存档名字 @type {function(string):boolean} */
    setLevelName: ll.imports("GMLib_ServerAPI", "setLevelName"),
    /** 设置假种子 @type {function(number):void} */
    setFakeSeed: ll.imports("GMLib_ServerAPI", "setFakeSeed"),
    /** 强制生成实体 @type {function(FloatPos,string):Entity} */
    spawnEntity: ll.imports("GMLib_ServerAPI", "spawnEntity"),
    /** 射弹投射物 @type {function(Entity,string,number,number):boolean} */
    shootProjectile: ll.imports("GMLib_ServerAPI", "shootProjectile"),
    /** 投掷实体 @type {function(Entity,Entity,number,number):boolean} */
    throwEntity: ll.imports("GMLib_ServerAPI", "throwEntity"),
    /** 根据玩家对象获取实体对象 @type {function(Player):Entity} */
    PlayerToEntity: ll.imports("GMLib_ServerAPI", "PlayerToEntity"),
    /** 启用错误方块清理 @type {function():void} */
    setUnknownBlockCleaner: ll.imports("GMLib_ModAPI", "setUnknownBlockCleaner"),
    /** 获取实验性功能ID列表 @type {function():Array<number>} */
    getAllExperiments: ll.imports("GMLIB_API", "getAllExperiments"),
    /** 获取实验性功能文本的键名 @type {function(number):string} */
    getExperimentTranslateKey: ll.imports("GMLIB_API", "getExperimentTranslateKey"),
    /** 获取实验性功能启用状态 @type {function(number):boolean} */
    getExperimentEnabled: ll.imports("GMLib_ModAPI", "getExperimentEnabled"),
    /** 设置实验性功能启用状态 @type {function(number,boolean):void} */
    setExperimentEnabled: ll.imports("GMLib_ModAPI", "setExperimentEnabled"),
    /** 注销合成表 @type {function(string):boolean} */
    unregisterRecipe: ll.imports("GMLIB_API", "unregisterRecipe"),
    /** 设置实验性依赖 @type {function(number):void} */
    registerExperimentsRequire: ll.imports("GMLib_ModAPI", "registerExperimentsRequire"),
    /** 注册切石机合成表 @type {function(string,string,number,string,number,number):boolean} */
    registerStoneCutterRecipe: ll.imports("GMLib_ModAPI", "registerStoneCutterRecipe"),
    /** 注册锻造纹饰合成表 @type {function(string,string,string,string):boolean} */
    registerSmithingTrimRecipe: ll.imports("GMLib_ModAPI", "registerSmithingTrimRecipe"),
    /** 注册锻造配方合成表 @type {function(string,string,string,string):boolean} */
    registerSmithingTransformRecipe: ll.imports("GMLib_ModAPI", "registerSmithingTransformRecipe"),
    /** 注册酿造容器表 @type {function(string,string,string,string):boolean} */
    registerBrewingContainerRecipe: ll.imports("GMLib_ModAPI", "registerBrewingContainerRecipe"),
    /** 注册酿造混合表 @type {function(string,string,string,string):boolean} */
    registerBrewingMixRecipe: ll.imports("GMLib_ModAPI", "registerBrewingMixRecipe"),
    /** 注册熔炼合成表 @type {function(string,string,string,Array.<string>):boolean} */
    registerFurnaceRecipe: ll.imports("GMLib_ModAPI", "registerFurnaceRecipe"),
    /** 注册有序合成表 @type {function(string,Array.<string>,Array.<string>,string,number,string)} */
    registerShapedRecipe: ll.imports("GMLib_ModAPI", "registerShapedRecipe"),
    /** 注册无序合成表 @type {function(string,Array.<string>,Array.<string>,string,number,string)} */
    registerShapelessRecipe: ll.imports("GMLib_ModAPI", "registerShapelessRecipe"),
    /** 注册有序合成表 @type {function(string,Array.<string>,Array.<string>,string,number,string)} */
    registerCustomShapedRecipe: ll.imports("GMLIB_API", "registerCustomShapedRecipe"),
    /** 注册无序合成表 @type {function(string,Array.<string>,Array.<string>,string,number,string)} */
    registerCustomShapelessRecipe: ll.imports("GMLIB_API", "registerCustomShapelessRecipe"),
    /** 检测LRCA版本是否大于或等于此版本 @type {function(number,number,number):boolean} */
    isVersionMatched: ll.imports("GMLIB_API", "isVersionMatched"),
    /** 获取LRCA版本 @type {function():string} */
    getVersion_LRCA: ll.imports("GMLIB_API", "getVersion_LRCA"),
    /** 获取GMLIB版本 @type {function():string} */
    getVersion_GMLIB: ll.imports("GMLIB_API", "getVersion_GMLIB"),
    /** 获取玩家坐标 @type {function(string):IntPos} */
    getPlayerPosition: ll.imports("GMLIB_API", "getPlayerPosition"),
    /** 设置玩家坐标 @type {function(string,IntPos):boolean} */
    setPlayerPosition: ll.imports("GMLIB_API", "setPlayerPosition"),
    /** 玩家是否存在于计分板 @type {function(string,string):boolean} */
    playerHasScore: ll.imports("GMLIB_API", "playerHasScore"),
    /** 获取玩家在计分板中的值 @type {function(string,string):number} */
    getPlayerScore: ll.imports("GMLIB_API", "getPlayerScore"),
    /** 增加玩家在计分板中的值 @type {function(string,string,number):boolean} */
    addPlayerScore: ll.imports("GMLIB_API", "addPlayerScore"),
    /** 减少玩家在计分板中的值 @type {function(string,string,number):boolean} */
    reducePlayerScore: ll.imports("GMLIB_API", "reducePlayerScore"),
    /** 设置玩家在计分板中的值 @type {function(string,string,number):boolean} */
    setPlayerScore: ll.imports("GMLIB_API", "setPlayerScore"),
    /** 重置玩家在计分板中的数据 @type {function(string,string):boolean} */
    resetPlayerScore: ll.imports("GMLIB_API", "resetPlayerScore"),
    /** 重置玩家所有的计分板数据 @type {function(string):boolean} */
    resetPlayerScores: ll.imports("GMLIB_API", "resetPlayerScores"),
    /** 实体是否存在于计分板中 @type {function(string,string):boolean} */
    entityHasScore: ll.imports("GMLIB_API", "entityHasScore"),
    /** 获取实体在计分板中的值 @type {function(string,string):number} */
    getEntityScore: ll.imports("GMLIB_API", "getEntityScore"),
    /** 增加实体在计分板中的值 @type {function(string,string,number):boolean} */
    addEntityScore: ll.imports("GMLIB_API", "addEntityScore"),
    /** 减少实体在计分板中的值 @type {function(string,string,number):boolean} */
    reduceEntityScore: ll.imports("GMLIB_API", "reduceEntityScore"),
    /** 设置实体在计分板中的值 @type {function(string,string,number):boolean} */
    setEntityScore: ll.imports("GMLIB_API", "setEntityScore"),
    /** 重置实体在计分板中的数据 @type {function(string,string):boolean} */
    resetEntityScore: ll.imports("GMLIB_API", "resetEntityScore"),
    /** 重置实体所有的计分板数据 @type {function(string):boolean} */
    resetEntityScores: ll.imports("GMLIB_API", "resetEntityScores"),
    /** 字符串是否存在于计分板 @type {function(string,string):boolean} */
    fakePlayerHasScore: ll.imports("GMLIB_API", "fakePlayerHasScore"),
    /** 获取字符串在计分板中的值 @type {function(string,string):number} */
    getFakePlayerScore: ll.imports("GMLIB_API", "getFakePlayerScore"),
    /** 增加字符串在计分板中的值 @type {function(string,string,number):boolean} */
    addFakePlayerScore: ll.imports("GMLIB_API", "addFakePlayerScore"),
    /** 减少字符串在计分板中的值 @type {function(string,string,number):boolean} */
    reduceFakePlayerScore: ll.imports("GMLIB_API", "reduceFakePlayerScore"),
    /** 设置字符串在计分板中的值 @type {function(string,string,number):boolean} */
    setFakePlayerScore: ll.imports("GMLIB_API", "setFakePlayerScore"),
    /** 重置字符串在计分板中的数据 @type {function(string,string):boolean} */
    resetFakePlayerScore: ll.imports("GMLIB_API", "resetFakePlayerScore"),
    /** 重置字符串所有的计分板数据 @type {function(string):boolean} */
    resetFakePlayerScores: ll.imports("GMLIB_API", "resetFakePlayerScores"),
    /** 创建计分板 @type {function(string):boolean} */
    addObjective: ll.imports("GMLIB_API", "addObjective"),
    /** 创建带有显示名称的计分板 @type {function(string,string):boolean} */
    addObjectiveWithDisplayName: ll.imports("GMLIB_API", "addObjectiveWithDisplayName"),
    /** 获取计分板显示名字 @type {function(string):string} */
    getDisplayName: ll.imports("GMLIB_API", "getDisplayName"),
    /** 设置计分板显示名字 @type {function(string,string):boolean} */
    setDisplayName: ll.imports("GMLIB_API", "setDisplayName"),
    /** 删除计分板 @type {function(string):boolean} */
    removeObjective: ll.imports("GMLIB_API", "removeObjective"),
    /** 设置计分板显示 @type {function(string,"list"|"sidebar"|"belowname",0|1):void} */
    setDisplayObjective: ll.imports("GMLIB_API", "setDisplayObjective"),
    /** 清除计分板显示 @type {function("list"|"sidebar"|"belowname"):void} */
    clearDisplayObjective: ll.imports("GMLIB_API", "clearDisplayObjective"),
    /** 获取所有计分板 @type {function():Array.<string>} */
    getAllObjectives: ll.imports("GMLIB_API", "getAllObjectives"),
    /** 获取所有跟踪目标 @type {function():Array.<{"Type":"Player","Uuid":string}|{"Type":"FakePlayer","Name":string}|{"Type":"Entity","UniqueId":string}>} */
    getAllTrackedTargets: ll.imports("GMLIB_API", "getAllTrackedTargets"),
    /** 获取所有跟踪玩家 @type {function():Array.<string>} */
    getAllScoreboardPlayers: ll.imports("GMLIB_API", "getAllScoreboardPlayers"),
    /** 获取所有跟踪字符串 @type {function():Array.<string>} */
    getAllScoreboardFakePlayers: ll.imports("GMLIB_API", "getAllScoreboardFakePlayers"),
    /** 获取所有跟踪实体 @type {function():Array.<string>} */
    getAllScoreboardEntities: ll.imports("GMLIB_API", "getAllScoreboardEntities"),
    /** 根据uuid获取玩家对象 @type {function(string):Player} */
    getPlayerFromUuid: ll.imports("GMLIB_API", "getPlayerFromUuid"),
    /** 根据UniqueId获取玩家对象 @type {function(string):Player} */
    getPlayerFromUniqueId: ll.imports("GMLIB_API", "getPlayerFromUniqueId"),
    /** 根据UniqueId获取实体对象 @type {function(string):Entity} */
    getEntityFromUniqueId: ll.imports("GMLIB_API", "getEntityFromUniqueId"),
    /** 获取世界出生点 @type {function():IntPos} */
    getWorldSpawn: ll.imports("GMLIB_API", "getWorldSpawn"),
    /** 设置世界出生点 @type {function(IntPos):void} */
    setWorldSpawn: ll.imports("GMLIB_API", "setWorldSpawn"),
    /** 获取玩家重生点 @type {function(Player):IntPos} */
    getPlayerSpawnPoint: ll.imports("GMLIB_API", "getPlayerSpawnPoint"),
    /** 设置玩家重生点 @type {function(Player,IntPos):void} */
    setPlayerSpawnPoint: ll.imports("GMLIB_API", "setPlayerSpawnPoint"),
    /** 清除玩家重生点 @type {function(Player):void} */
    clearPlayerSpawnPoint: ll.imports("GMLIB_API", "clearPlayerSpawnPoint"),
    /** 设置资源包路径 @type {function(string):void} */
    setCustomPackPath: ll.imports("GMLIB_API", "setCustomPackPath"),
    /** 获取支持的语言标识符 @type {function():Array.<string>} */
    getSupportedLanguages: ll.imports("GMLIB_API", "getSupportedLanguages"),
    /** 加载语言翻译 @type {function(string,string):void} */
    loadLanguage: ll.imports("GMLIB_API", "loadLanguage"),
    /** 更新或创建语言文件 @type {function(string,string,string):void} */
    updateOrCreateLanguageFile: ll.imports("GMLIB_API", "updateOrCreateLanguageFile"),
    /** 加载语言文件目录 @type {function(string):void} */
    loadLanguagePath: ll.imports("GMLIB_API", "loadLanguagePath"),
    /** 合并json @type {function(string,string):string} */
    mergePatchJson: ll.imports("GMLIB_API", "mergePatchJson"),
    /** 根据uuid获取xuid @type {function(string):string} */
    getXuidByUuid: ll.imports("GMLIB_API", "getXuidByUuid"),
    /** 根据uuid获取名字 @type {function(string):string} */
    getNameByUuid: ll.imports("GMLIB_API", "getNameByUuid"),
    /** 根据xuid获取uuid @type {function(string):string} */
    getUuidByXuid: ll.imports("GMLIB_API", "getUuidByXuid"),
    /** 根据xuid获取名字 @type {function(string):string} */
    getNameByXuid: ll.imports("GMLIB_API", "getNameByXuid"),
    /** 根据名字获取xuid @type {function(string):string} */
    getXuidByName: ll.imports("GMLIB_API", "getXuidByName"),
    /** 根据名字获取uuid @type {function(string):string} */
    getUuidByName: ll.imports("GMLIB_API", "getUuidByName"),
    /** 获取所有已记录的玩家信息 @type {function():Array.<{"Uuid":string,"Xuid":string,"Name":string}>} */
    getAllPlayerInfo: ll.imports("GMLIB_API", "getAllPlayerInfo"),
    /** 获取方块RuntimeId @type {function(string,number):number} */
    getBlockRuntimeId: ll.imports("GMLIB_API", "getBlockRuntimeId"),
    /** 添加虚假列表玩家 @type {function(string,string):boolean} */
    addFakeList: ll.imports("GMLIB_API", "addFakeList"),
    /** 删除虚假列表玩家 @type {function(string):boolean} */
    removeFakeList: ll.imports("GMLIB_API", "removeFakeList"),
    /** 删除所有虚假列表玩家 @type {function():void} */
    removeAllFakeLists: ll.imports("GMLIB_API", "removeAllFakeList"),
    /** 启用I18n修复 @type {function():void} */
    setFixI18nEnabled: ll.imports("GMLib_ModAPI", "setFixI18nEnabled"),
    /** 获取方块翻译键名 @type {function(Block):string} */
    getBlockTranslateKey: ll.imports("GMLIB_API", "getBlockTranslateKey"),
    /** 获取物品翻译键名 @type {function(Item):string} */
    getItemTranslateKey: ll.imports("GMLIB_API", "getItemTranslateKey"),
    /** 获取实体翻译键名 @type {function(Entity):string} */
    getEntityTranslateKey: ll.imports("GMLIB_API", "getEntityTranslateKey"),
    /** 从文件中读取NBT @type {function(string,boolean):NbtCompound} */
    readNbtFromFile: ll.imports("GMLIB_API", "readNbtFromFile"),
    /** 保存NBT至文件 @type {function(string,NbtCompound,boolean):void} */
    saveNbtToFile: ll.imports("GMLIB_API", "saveNbtToFile"),
    /** 获取方块硬度 @type {function(Block):number} */
    getBlockDestroySpeed: ll.imports("GMLIB_API", "getBlockDestroySpeed"),
    /** 获取物品挖掘方块速度 @type {function(Item,Block):number} */
    getDestroyBlockSpeed: ll.imports("GMLIB_API", "getDestroyBlockSpeed"),
    /** 使玩家挖掘方块 @type {function(Block,IntPos,Player):void} */
    playerDestroyBlock: ll.imports("GMLIB_API", "playerDestroyBlock"),
    /** 物品冒险模式下是否可以挖掘方块 @type {function(Item,Block):boolean} */
    itemCanDestroyBlock: ll.imports("GMLIB_API", "itemCanDestroyBlock"),
    /** 物品是否能破坏方块 @type {function(Item):boolean} */
    itemCanDestroyInCreative: ll.imports("GMLIB_API", "itemCanDestroyInCreative"),
    /** 物品是否可以采集方块 @type {function(Item,Block):boolean} */
    itemCanDestroySpecial: ll.imports("GMLIB_API", "itemCanDestroySpecial"),
    /** @type {function(Block):boolean} */
    blockCanDropWithAnyTool: ll.imports("GMLIB_API", "blockCanDropWithAnyTool"),
    /** @type {function(Block,Player,IntPos):boolean} */
    blockPlayerWillDestroy: ll.imports("GMLIB_API", "blockPlayerWillDestroy"),
    /** 使玩家攻击实体 @type {function(Entity,Player):boolean} */
    playerAttack: ll.imports("GMLIB_API", "playerAttack"),
    /** @type {function(Player,Entity):void} */
    playerPullInEntity: ll.imports("GMLIB_API", "playerPullInEntity"),
    /** 根据命令空间获取翻译键名 @type {function(string):string} */
    getBlockTranslateKeyFromName: ll.imports("GMLIB_API", "getBlockTranslateKeyFromName"),
    /** 获取存档种子 @type {function():string} */
    getLevelSeed: ll.imports("GMLib_ServerAPI", "getLevelSeed"),
    /** 获取方块亮度 @type {function(string,number):number} */
    getBlockLightEmission: ll.imports("GMLIB_API", "getBlockLightEmission"),
    /** 获取游戏规则列表 @type {function():Array.<{Name:string,Value:string,Type:"Bool"|"Float"|"Int"}>} */
    getGameRules: ll.imports("GMLIB_API", "getGameRules"),
    /** 给物品添加附魔 @type {function(Item,string,number,boolean):boolean} */
    applyEnchant: ll.imports("GMLIB_API", "applyEnchant"),
    /** 删除物品所有附魔 @type {function(Item):void} */
    removeEnchants: ll.imports("GMLIB_API", "removeEnchants"),
    /** 判断物品是否拥有附魔 @type {function(Item,string):boolean} */
    hasEnchant: ll.imports("GMLIB_API", "hasEnchant"),
    /** 获取附魔等级 @type {function(Item,string):number} */
    getEnchantLevel: ll.imports("GMLIB_API", "getEnchantLevel"),
    /** 获取附魔名字 @type {function(string,number):number} */
    getEnchantNameAndLevel: ll.imports("GMLIB_API", "getEnchantNameAndLevel"),
    /** 通过ID获取附魔命名空间ID @type {function(number):string} */
    getEnchantTypeNameFromId: ll.imports("GMLIB_API", "getEnchantTypeNameFromId"),
    /** 获取最大玩家数 @type {function():number} */
    getMaxPlayers: ll.imports("GMLib_ServerAPI", "getMaxPlayers"),
    /** 丢出玩家背包内物品 @type {function(Player,Item,boolean):boolean} */
    dropPlayerItem: ll.imports("GMLIB_API", "dropPlayerItem"),
    /** 获取玩家的RuntimeId @type {function(Player):number} */
    getPlayerRuntimeId: ll.imports("GMLIB_API", "getPlayerRuntimeId"),
    /** 获取实体的RuntimeId @type {function(Entity):number} */
    getEntityRuntimeId: ll.imports("GMLIB_API", "getEntityRuntimeId"),
    /** 获取实体命名 @type {function(Entity):string} */
    getEntityNameTag: ll.imports("GMLIB_API", "getEntityNameTag"),
    /** 物品是否有不可破坏标签 @type {function(Item):boolean} */
    ItemisUnbreakable: ll.imports("GMLIB_API", "ItemisUnbreakable"),
    /** 设置物品不可破坏标签 @type {function(Item,boolean):void} */
    setItemUnbreakable: ll.imports("GMLIB_API", "setItemUnbreakable"),
    /** 物品是否死亡不会掉落 @type {function(Item):boolean} */
    getItemShouldKeepOnDeath: ll.imports("GMLIB_API", "getItemShouldKeepOnDeath"),
    /** 设置物品死亡不掉落 @type {function(Item,boolean):void} */
    setItemShouldKeepOnDeath: ll.imports("GMLIB_API", "setItemShouldKeepOnDeath"),
    /** 获取物品锁定模式 @type {function(Item):number} */
    getItemLockMode: ll.imports("GMLIB_API", "getItemLockMode"),
    /** 设置物品锁定模式 @type {function(Item,number):void} */
    setItemLockMode: ll.imports("GMLIB_API", "setItemLockMode"),
    /** 获取物品惩罚等级 @type {function(Item):number} */
    getItemRepairCost: ll.imports("GMLIB_API", "getItemRepairCost"),
    /** 设置物品惩罚等级 @type {function(Item,number):void} */
    setItemRepairCost: ll.imports("GMLIB_API", "setItemRepairCost"),
    /** 获取物品冒险模式下可破坏的方块 @type {function(Item):Array.<string>} */
    getItemCanDestroy: ll.imports("GMLIB_API", "getItemCanDestroy"),
    /** 设置物品冒险模式下可破坏的方块 @type {function(Item,Array.<string>):void} */
    setItemCanDestroy: ll.imports("GMLIB_API", "setItemCanDestroy"),
    /** 获取物品冒险模式下能放置在什么方块上 @type {function(Item):Array.<string>} */
    getItemCanPlaceOn: ll.imports("GMLIB_API", "getItemCanPlaceOn"),
    /** 设置物品冒险模式下能放置在什么方块上 @type {function(Item,Array.<string>):void} */
    setItemCanPlaceOn: ll.imports("GMLIB_API", "setItemCanPlaceOn"),
    /** 获取玩家饥饿值 @type {function(Player):number} */
    getPlayerHungry: ll.imports("GMLIB_API", "getPlayerHungry"),
    /** 获取玩家盔甲覆盖百分比 @type {function(Player):number} */
    getPlayerArmorCoverPercentage: ll.imports("GMLIB_API", "getPlayerArmorCoverPercentage"),
    /** 获取玩家盔甲值 @type {function(Player):number} */
    getPlayerArmorValue: ll.imports("GMLIB_API", "getPlayerArmorValue"),
    /** 获取实体主人的UniqueID @type {function(Entity):Entity} */
    getEntityOwnerUniqueId: ll.imports("GMLIB_API", "getEntityOwnerUniqueId"),
    /** 获取物品分类名称 @type {function(Item):string} */
    getItemCategoryName: ll.imports("GMLIB_API", "getItemCategoryName"),
    /** 获取物品的命名 @type {function(Item):string} */
    getItemCustomName: ll.imports("GMLIB_API", "getItemCustomName"),
    /** 获取物品BUFF效果名称 @type {function(Item):string} */
    getItemEffecName: ll.imports("GMLIB_API", "getItemEffecName"),
    /** 物品是否为食物 @type {function(Item):boolean} */
    itemIsFood: ll.imports("GMLIB_API", "itemIsFood"),
    /** 设置玩家UI栏物品 @type {function(Player,number,Item):void} */
    setPlayerUIItem: ll.imports("GMLIB_API", "setPlayerUIItem"),
    /** 获取玩家UI栏物品 @type {function(Player,number):Item} */
    getPlayerUIItem: ll.imports("GMLIB_API", "getPlayerUIItem"),
    /** 更新玩家容器物品 @type {function(Player,number,number,Item):void} */
    sendInventorySlotPacket: ll.imports("GMLIB_API", "sendInventorySlotPacket"),
    /** 获取容器类型 @type {function(Container):string} */
    getContainerType: ll.imports("GMLIB_API", "getContainerType"),
    /** 玩家是否拥有NBT @type {function(string):boolean} */
    hasPlayerNbt: ll.imports("GMLIB_API", "hasPlayerNbt"),
    /** 获取物品最大堆叠数量 @type {function(Item):number} */
    getItemMaxCount: ll.imports("GMLIB_API", "getItemMaxCount"),
    /** 实体包含在某族里 @type {function(Entity,string):boolean} */
    entityHasFamily: ll.imports("GMLIB_API", "entityHasFamily"),
    /** 获取玩家破坏方块所需时间 @type {function(Player,Block):number} */
    getPlayerDestroyBlockProgress: ll.imports("GMLIB_API", "getPlayerDestroyBlockProgress"),
    /** 获取实体的buff是否显示 @type {function(Player,number):boolean} */
    getEntityEffectVisible: ll.imports("GMLIB_API", "getEntityEffectVisible"),
    /** 获取实体的buff持续时间 @type {function(Player,number):number} */
    getEntityEffectDuration: ll.imports("GMLIB_API", "getEntityEffectDuration"),
    /** 获取实体的buff简单模式下的持续时间 @type {function(Player,number):number} */
    getEntityEffectDurationEasy: ll.imports("GMLIB_API", "getEntityEffectDuration"),
    /** 获取实体的buff困难模式下的持续时间 @type {function(Player,number):number} */
    getEntityEffectDurationHard: ll.imports("GMLIB_API", "getEntityEffectDurationHard"),
    /** 获取实体的buff普通模式下的持续时间 @type {function(Player,number):number} */
    getEntityEffectDurationNormal: ll.imports("GMLIB_API", "getEntityEffectDurationNormal"),
    /** 获取实体的buff效果等级 @type {function(Entity,number):number} */
    getEntityEffectAmplifier: ll.imports("GMLIB_API", "getEntityEffectAmplifier"),
    /** 获取实体的buff是否为信标给予 @type {function(Entity,number):boolean} */
    getEntityEffectAmbient: ll.imports("GMLIB_API", "getEntityEffectAmbient"),
    /** 实体是否拥有buff效果 @type {function(Entity,number):boolean} */
    entityHasEffect: ll.imports("GMLIB_API", "entityHasEffect"),
    /** 获取实体所有buff效果 @type {function(Entity):Array.<number>} */
    getEntityAllEffects: ll.imports("GMLIB_API", "getEntityAllEffects"),
    /** 获取游戏难度 @type {function():number} */
    getGameDifficulty: ll.imports("GMLIB_API", "getGameDifficulty"),
    /** 设置游戏难度 @type {function(difficulty):void} */
    setGameDifficulty: ll.imports("GMLIB_API", "setGameDifficulty"),
    /** 获取默认游戏模式 @type {function():number} */
    getDefaultGameMode: ll.imports("GMLIB_API", "getDefaultGameMode"),
    /** 设置默认游戏模式 @type {function(mode):void} */
    setDefaultGameMode: ll.imports("GMLIB_API", "setDefaultGameMode"),
    /** 实体是否为某类型 @type {function(Entity, number):boolean} */
    entityIsType: ll.imports("GMLIB_API", "entityIsType"),
    /** 实体是包含某类型 @type {function(Entity, number):boolean} */
    entityHasType: ll.imports("GMLIB_API", "entityHasType"),
    /** 获取实体类型ID @type {function(Entity):number} */
    getEntityTypeId: ll.imports("GMLIB_API", "getEntityTypeId"),
    /** 获取实体类型ID @type {function(Entity):number} */
    getPlayerProtocolVersion: ll.imports("GMLIB_API", "getPlayerProtocolVersion"),
};

/** LRCA的二进制流数据包导出接口 */
const GMLIB_BinaryStream_API = {
    /** 创建二进制流数据包 @type {function():number} */
    create: ll.imports("GMLIB_BinaryStream_API", "create"),
    /** 拷贝二进制流数据包 @type {function(number):number} */
    copy: ll.imports("GMLIB_BinaryStream_API", "copy"),
    /** 发送二进制流数据包 @type {function(number,player):void} */
    sendTo: ll.imports("GMLIB_BinaryStream_API", "sendTo"),
    /** 销毁二进制流数据包 @type {function(number):void} */
    destroy: ll.imports("GMLIB_BinaryStream_API", "destroy"),
    /** 重置二进制流数据包 @type {function(number):void} */
    reset: ll.imports("GMLIB_BinaryStream_API", "reset"),
    /** 写入二进制流数据包头部 @type {function(number, number):void} */
    writePacketHeader: ll.imports("GMLIB_BinaryStream_API", "writePacketHeader"),
    /** 写入UUID @type {function(number, string):void} */
    writeUuid: ll.imports("GMLIB_BinaryStream_API", "writeUuid"),
    /** 写入物品 @type {function(number, Item):void} */
    writeItem: ll.imports("GMLIB_BinaryStream_API", "writeItem"),
    /** 写入NBT @type {function(NbtCompound, Item):void} */
    writeCompoundTag: ll.imports("GMLIB_BinaryStream_API", "writeCompoundTag"),
    /** 写入字符串 @type {function(number, string):void} */
    writeString: ll.imports("GMLIB_BinaryStream_API", "writeString"),
    /** 写入布尔值 @type {function(number, boolean):void} */
    writeBool: ll.imports("GMLIB_BinaryStream_API", "writeBool"),
    /** 写入字节 @type {function(number, number):void} */
    writeByte: ll.imports("GMLIB_BinaryStream_API", "writeByte"),
    /** 写入双精度浮点数 @type {function(number, number):void} */
    writeDouble: ll.imports("GMLIB_BinaryStream_API", "writeDouble"),
    /** 写入浮点数 @type {function(number, number):void} */
    writeFloat: ll.imports("GMLIB_BinaryStream_API", "writeFloat"),
    /** @type {function(number, number):void} */
    writeSignedBigEndianInt: ll.imports("GMLIB_BinaryStream_API", "writeSignedBigEndianInt"),
    /** @type {function(number, number):void} */
    writeSignedInt: ll.imports("GMLIB_BinaryStream_API", "writeSignedInt"),
    /** @type {function(number, number):void} */
    writeSignedInt64: ll.imports("GMLIB_BinaryStream_API", "writeSignedInt64"),
    /** @type {function(number, number):void} */
    writeSignedShort: ll.imports("GMLIB_BinaryStream_API", "writeSignedShort"),
    /** @type {function(number, number):void} */
    writeUnsignedChar: ll.imports("GMLIB_BinaryStream_API", "writeUnsignedChar"),
    /** @type {function(number, number):void} */
    writeUnsignedInt: ll.imports("GMLIB_BinaryStream_API", "writeUnsignedInt"),
    /** @type {function(number, number):void} */
    writeUnsignedInt64: ll.imports("GMLIB_BinaryStream_API", "writeUnsignedInt64"),
    /** @type {function(number, number):void} */
    writeUnsignedShort: ll.imports("GMLIB_BinaryStream_API", "writeUnsignedShort"),
    /** @type {function(number, number):void} */
    writeUnsignedVarInt: ll.imports("GMLIB_BinaryStream_API", "writeUnsignedVarInt"),
    /** @type {function(number, number):void} */
    writeUnsignedVarInt64: ll.imports("GMLIB_BinaryStream_API", "writeUnsignedVarInt64"),
    /** @type {function(number, number):void} */
    writeVarInt: ll.imports("GMLIB_BinaryStream_API", "writeVarInt"),
    /** @type {function(number, number):void} */
    writeVarInt64: ll.imports("GMLIB_BinaryStream_API", "writeVarInt64"),
};

/** 静态悬浮字类列表 @type {Map<number,StaticFloatingText>} */
const mStaticFloatingTextMap = new Map();
/** 动态悬浮字类列表 @type {Map<number,DynamicFloatingText>} */
const mDynamicFloatingTextMap = new Map();

/** 静态悬浮字类 */
class StaticFloatingText {
    /**
     * 构造函数
     * @param {FloatPos} pos 要生成的坐标
     * @param {string} text 悬浮字文本
     * @param {boolean?} [papi=true] 是否使用PAPI变量
     */
    constructor(pos, text, papi = true) {
        this.mPosition = pos;
        this.mText = text;
        this.mPlaceholderAPI = papi;
        this.mRuntimeId = GMLIB_API.createFloatingText(this.mPosition, this.mText, this.mPlaceholderAPI);
        mStaticFloatingTextMap.set(this.mRuntimeId, this);
    }

    /**
     * 发送悬浮字给玩家
     * @param {Player} player 玩家对象
     * @returns {boolean} 是否成功发送
     */
    sendToClient(player) {
        return GMLIB_API.sendFloatingTextToPlayer(this.mRuntimeId, player);
    }

    /**
     * 发送悬浮字给所有玩家
     * @returns {boolean} 是否成功发送
     */
    sendToClients() {
        return GMLIB_API.sendFloatingText(this.mRuntimeId);
    }

    /**
     * 删除玩家的悬浮字
     * @param {Player} player 玩家对象
     * @returns {boolean} 是否成功删除
     */
    removeFromClient(player) {
        return GMLIB_API.removeFloatingTextFromPlayer(this.mRuntimeId, player);
    }

    /**
     * 删除所有玩家悬浮字
     * @returns {boolean} 是否成功删除
     */
    removeFromClients() {
        return GMLIB_API.removeFloatingText(this.mRuntimeId);
    }

    /**
     * 更新玩家的悬浮字
     * @param {Player} player 玩家对象
     * @returns {boolean} 是否成功更新
     */
    updateClient(player) {
        return GMLIB_API.updateClientFloatingTextData(this.mRuntimeId, player);
    }

    /**
     * 更新所有玩家的悬浮字
     * @returns {boolean} 是否成功更新
     */
    updateClients() {
        return GMLIB_API.updateAllClientsFloatingTextData(this.mRuntimeId);
    }

    /**
     * 获取悬浮字的RuntimeId
     * @returns {number} 悬浮字的RuntimeId
     */
    getRuntimeId() {
        return this.mRuntimeId;
    }

    /**
     * 获取悬浮字显示的文本
     * @returns {IntPos} 悬浮字显示的文本
     */
    getText() {
        return this.mText;
    }

    /**
     * 设置悬浮字显示的文本
     * @param {string} newText 要显示的文本
     */
    setText(newText) {
        this.mText = newText;
    }

    /**
     * 更新所有玩家的悬浮字
     * @returns {boolean} 是否成功更新
     */
    update() {
        GMLIB_API.setFloatingTextData(this.mRuntimeId, this.mText);
        return this.updateClients();
    }

    /**
     * 更新悬浮字文本
     * @param {string} newText 要显示的文本
     * @returns {boolean} 是否成功更新
     */
    updateText(newText) {
        this.setText(newText);
        return this.update();
    }

    /**
     * 获取悬浮字的坐标
     * @returns {FlatPos} 悬浮字的坐标
     */
    getPos() {
        return this.mPosition;
    }

    /**
     * 删除悬浮字
     * @returns {boolean} 是否成功删除
     */
    destroy() {
        mStaticFloatingTextMap.delete(this.mRuntimeId);
        return GMLIB_API.deleteFloatingText(this.mRuntimeId);
    }

    /**
     * 根据RuntimeId获取静态悬浮字
     * @param {number} runtimeId 悬浮字的RuntimeId
     * @returns {StaticFloatingText|null} 悬浮字对象
     */
    static getFloatingText(runtimeId) {
        if (mStaticFloatingTextMap.has(runtimeId)) {
            return mStaticFloatingTextMap.get(runtimeId);
        }
        return null;
    }

    /**
     * 获取所有静态悬浮字
     * @returns {Array<StaticFloatingText>} 所有悬浮字对象
     */
    static getAllFloatingTexts() {
        let result = [];
        mStaticFloatingTextMap.forEach((ft) => {
            result.push(ft);
        });
        return result;
    }
}

/** 动态悬浮字类 */
class DynamicFloatingText extends StaticFloatingText {
    /**
     * 创建一个动态悬浮字
     * @param {FlatPos} pos 悬浮字的坐标
     * @param {string} text 悬浮字显示的文本
     * @param {number} [updateRate=1] 更新频率(秒)
     * @param {boolean} [papi=true] 是否使用PAPI变量
     */
    constructor(pos, text, updateRate = 1, papi = true) {
        super(pos, text, papi);
        this.mRuntimeId = GMLIB_API.createFloatingText(this.mPosition, this.mText, this.mPlaceholderAPI);
        this.mUpdateRate = updateRate;
        this.mTaskId = null;
        mDynamicFloatingTextMap.set(this.mRuntimeId, this);
        this.startUpdate();
    }

    /**
     * 获取悬浮字更新频率
     * @returns {number} 更新频率，单位为秒
     */
    getUpdateRate() {
        return this.mUpdateRate;
    }

    /**
     * 设置悬浮字更新频率
     * @param {number} updateRate 更新频率，单位为秒
     */
    setUpdateRate(updateRate = 1) {
        this.stopUpdate();
        this.mUpdateRate = updateRate;
        this.startUpdate();
    }

    /**
     * 开始更新悬浮字
     * @returns {boolean} 是否成功开始更新
     */
    startUpdate() {
        if (this.mTaskId == null) {
            this.mTaskId = setInterval(() => {
                this.update();
            }, this.mUpdateRate * 1000);
            return true;
        }
        return false;
    }

    /**
     * 停止更新悬浮字
     * @returns {boolean} 是否成功停止更新
     */
    stopUpdate() {
        if (this.mTaskId) {
            clearInterval(this.mTaskId);
            this.mTaskId = null;
            return true;
        }
        return false;
    }

    /**
     * 删除悬浮字
     * @returns {boolean} 是否成功删除
     */
    destroy() {
        mDynamicFloatingTextMap.delete(this.mRuntimeId);
        return GMLIB_API.deleteFloatingText(this.mRuntimeId);
    }

    /**
     * 根据runtimeId获取动态悬浮字对象
     * @param {number} runtimeId 悬浮字的RuntimeId
     * @returns {DynamicFloatingText} 悬浮字对象
     */
    static getFloatingText(runtimeId) {
        if (mDynamicFloatingTextMap.has(runtimeId)) {
            return mDynamicFloatingTextMap.get(runtimeId);
        }
        return null;
    }

    /**
     * 获取所有动态悬浮字
     * @returns {Array<DynamicFloatingText>} 所有悬浮字对象
     */
    static getAllFloatingTexts() {
        let result = [];
        mDynamicFloatingTextMap.forEach((ft) => {
            result.push(ft);
        });
        return result;
    }
}

/** 基础游戏API类 */
class Minecraft {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 获取服务器平均tps
     * @returns {number} 服务器平均tps
     */
    static getServerAverageTps() {
        return GMLIB_API.getServerAverageTps();
    }

    /**
     * 获取服务器当前tps
     * @returns {number} 服务器当前tps
     */
    static getServerCurrentTps() {
        return GMLIB_API.getServerCurrentTps();
    }

    /**
     * 获取服务器mspt
     * @returns {number} 服务器mspt
     */
    static getServerMspt() {
        return GMLIB_API.getServerMspt();
    }

    /**
     * 获取所有玩家uuid
     * @returns {Array<string>} 所有玩家uuid
     */
    static getAllPlayerUuids() {
        return GMLIB_API.getAllPlayerUuids();
    }

    /**
     * 获取玩家NBT
     * @param {string} uuid 玩家的uuid
     * @returns {NbtCompound} 玩家的NBT
     */
    static getPlayerNbt(uuid) {
        return GMLIB_API.getPlayerNbt(uuid);
    }

    /**
     * 写入玩家NBT
     * @param {string} uuid 玩家的uuid
     * @param {NbtCompound} nbt 要写入的NBT
     * @param {boolean?} [forceCreate=true] 不存在是否创建
     * @returns {boolean} 是否成功写入NBT
     */
    static setPlayerNbt(uuid, nbt, forceCreate = true) {
        return GMLIB_API.setPlayerNbt(uuid, nbt, forceCreate);
    }

    /**
     * 覆盖玩家NBT的特定Tags
     * @param {string} uuid 玩家的uuid
     * @param {NbtCompound} nbt 要写入的NBT
     * @param {Array.<string>} tags 要覆盖的NBT标签
     * @returns {boolean} 是否成功写入NBT
     */
    static setPlayerNbtTags(uuid, nbt, tags) {
        return GMLIB_API.setPlayerNbtTags(uuid, nbt, tags);
    }

    /**
     * 删除玩家NBT
     * @param {string} uuid 玩家的uuid
     * @returns {boolean} 是否成功删除NBT
     */
    static deletePlayerNbt(uuid) {
        return GMLIB_API.deletePlayerNbt(uuid);
    }

    /**
     * 获取玩家坐标
     * @param {string} uuid 玩家的uuid
     * @returns {IntPos|null} 玩家坐标
     */
    static getPlayerPosition(uuid) {
        let pos = GMLIB_API.getPlayerPosition(uuid);
        if (pos.dimid == -1) {
            return null;
        }
        return pos;
    }

    /**
     * 设置玩家坐标
     * @param {string} uuid 玩家的uuid
     * @param {IntPos} pos 要设置的坐标
     * @returns {boolean} 是否成功设置玩家坐标
     */
    static setPlayerPosition(uuid, pos) {
        return GMLIB_API.setPlayerPosition(uuid, pos);
    }

    /**
     * 获取世界出生点
     * @returns {IntPos} 世界坐标
     */
    static getWorldSpawn() {
        return GMLIB_API.getWorldSpawn();
    }

    /**
     * 设置世界出生点
     * @param {IntPos} pos 要设置的出生点坐标
     */
    static setWorldSpawn(pos) {
        GMLIB_API.setWorldSpawn(pos);
    }

    /**
     * 启用教育版内容
     */
    static setEducationFeatureEnabled() {
        GMLIB_API.setEducationFeatureEnabled();
    }

    /**
     * 注册Ability命令
     */
    static registerAbilityCommand() {
        GMLIB_API.registerAbilityCommand();
    }

    /**
     * 启用Xbox成就
     */
    static setEnableAchievement() {
        GMLIB_API.setEnableAchievement();
    }

    /**
     * 信任所有玩家皮肤
     */
    static setForceTrustSkins() {
        GMLIB_API.setForceTrustSkins();
    }

    /**
     * 启用资源包双端共存
     */
    static enableCoResourcePack() {
        GMLIB_API.enableCoResourcePack();
    }

    /**
     * 获取存档名称
     * @returns {string} 世界名称
     */
    static getWorldName() {
        return GMLIB_API.getLevelName();
    }

    /**
     * 设置存档名称
     * @param {string} name 世界名称
     * @returns {boolean} 是否成功设置世界名称
     */
    static setWorldName(name) {
        return GMLIB_API.setLevelName(name);
    }

    /**
     * 设置假种子
     * @param {Number?} [seed=114514] seed 要设置的假种子
     */
    static setFakeSeed(seed = 114514) {
        GMLIB_API.setFakeSeed(seed);
    }

    /**
     * 启用错误方块清理
     */
    static setUnknownBlockCleaner() {
        GMLIB_API.setUnknownBlockCleaner();
    }

    /**
     * 强制生成实体
     * @param {FloatPos} pos 要生成的坐标
     * @param {string} name 实体命名空间ID
     * @returns {boolean} 是否成功生成实体
     */
    static spawnEntity(pos, name) {
        return GMLIB_API.spawnEntity(pos, name);
    }

    /**
     * 射弹投射物
     * @param {Entity} entity 实体对象
     * @param {string} proj 投射物命名空间ID
     * @param {number} [speed=2] 速度 
     * @param {number} [offset=3] 偏移量 
     * @returns {boolean} 是否成功投射投射物
     */
    static shootProjectile(entity, proj, speed = 2, offset = 3) {
        return GMLIB_API.shootProjectile(entity, proj, speed, offset);
    }

    /**
     * 投掷实体
     * @param {Entity} entity 实体对象
     * @param {Entity} proj 被投掷的实体
     * @param {number} [speed=2] 速度 
     * @param {number} [offset=3] 偏移量 
     * @returns {boolean} 是否成功投射投射物
     */
    static throwEntity(entity, proj, speed = 2, offset = 3) {
        return GMLIB_API.throwEntity(entity, proj, speed = 2, offset = 3);
    }

    /**
     * 获取服务器使用的语言
     * @returns {string} 服务器使用的语言
     */
    static getServerLanguage() {
        return I18nAPI.getCurrentLanguage();
    }

    /**
     * 设置服务器使用的语言
     * @param {string} language 语言标识符
     * @returns {boolean} 是否成功设置服务器使用的语言
     */
    static setServerLanguage(language) {
        return I18nAPI.chooseLanguage(language);
    }

    /**
     * 设置资源包路径
     * @param {string} path 资源包路径
     * @returns {boolean} 是否成功设置资源包路径
     */
    static setCustomPackPath(path) {
        GMLIB_API.setCustomPackPath(path);
    }

    /**
     * 翻译资源包文本
     * @param {string} key 键名
     * @param {Array.<string>} params 翻译参数
     * @returns {string} 翻译后的文本
     */
    static resourcePackTranslate(key, params = []) {
        return I18nAPI.get(key, params);
    }

    /**
     * 根据uuid获取玩家对象
     * @param {string} uuid 玩家的uuid
     * @returns {Player} 玩家对象
     */
    static getPlayerFromUuid(uuid) {
        return GMLIB_API.getPlayerFromUuid(uuid);
    }

    /**
     * 根据UniqueId获取玩家对象
     * @param {string|number} uniqueId 玩家的UniqueId
     * @returns {Player} 玩家对象
     */
    static getPlayerFromUniqueId(uniqueId) {
        return GMLIB_API.getPlayerFromUniqueId(uniqueId.toString());
    }

    /**
     * 根据UniqueId获取实体对象
     * @param {string|number} uniqueId 实体的UniqueId
     * @returns {Entity} 实体对象
     */
    static getEntityFromUniqueId(uniqueId) {
        return GMLIB_API.getEntityFromUniqueId(uniqueId.toString());
    }

    /**
     * 获取方块runtimeId
     * @param {string} block 方块命名空间ID
     * @param {number} [legacyData=0] 方块的特殊值
     * @returns {number} 方块的runtimeId
     */
    static getBlockRuntimeId(block, legacyData = 0) {
        return GMLIB_API.getBlockRuntimeId(block, legacyData);
    }

    /**
     * 添加虚假列表玩家
     * @param {string} name 虚假玩家的名字
     * @param {string} xuid 虚假玩家的xuid
     * @returns {boolean} 是否成功添加
     */
    static addFakeList(name, xuid) {
        return GMLIB_API.addFakeList(name, xuid);
    }

    /**
     * 移除虚假列表玩家
     * @param {string} nameOrXuid 虚假的玩家名字或xuid
     * @returns {boolean} 是否成功移除
     */
    static removeFakeList(nameOrXuid) {
        return GMLIB_API.removeFakeList(nameOrXuid);
    }

    /**
     * 移除所有虚假列表玩家
     * @returns {boolean} 是否成功移除
     */
    static removeAllFakeLists() {
        return GMLIB_API.removeAllFakeLists();
    }

    /**
     * 启用I18n修复
     */
    static setFixI18nEnabled() {
        GMLIB_API.setFixI18nEnabled();
    }

    /**
     * 保存NBT至文件
     * @param {string} path 文件路径
     * @param {NbtCompound} nbt NBT对象
     * @param {boolean} [isBinary=true] 是否为写入为二进制文件
     * @returns 
     */
    static saveNbtToFile(path, nbt, isBinary = true) {
        return GMLIB_API.saveNbtToFile(path, nbt, isBinary);
    }

    /**
     * 从文件读取NBT
     * @param {string} path 文件路径
     * @param {boolean} [isBinary=true] 是否为读取为二进制文件
     * @returns {NbtCompound} NBT对象
     */
    static readNbtFromFile(path, isBinary = true) {
        return GMLIB_API.readNbtFromFile(path, isBinary);
    }

    /**
     * 根据命名空间ID获取翻译键名
     * @param {string} name 方块的命名空间ID
     * @returns {string} 方块的翻译键名
     */
    static getBlockTranslateKeyFromName(name) {
        return GMLIB_API.getBlockTranslateKeyFromName(name);
    }

    /**
     * 获取存档种子
     */
    static getLevelSeed() {
        return GMLIB_API.getLevelSeed();
    }

    /**
     * 获取方块亮度
     * @param {string} block 方块的命名空间ID
     * @param {number} [legacyData=0] 方块的特殊值
     * @returns {number} 方块的亮度(-1为不存在)
     */
    static getBlockLightEmission(block, legacyData = 0) {
        return GMLIB_API.getBlockLightEmission(block, legacyData);
    }

    /**
     * 获取游戏规则列表
     * @returns {Array.<{Name:string,Value:boolean|number}>}
     */
    static getGameRules() {
        const gameRules = GMLIB_API.getGameRules();
        let result = [];
        for (const gameRule of gameRules) {
            if (gameRule.Type === "Bool") {
                result.push({
                    "Name": gameRule.Name,
                    "Value": gameRule.Value == "1" ? true : false
                });
            } else {
                result.push({
                    "Name": gameRule.Name,
                    "Value": JSON.parse(gameRule.Value)
                });
            }
        }
        return result;
    }

    /**
     * 获取附魔名字和等级
     * @param {string} typeName 附魔的命名空间ID
     * @param {number} level 附魔等级
     * @returns {string} 文本
     */
    static getEnchantNameAndLevel(typeName, level) {
        return GMLIB_API.getEnchantNameAndLevel(typeName, level);
    }

    /**
     * 通过附魔ID获取附魔命名空间ID
     * @param {number} id 附魔ID
     * @returns {string?} 附魔的命名空间ID
     */
    static getEnchantTypeNameFromId(id) {
        const result = GMLIB_API.getEnchantTypeNameFromId(id);
        return result === "" ? null : result;
    }

    /**
     * 获取最大玩家数量
     * @returns {number} 最大玩家数量
     */
    static getMaxPlayers() {
        return GMLIB_API.getMaxPlayers();
    }

    /**
     * 玩家是否拥有NBT
     * @param {string} uuid 玩家的uuid
     * @returns 玩家是否拥有NBT
     */
    static hasPlayerNbt(uuid) {
        return GMLIB_API.hasPlayerNbt(uuid);
    }

    /**
     * 获取游戏难度
     * @returns {-1|0|1|2|3} 游戏难度
     */
    static getGameDifficulty() {
        return GMLIB_API.getGameDifficulty();
    }

    /**
     * 设置游戏难度
     * @param {0|1|2|3} difficulty 游戏难度
     */
    static setGameDifficulty(difficulty) {
        GMLIB_API.setGameDifficulty(difficulty);
    }

    /**
     * 获取默认游戏模式
     * @returns {-1|0|1|2|5|6} 游戏模式
    */
    static getDefaultGameMode() {
        return GMLIB_API.getDefaultGameMode();
    }
    /**
     * 设置默认游戏模式
     * @param {0|1|2|3} gameMode 游戏模式
     */
    static setDefaultGameMode(gameMode) {
        GMLIB_API.setDefaultGameMode(gameMode);
    }
}

/** 合成表类 */
class Recipes {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 注销合成表
     * @param {string} recipeId 合成表唯一标识符
     * @returns {boolean} 是否注销成功
     */
    static unregisterRecipe(recipeId) {
        return GMLIB_API.unregisterRecipe(recipeId);
    }

    /**
     * 注册切石机合成表
     * @param {string} recipeId 合成表唯一标识符
     * @param {string} inputName 输入物品
     * @param {number} inputAux 输入物品额外数据
     * @param {string} outputName 合成结果
     * @param {number} outputAux 合成结果额外数据
     * @param {number} outputCount 合成结果数量
     * @returns {boolean} 是否注册成功
     */
    static registerStoneCutterRecipe(recipeId, inputName, inputAux, outputName, outputAux, outputCount) {
        return GMLIB_API.registerStoneCutterRecipe(recipeId, inputName, inputAux, outputName, outputAux, outputCount);
    }

    /**
     * 注册锻造纹饰合成表
     * @param {string} recipeId 合成表唯一标识符
     * @param {string} template 锻造模板
     * @param {string} base 基础材料
     * @param {string} addition 纹饰材料
     * @returns {boolean} 是否注册成功
     */
    static registerSmithingTrimRecipe(recipeId, template, base, addition) {
        return GMLIB_API.registerSmithingTrimRecipe(recipeId, template, base, addition);
    }

    /**
     * 注册锻造配方合成表
     * @param {string} recipeId 合成表唯一标识符
     * @param {string} template 锻造模板
     * @param {string} base 基础物品
     * @param {string} addition 升级材料
     * @param {string} result 合成结果
     * @returns {boolean} 是否注册成功
     */
    static registerSmithingTransformRecipe(recipeId, template, base, addition, result) {
        return GMLIB_API.registerSmithingTransformRecipe(recipeId, template, base, addition, result);
    }

    /**
     * 注册酿造容器表
     * @param {string} recipeId 合成表唯一标识符
     * @param {string} input 输入物品
     * @param {string} output 合成结果
     * @param {string} reagent 酿造物品
     * @returns {boolean} 是否注册成功
     */
    static registerBrewingContainerRecipe(recipeId, input, output, reagent) {
        return GMLIB_API.registerBrewingContainerRecipe(recipeId, input, output, reagent);
    }

    /**
     * 注册酿造混合表
     * @param {string} recipeId 合成表唯一标识
     * @param {string} input 输入物品（必须是原版药水物品id）
     * @param {string} output 合成结果（必须是原版药水物品id）
     * @param {string} reagent 酿造物品
     * @returns {boolean} 是否注册成功
     */
    static registerBrewingMixRecipe(recipeId, input, output, reagent) {
        return GMLIB_API.registerBrewingMixRecipe(recipeId, input, output, reagent);
    }

    /**
     * 注册熔炼合成表
     * @param {string} recipeId 合成表唯一标识
     * @param {string} input 输入材料
     * @param {string} output 合成结果
     * @param {Array.<string>} [tags=["furnace"]] 材料的标签数组
     * @returns {boolean} 是否注册成功
     */
    static registerFurnaceRecipe(recipeId, input, output, tags = ["furnace"]) {
        return GMLIB_API.registerFurnaceRecipe(recipeId, input, output, tags);
    }

    /**
     * 注册有序合成表
     * @param {string} recipeId 合成表唯一标识
     * @param {[string,string,string]} shape 合成表摆放方式，数组元素为字符串
     * @param {Array.<string>} ingredients 材料数组
     * @param {string} result 合成结果
     * @param {string} [count=1] 合成结果的数量
     * @param {string} [unlock=AlwaysUnlocked] 解锁条件(也可以填物品命名空间ID)
     * @returns {boolean} 是否注册成功
     */
    static registerShapedRecipe(recipeId, shape, ingredients, result, count = 1, unlock = "AlwaysUnlocked") {
        return GMLIB_API.registerShapedRecipe(recipeId, shape, ingredients, result, count, unlock);
    }

    /**
     * 注册自定义有序合成表
     * @param {string} recipeId 合成表唯一标识
     * @param {[string,string,string]} shape 合成表摆放方式，数组元素为字符串
     * @param {Array.<string>} ingredients 材料数组
     * @param {Item} result 合成结果
     * @returns {boolean} 是否注册成功
     */
    static registerCustomShapedRecipe(recipeId, shape, ingredients, result) {
        return GMLIB_API.registerCustomShapedRecipe(recipeId, shape, ingredients, result);
    }

    /**
     * 注册无序合成表
     * @param {string} recipeId 合成表唯一标识
     * @param {Array.<string>} ingredients 合成材料
     * @param {string} result 合成结果
     * @param {number} [count=1] 合成数量
     * @param {string} [unlock=AlwaysUnlocked] 解锁条件(也可以填物品命名空间ID)
     * @returns  {boolean} 是否注册成功
     */
    static registerShapelessRecipe(recipeId, ingredients, result, count = 1, unlock = "AlwaysUnlocked") {
        return GMLIB_API.registerShapelessRecipe(recipeId, ingredients, result, count, unlock);
    }

    /**
     * 注册自定义无序合成表
     * @param {string} recipeId 合成表唯一标识
     * @param {Array.<string>} ingredients 合成材料
     * @param {Item} result 合成结果
     * @returns  {boolean} 是否注册成功
     */
    static registerCustomShapelessRecipe(recipeId, ingredients, result) {
        return GMLIB_API.registerCustomShapelessRecipe(recipeId, ingredients, result);
    }
}

/** 实验性功能类 */
class Experiments {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 获取所有实验的id
     * @returns {Array.<number>} 所有实验的id
     */
    static getAllExperimentIds() {
        return GMLIB_API.getAllExperiments();
    }
    /**
     * 获取实验性功能文本的键名
     * @param {number} id 实验性功能的id
     * @returns {string} 实验性功能文本的键名
     */
    static getExperimentTranslateKey(id) {
        return GMLIB_API.getExperimentTranslateKey(id);
    }

    /**
     * 获取实验性功能启用状态
     * @param {number} id 实验性功能的id
     * @returns {boolean} 实验性功能是否开启
     */
    static getExperimentEnabled(id) {
        return GMLIB_API.getExperimentEnabled(id);
    }

    /**
     * 设置实验性功能启用状态
     * @param {number} id 实验性功能的id
     * @param {boolean?} [value=true] 实验性功能是否开启
     */
    static setExperimentEnabled(id, value = true) {
        GMLIB_API.setExperimentEnabled(id, value);
    }

    /**
     * 设置实验性依赖
     * @param {number} id 实验性功能的id
     */
    static registerExperimentsRequire(id) {
        GMLIB_API.registerExperimentsRequire(id);
    }
}

/** 版本类 */
class Version {
    /**
     * 创建版本对象
     * @param {number} major 主版本号
     * @param {number} minor 次版本号
     * @param {number} patch 修订版本号
     * @constructor
     */
    constructor(major, minor, patch) {
        this.mMajor = major;
        this.mMinor = minor;
        this.mPatch = patch;
    }

    /**
     * 转换成字符串
     * @param {boolean} [prefix=true] 是否添加前缀"v"
     * @returns {string} 版本字符串
     */
    toString(prefix = true) {
        let result = `${this.mMajor}.${this.mMinor}.${this.mPatch}`;
        if (prefix) {
            result = "v" + result;
        }
        return result;
    }

    /**
     * 转换成数组
     * @returns {[number,number,number]} 版本数组
     */
    toArray() {
        return [this.mMajor, this.mMinor, this.mPatch];
    }

    /**
     * 转换成数字
     * @returns {number} 版本数字
     */
    valueOf() {
        return 100000000 * this.mMajor + 10000 * this.mMinor + this.mPatch;
    }

    /**
     * 从字符串中创建版本对象
     * @param {string} version 版本号字符串
     * @returns {Version|null} 版本对象
     */
    static fromString(string) {
        if (typeof string === "string" || string instanceof String) {
            let pattern = /^v?\d+\.\d+\.\d+$/;
            if (pattern.test(string)) {
                let regex = /\d+/g;
                let numbers = string.match(regex);
                let array = numbers.slice(0, 3).map(Number);
                return new Version(array[0], array[1], array[2]);
            }
        }
        return null;
    }

    /**
     * 从数组中创建版本对象
     * @param {[number,number,number]} array 版本号数组
     * @returns {Version|null} 版本对象
     */
    static fromArray(array) {
        if (Array.isArray(array) && array.length == 3) {
            let isNumber = array.every(element => typeof element == "number");
            if (isNumber) {
                return new Version(array[0], array[1], array[2]);
            }
        }
        return null;
    }

    /**
     * 检测LRCA版本是否大于或等于此版本
     * @param {Version} version 版本对象
     * @returns {boolean} 检测结果
     */
    static isPluginVersionMatched(version) {
        return GMLIB_API.isVersionMatched(version.mMajor, version.mMinor, version.mPatch);
    }

    /**
     * 获取LRCA版本号对象
     * @returns {Version} 版本对象
     */
    static getLrcaVersion() {
        return Version.fromString(GMLIB_API.getVersion_LRCA());
    }

    /**
     * 获取GMLIB版本号对象
     * @returns {Version} 版本对象
     */
    static getGmlibVersion() {
        return Version.fromString(GMLIB_API.getVersion_GMLIB());
    }
}

/** 计分板类 */
class Scoreboard {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 获取所有跟踪实体
     * @returns {Array.<string>} 所有跟踪实体
     */
    static getAllTrackedEntities() {
        return GMLIB_API.getAllScoreboardEntities();
    }

    /**
     * 获取所有跟踪玩家
     * @returns {Array.<string>} 所有跟踪玩家
     */
    static getAllTrackedPlayers() {
        return GMLIB_API.getAllScoreboardPlayers();
    }

    /**
     * 获取所有跟踪字符串
     * @returns {Array.<string>} 所有跟踪字符串
     */
    static getAllTrackedFakePlayers() {
        return GMLIB_API.getAllScoreboardFakePlayers();
    }

    /**
     * 获取所有跟踪目标
     * @returns {Array.<{"Type":"Player","Uuid":string}|{"Type":"FakePlayer","Name":string}|{"Type":"Entity","UniqueId":string}>} 所有跟踪目标
     */
    static getAllTrackedTargets() {
        return GMLIB_API.getAllTrackedTargets();
    }

    /**
     * 创建计分板
     * @param {string} name 计分板名字
     * @param {string?} [displayName=""] 显示名称 
     * @returns {boolean} 是否创建成功
     */
    static addObjective(name, displayName = "") {
        if (displayName == "") {
            return GMLIB_API.addObjective(name);
        }
        return GMLIB_API.addObjectiveWithDisplayName(name, displayName);
    }

    /**
     * 移除计分板
     * @param {string} name 计分板名字
     * @returns {boolean} 是否移除成功
     */
    static removeObjective(name) {
        return GMLIB_API.removeObjective(name);
    }

    /**
     * 获取所有计分板名字
     * @returns {Array.<string>} 所有计分板名字列表
     */
    static getAllObjectives() {
        return GMLIB_API.getAllObjectives();
    }

    /**
     * 获取计分板显示名称
     * @param {string} objective 计分板名字
     * @returns {string} 计分板显示名称
     */
    static getDisplayName(objective) {
        return GMLIB_API.getDisplayName(objective);
    }

    /**
     * 设置计分板显示名称
     * @param {string} objective 计分板名字
     * @param {string} displayName 显示名称
     * @returns {boolean} 是否设置成功
     */
    static setDisplayName(objective, displayName) {
        return GMLIB_API.setDisplayName(objective, displayName);
    }

    /**
     * 设置计分板显示
     * @param {string} objective 计分板名称
     * @param {"list" | "sidebar" | "belowname"} slot 显示位置
     * @param {0|1?} [order=0] 排序方式
     */
    static setDisplay(objective, slot, order = 0) {
        GMLIB_API.setDisplayObjective(objective, slot, order);
    }

    /**
     * 清除计分板显示
     * @param {"list" | "sidebar" | "belowname"} slot 清除的显示位置
     */
    static clearDisplay(slot) {
        GMLIB_API.clearDisplayObjective(slot);
    }

    /**
     * 获取玩家在计分板中的值
     * @param {string} uuid 玩家的uuid
     * @param {string} objective 计分板名称
     * @returns {number?} 计分板值
     */
    static getPlayerScore(uuid, objective) {
        if (GMLIB_API.playerHasScore(uuid, objective)) {
            return GMLIB_API.getPlayerScore(uuid, objective);
        }
        return null;
    }

    /**
     * 增加玩家在计分板中的值
     * @param {string} uuid 玩家的uuid
     * @param {string} objective 计分板名称
     * @param {number} value 增加的值
     * @returns {boolean} 是否增加成功
     */
    static addPlayerScore(uuid, objective, value) {
        return GMLIB_API.addPlayerScore(uuid, objective, value);
    }

    /**
     * 减少玩家在计分板中的值
     * @param {string} uuid 玩家的uuid
     * @param {string} objective 计分板名称
     * @param {number} value 减少的值
     * @returns {boolean} 是否减少成功
     */
    static reducePlayerScore(uuid, objective, value) {
        return GMLIB_API.reducePlayerScore(uuid, objective, value);
    }

    /**
     * 设置玩家在计分板中的值
     * @param {string} uuid 玩家的uuid
     * @param {string} objective 计分板名称
     * @param {number} value 设置的值
     * @returns {boolean} 是否设置成功
     */
    static setPlayerScore(uuid, objective, value) {
        return GMLIB_API.setPlayerScore(uuid, objective, value);
    }

    /**
     * 重置玩家在计分板中的数据
     * @param {string} uuid 玩家的uuid
     * @param {string} objective 计分板名称
     * @returns {boolean} 是否重置成功
     */
    static resetPlayerScore(uuid, objective) {
        return GMLIB_API.resetPlayerScore(uuid, objective);
    }

    /**
     * 重置玩家所有的计分板数据
     * @param {string} uuid 玩家的uuid
     * @returns {boolean} 是否重置成功
     */
    static resetPlayerScores(uuid) {
        return GMLIB_API.resetPlayerScores(uuid);
    }

    /**
     * 获取字符串在计分板中的值
     * @param {string} name 字符串名称
     * @param {string} objective 计分板名称
     * @returns {number?} 计分板值
     */
    static getFakePlayerScore(name, objective) {
        if (GMLIB_API.fakePlayerHasScore(name, objective)) {
            return GMLIB_API.getFakePlayerScore(name, objective);
        }
        return null;
    }

    /**
     * 增加字符串在计分板中的值
     * @param {string} name 字符串名称
     * @param {string} objective 计分板名称
     * @param {number} value 增加的值
     * @returns {boolean} 是否增加成功
     */
    static addFakePlayerScore(name, objective, value) {
        return GMLIB_API.addFakePlayerScore(name, objective, value);
    }

    /**
     * 减少字符串在计分板中的值
     * @param {string} name 字符串名称
     * @param {string} objective 计分板名称
     * @param {number} value 减少的值
     * @returns {boolean} 是否减少成功
     */
    static reduceFakePlayerScore(name, objective, value) {
        return GMLIB_API.reduceFakePlayerScore(name, objective, value);
    }

    /**
     * 设置字符串在计分板中的值
     * @param {string} name 字符串名称
     * @param {string} objective 计分板名称
     * @param {number} value 设置的值
     * @returns {boolean} 是否设置成功
     */
    static setFakePlayerScore(name, objective, value) {
        return GMLIB_API.setFakePlayerScore(name, objective, value);
    }

    /**
     * 重置字符串在计分板中的数据
     * @param {string} name 字符串名称
     * @param {string} objective 计分板名称
     * @returns {boolean} 是否重置成功
     */
    static resetFakePlayerScore(name, objective) {
        return GMLIB_API.resetFakePlayerScore(name, objective);
    }

    /**
     * 重置字符串所有的计分板数据
     * @param {string} name 字符串
     * @returns {boolean} 是否重置成功
     */
    static resetFakePlayerScores(name) {
        return GMLIB_API.resetFakePlayerScores(name);
    }

    /**
     * 获取实体在计分板中的值
     * @param {string} uniqueId 实体的uniqueId
     * @param {string} objective 计分板名称
     * @returns {number?} 计分板值
     */
    static getEntityScore(uniqueId, objective) {
        if (GMLIB_API.entityHasScore(uniqueId, objective)) {
            return GMLIB_API.getEntityScore(uniqueId, objective);
        }
        return null;
    }

    /**
     * 增加实体在计分板中的值
     * @param {string} uniqueId 实体的uniqueId
     * @param {string} objective 计分板名称
     * @param {number} value 增加的值
     * @returns {boolean} 是否增加成功
     */
    static addEntityScore(uniqueId, objective, value) {
        return GMLIB_API.addEntityScore(uniqueId, objective, value);
    }

    /**
     * 减少实体在计分板中的值
     * @param {string} uniqueId 实体的uniqueId
     * @param {string} objective 计分板名称
     * @param {number} value 减少的值
     * @returns {boolean} 是否减少成功
     */
    static reduceEntityScore(uniqueId, objective, value) {
        return GMLIB_API.reduceEntityScore(uniqueId, objective, value);
    }

    /**
     * 设置实体在计分板中的值
     * @param {string} uniqueId 实体的uniqueId
     * @param {string} objective 计分板名称
     * @param {number} value 设置的值
     * @returns {boolean} 是否设置成功
     */
    static setEntityScore(uniqueId, objective, value) {
        return GMLIB_API.setEntityScore(uniqueId, objective, value);
    }

    /**
     * 重置实体的计分板数据
     * @param {string} uniqueId 实体的uniqueId
     * @param {string} objective 计分板名称
     * @returns {boolean} 是否重置成功
     */
    static resetEntityScore(uniqueId, objective) {
        return GMLIB_API.resetEntityScore(uniqueId, objective);
    }

    /**
     * 重置实体的所有计分板数据
     * @param {string} uniqueId 实体的uniqueId
     * @returns {boolean} 是否重置成功
     */
    static resetEntityScores(uniqueId) {
        return GMLIB_API.resetEntityScores(uniqueId);
    }
}

/** 仿LSE的JsonConfigFile类 */
class JsonConfig {
    /**
     * 创建或打开一个 Json 配置文件
     * @param {string} path Json文件的路径
     * @param {object} defultValue 默认数据
     * @constructor
     */
    constructor(path, defultValue = {}) {
        this.mData = defultValue;
        this.mPath = path;
        this.init();
    }

    /**
     * 初始化Json文件
     */
    init() {
        if (File.exists(this.mPath)) {
            let existDataStr = File.readFrom(this.mPath);
            existDataStr = existDataStr.replace(/\/\/.*|\/\*[^]*?\*\//g, "");
            try {
                let result = GMLIB_API.mergePatchJson(JSON.stringify(this.mData), existDataStr);
                this.mData = JSON.parse(result);
            } catch {
                let newPath = this.mPath + "_old";
                File.rename(this.mPath, newPath);
            }
        }
        this.save();
    }

    /**
     * 保存Json文件
     * @param {number} [format=4] 缩进长度
     */
    save(format = 4) {
        let dataStr = JSON.stringify(this.mData, null, format);
        File.writeTo(this.mPath, dataStr);
    }

    /**
     * 获取所有数据
     * @returns {object} 数据
     */
    getData() {
        return this.mData;
    }

    /**
     * 读取数据
     * @param {string} key 键名
     * @param {any?} [defultValue=undefined] 不存在时返回值
     * @returns {any} 数据
     */
    get(key, defultValue = undefined) {
        let result = this.getData()[key];
        if (!result && defultValue != undefined) {
            this.set(key, defultValue);
            return defultValue;
        }
        return result;
    }

    /**
     * 设置数据
     * @param {string} key 键名
     * @param {any} value 值
     */
    set(key, value) {
        this.getData()[key] = value;
        this.save();
    }

    /**
     * 删除数据
     * @param {string} key 键名
     */
    delete(key) {
        delete this.getData()[key];
        this.save();
    }
}

/**
 * JSON版语言类
 */
class JsonLanguage extends JsonConfig {
    /**
     * 创建或打开一个 Json 语言文件
     * @param {string} path Json文件的路径
     * @param {object} defultValue 默认值
     * @constructor
     */
    constructor(path, defultValue = {}) {
        super(path, defultValue);
    }

    /**
     * 翻译键名
     * @param {string} key 键名
     * @param {Array.<string>} data 翻译参数
     * @returns {string} 翻译结果
     */
    translate(key, data = []) {
        let result = this.get(key);
        if (result == null) {
            return key;
        }
        data.forEach((val, index) => {
            let old = `{${index + 1}}`;
            result = result.split(old).join(val?.toString() ?? "");
        });
        return result;
    }
}

/** JSON版I18n类 */
class JsonI18n {
    /**
     * 加载翻译数据目录
     * @param {string} path 目录
     * @param {string?} [localLangCode="en_US"]  默认语言
     */
    constructor(path, localLangCode = "en_US") {
        if (!path.endsWith("/") && !path.endsWith("\\")) {
            path = path + "/";
        }
        this.mPath = path;
        this.mLangCode = localLangCode;
        this.mAllLanguages = {};
        this.mDefaultLangCode = "en_US";
        this.loadAllLanguages();
    }

    /**
     * 加载所有语言
     */
    loadAllLanguages() {
        let exist_list = File.getFilesList(this.mPath);
        exist_list.forEach((name) => {
            let code = name.replace(".json", "");
            let path = this.mPath + name;
            let language = new JsonLanguage(path);
            this.mAllLanguages[code] = language;
        });
    }

    /**
     * 加载语言
     * @param {string} langCode 语言标识符
     * @param {any?} [defaultData={}] 默认数据
     */
    loadLanguage(langCode, defaultData = {}) {
        let langPath = this.mPath;
        langPath = langPath + langCode + ".json";
        let language = new JsonLanguage(langPath, defaultData);
        this.mAllLanguages[langCode] = language;
    }

    /**
     * 设置语言
     * @param {string} langCode 语言标识符
     */
    chooseLanguage(langCode) {
        this.mLangCode = langCode;
    }

    /**
     * 设置默认语言
     * @param {string} langCode 语言标识符
     */
    setDefaultLanguage(langCode) {
        this.mDefaultLangCode = langCode;
    }

    /**
     * 翻译键名
     * @param {string} key 键名
     * @param {Array.<string>?} [data=[]] 翻译参数
     * @param {string?} [langCode=this.mLangCode] 翻译语言
     * @returns {string} 翻译结果
     */
    translate(key, data = [], langCode = this.mLangCode) {
        let language = this.mAllLanguages[langCode];
        let result = language.translate(key, data);
        if (result == key) {
            let language = this.mAllLanguages[this.mDefaultLangCode];
            if (language) {
                result = language.translate(key, data);
            }
        }
        return result;
    }
};

/** I18nAPI类 */
class I18nAPI {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 获取键翻译
     * @param {string} key 键名
     * @param {Array.<string>?} params 翻译参数
     * @param {string?} langCode 要翻译的语言
     * @returns {string} 翻译结果
     */
    static get(key, params = [], langCode = undefined) {
        const data = params.map(item => item?.toString() || "");
        if (langCode) {
            return GMLIB_API.resourcePackTranslate(key, data, langCode);
        }
        return GMLIB_API.resourcePackDefaultTranslate(key, data);
    }

    /**
     * 获取键翻译
     * @param {string} key 键名
     * @param {Array.<string>?} params 翻译参数
     * @param {string?} langCode 要翻译的语言
     * @returns {string} 翻译结果
     */
    static translate(key, params = [], langCode = undefined) {
        return I18nAPI.get(key, params, langCode);
    }

    /**
     * 获取支持的语言标识符
     * @returns {Array.<string>} 语言标识符数组
     */
    static getSupportedLanguages() {
        return GMLIB_API.getSupportedLanguages();
    }

    /**
     * 获取资源包默认语言
     * @returns {string} 语言标识符
     */
    static getCurrentLanguage() {
        return GMLIB_API.getResourcePackI18nLanguage();
    }

    /**
     * 设置资源包默认语言
     * @param {string} language 语言标识符
     */
    static chooseLanguage(language) {
        GMLIB_API.chooseResourcePackI18nLanguage(language);
    }

    /**
     * 加载语言数据
     * @param {string} code 语言数据
     * @param {string} language 语言标识符
     */
    static loadLanguage(code, language) {
        GMLIB_API.loadLanguage(code, language);
    }

    /**
     * 更新或创建语言文件
     * @param {string} code 语言数据
     * @param {strring} lang 语言标识符
     * @param {string} path 文件路径
     */
    static updateOrCreateLanguageFile(code, lang, path) {
        GMLIB_API.updateOrCreateLanguageFile(code, lang, path);
    }

    /**
     * 加载语言目录
     * @param {string} path 文件夹路径
     */
    static loadLanguageDirectory(path) {
        GMLIB_API.loadLanguagePath(path);
    }
};

/** 玩家数据库API类 */
class UserCache {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 根据uuid获取xuid
     * @param {string} uuid 玩家uuid
     * @returns {string?} xuid
     */
    static getXuidByUuid(uuid) {
        let result = GMLIB_API.getXuidByUuid(uuid);
        return result == "" ? null : result;
    }

    /**
     * 根据xuid获取uuid
     * @param {string} xuid 玩家xuid
     * @returns {string?} uuid
     */
    static getUuidByXuid(xuid) {
        let result = GMLIB_API.getUuidByXuid(xuid);
        return result == "" ? null : result;
    }

    /**
     * 根据xuid获取玩家名称
     * @param {string} xuid 玩家xuid
     * @returns {string?} 玩家名称
     */
    static getNameByUuid(uuid) {
        let result = GMLIB_API.getNameByUuid(uuid);
        return result == "" ? null : result;
    }

    /**
     * 根据xuid获取玩家名称
     * @param {string} xuid 玩家uuid
     * @returns {string?} 玩家名称
     */
    static getNameByXuid(xuid) {
        let result = GMLIB_API.getNameByXuid(xuid);
        return result == "" ? null : result;
    }

    /**
     * 根据名称获取xuid
     * @param {string} name 玩家名称
     * @returns {string?} 玩家的xuid
     */
    static getXuidByName(name) {
        let result = GMLIB_API.getXuidByName(name);
        return result == "" ? null : result;
    }

    /**
     * 根据名称获取uuid
     * @param {string} name 玩家名称
     * @returns {string?} 玩家的uuid
     */
    static getUuidByName(name) {
        let result = GMLIB_API.getUuidByName(name);
        return result == "" ? null : result;
    }

    /**
     * 获取玩家信息
     * @param {string} playerIdentifier 玩家的 xuid 或 uuid 或 名称
     * @returns {{Xuid: String, Uuid: string, Name: string}?} 玩家信息
     */
    static getPlayerInfo(playerIdentifier) {
        return GMLIB_API.getAllPlayerInfo().find(Info => Object.keys(Info).some(InfoKey => Info[InfoKey] === playerIdentifier));
    }

    /**
     * 获取所有玩家信息
     * @returns {Array.<{Xuid: String, Uuid: string, Name: string}>} 包含所有玩家信息的数组
     */
    static getAllPlayerInfo() {
        return GMLIB_API.getAllPlayerInfo();
    }
};

/** 二进制数据包API类 */
class GMLIB_BinaryStream {

    /** 数据包ID @type {number} */
    #id = null;
    /** 数据包是否被销毁 @type {boolean} */
    #destroy = false;

    /**
     * 创建二进制流数据包
     * @param {({"type":string,"value":any}[]|GMLIB_BinaryStream)?} value 写入数据
     * @returns {GMLIB_BinaryStream}
     */
    constructor(value) {
        this.#id = value instanceof GMLIB_BinaryStream ? GMLIB_BinaryStream_API.copy(value.getId()) : GMLIB_BinaryStream_API.create();
        if (Array.isArray(value)) this.write(value);
    }

    /**
     * 获取数据包的ID
     * @returns {number}
     */
    getId() {
        return this.#id;
    }

    /**
     * 发送数据包
     * @param {Player|Entity} player 玩家
     * @param {boolean} [free=true] 发送后销毁数据包
     * @returns {GMLIB_BinaryStream}
     */
    sendTo(player, free = true) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        if (player instanceof LLSE_Entity && player.isPlayer()) player = player.toPlayer();
        if (player instanceof LLSE_Player && !player.isSimulatedPlayer()) GMLIB_BinaryStream_API.sendTo(this.#id, player);
        if (free) this.destroy();
        return this;
    }

    /**
     * 发送数据包到玩家
     * @param {Player[]|Entity[]} players 玩家对象数组
     * @param {boolean} free 发送后销毁数据包
     * @returns {GMLIB_BinaryStream}
     */
    sendToPlayers(players, free = true) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        players.forEach(player => this.sendTo(player, false));
        if (free) this.destroy();
        return this;
    }

    /** 
     * 发送数据包到所有玩家
     * @param {boolean} [free=true] 发送后销毁数据包
     * @returns {GMLIB_BinaryStream}
     */
    sendToAll(free = true) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        mc.getOnlinePlayers().forEach(player => this.sendTo(player, false));
        if (free) this.destroy();
        return this;
    }

    /**
     * 发送数据包到维度
     * @param {number} dimid 维度ID
     * @param {boolean} [free=true] 发送后销毁数据包
     * @returns {GMLIB_BinaryStream}
     */
    sendToDimension(dimid, free = true) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        mc.getOnlinePlayers().filter(player => player.pos.dimid === dimid).forEach(player => this.sendTo(player, false));
        if (free) this.destroy();
        return this;
    }

    /**
     * 销毁数据包
     * @returns {GMLIB_BinaryStream}
     */
    destroy() {
        GMLIB_BinaryStream_API.destroy(this.#id);
        this.#destroy = true;
        return this;
    }

    /**
     * 数据包是否已被销毁
     * @returns {boolean} 
     */
    isDestroy() {
        return this.#destroy;
    }

    /**
     * 重置数据包
     * @returns {GMLIB_BinaryStream}
     */
    reset() {
        GMLIB_BinaryStream_API.reset(this.#id);
        this.#destroy = false;
        return this;
    }

    /**
     * 转换成字符串
     * @returns {string} 字符串
     */
    toString() {
        return `<GMLIB_BinaryStream#${this.#id}>`;
    }

    /**
     * 写入数据
     * @param {{"type":string,"value":any}[]|{"type":string,"value":any}} value 数据
     * @returns {GMLIB_BinaryStream}
     */
    write(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        if (Array.isArray(value)) value.forEach(v => this.write(v));
        if (value?.type != null && value?.value != null) this[`write${value.type}`]?.(value.value);
        return this;
    }

    /**
     * 写入数据包头部
     * @param {number} id 数据包ID
     * @returns {GMLIB_BinaryStream}
     */
    writePacketHeader(id) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writePacketHeader(this.#id, id);
        return this;
    }

    /**
     * 写入UUID
     * @param {string} value UUID
     * @returns {GMLIB_BinaryStream}
     */
    writeUuid(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUuid(this.#id, value);
        return this;
    }

    /**
     * 写入物品
     * @param {Item} value 物品
     * @returns {GMLIB_BinaryStream}
     */
    writeItem(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeItem(this.#id, value);
        return this;
    }

    /**
     * 写入NBT
     * @param {NbtCompound} value NBT
     * @returns {GMLIB_BinaryStream}
     */
    writeCompoundTag(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeCompoundTag(this.#id, value);
        return this;
    }

    /**
     * @param {{"id":number,"type":number,"value":string|IntPos|FloatPos|number|NbtCompound}[]} value 数据
     * @returns {GMLIB_BinaryStream}
     */
    writeDataItem(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        this.writeUnsignedVarInt(value.length);
        for (const data of value) {
            this.writeUnsignedVarInt(data.id);
            this.writeUnsignedVarInt(data.type);
            switch (data.type) {
                case 0: this.writeUnsignedChar(data.value); break;
                case 1: this.writeUnsignedShort(data.value); break;
                case 2: this.writeVarInt(data.value); break;
                case 3: this.writeFloat(data.value); break;
                case 4: this.writeString(data.value); break;
                case 5: this.writeCompoundTag(data.value); break;
                case 6: this.writeBlockPos(data.value); break;
                case 7: this.writeVarInt64(data.value); break;
                case 8: this.writeVec3(data.value); break;
                default: throw new Error("Unknown data type");
            }
        }
        return this;
    }

    /**
     * @param {{"mA":number,"mB":number,"mType":number,"mImmediate":boolean,"mPassengerInitiated":boolean}} value 数据
     * @returns {GMLIB_BinaryStream}
     */
    writeActorLink(value) {
        this.writeVarInt64(value.mA);
        this.writeVarInt64(value.mB);
        this.writeUnsignedChar(value.mType);
        this.writeBool(value.mImmediate);
        this.writeBool(value.mPassengerInitiated);
        return this;
    }

    /**
     * 写入字符串
     * @param {string} value 字符串
     * @returns {GMLIB_BinaryStream}
     */
    writeString(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeString(this.#id, value);
        return this;
    }

    /**
     * 写入布尔值
     * @param {boolean} value 布尔值
     * @returns {GMLIB_BinaryStream}
     */
    writeBool(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeBool(this.#id, Boolean(value));
        return this;
    }

    /**
     * 写入字节
     * @param {number} value 字节
     * @returns {GMLIB_BinaryStream}
     */
    writeByte(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeByte(this.#id, Number(value));
        return this;
    }

    /**
     * 写入(双精度)浮点数
     * @param {number} value 浮点数
     * @returns {GMLIB_BinaryStream}
     */
    writeDouble(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeDouble(this.#id, value);
        return this;
    }

    /**
     * 写入(单精度)浮点数
     * @param {number} value 浮点数
     * @returns {GMLIB_BinaryStream}
     */
    writeFloat(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeFloat(this.#id, value);
        return this;
    }

    /**
     * 写入浮点数坐标对象
     * @param {FloatPos} value 浮点数坐标对象
     * @returns {GMLIB_BinaryStream}
     */
    writeVec3({ x, y, z }) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        this.writeFloat(x);
        this.writeFloat(y);
        this.writeFloat(z);
        return this;
    }

    /**
     * 写入整数坐标对象
     * @param {IntPos} value 整数坐标对象
     * @returns {GMLIB_BinaryStream}
     */
    writeBlockPos({ x, y, z }) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        this.writeVarInt(x);
        this.writeUnsignedVarInt(y);
        this.writeVarInt(z);
        return this;
    }

    /**
     * 
     * @param {{"x":number,"z":number}} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeVec2({ x, z }) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        this.writeFloat(x);
        this.writeFloat(z);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeSignedBigEndianInt(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeSignedBigEndianInt(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeSignedInt(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeSignedInt(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeSignedInt64(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeSignedInt64(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeSignedShort(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeSignedShort(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeUnsignedChar(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUnsignedChar(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeUnsignedInt(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUnsignedInt(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeUnsignedInt64(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUnsignedInt64(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeUnsignedShort(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUnsignedShort(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeUnsignedVarInt(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUnsignedVarInt(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeUnsignedVarInt64(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeUnsignedVarInt64(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeVarInt(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeVarInt(this.#id, value);
        return this;
    }

    /**
     * @param {number} value 数值
     * @returns {GMLIB_BinaryStream}
     */
    writeVarInt64(value) {
        if (this.#destroy) throw new Error("The BinaryStream has been destroyed");
        GMLIB_BinaryStream_API.writeVarInt64(this.#id, value);
        return this;
    }
}

LLSE_Player.prototype.toEntity =
    /**
     * 获取实体对象
     * @returns {Entity} 实体对象
     */
    function () {
        return GMLIB_API.PlayerToEntity(this);
    };

LLSE_Player.prototype.getSpawnPoint =
    /**
     * 获取玩家重生坐标
     * @returns {IntPos} 重生坐标对象
     */
    function () {
        return GMLIB_API.getPlayerSpawnPoint(this);
    };

LLSE_Player.prototype.setSpawnPoint =
    /**
     * 设置玩家重生坐标
     * @param {IntPos} pos 坐标对象
     */
    function (pos) {
        GMLIB_API.setPlayerSpawnPoint(this, pos);
    };

LLSE_Player.prototype.clearSpawnPoint =
    /**
     * 清除玩家重生点
     */
    function () {
        GMLIB_API.clearPlayerSpawnPoint(this);
    };

LLSE_Entity.prototype.shootProjectile =
    /**
     * 射弹投射物
     * @param {string} proj 投射物命名空间ID
     * @param {number} [speed=2] 速度 
     * @param {number} [offset=3] 偏移量
     * @returns {boolean} 是射弹投射物
     */
    function (proj, speed = 2, offset = 3) {
        return GMLIB_API.shootProjectile(this, proj, speed, offset);
    };

LLSE_Entity.prototype.throwEntity =
    /**
     * 投掷实体
     * @param {Entity} proj 投掷的实体对象
     * @param {number} [speed=2] 速度
     * @param {number} [offset=3] 偏移量
     * @returns {boolean} 是否投掷成功
     */
    function (proj, speed = 2, offset = 3) {
        return GMLIB_API.throwEntity(this, proj, speed, offset);
    };

LLSE_Entity.prototype.getTranslateKey =
    /**
     * 获取实体翻译键名
     * @returns {string} 翻译键名
     */
    function () {
        return GMLIB_API.getEntityTranslateKey(this);
    };

LLSE_Entity.prototype.getTranslateName =
    /**
     * 获取实体名字翻译
     * @param {string} language 语言标识符
     * @returns {string} 翻译名称
     */
    function (language) {
        return I18nAPI.get(this.getTranslateKey(), [], language);
    };

LLSE_Block.prototype.getTranslateKey =
    /**
     * 获取方块翻译键名
     * @returns {string} 翻译键名
     */
    function () {
        return GMLIB_API.getBlockTranslateKey(this);
    };

LLSE_Block.prototype.getTranslateName =
    /**
     * 获取方块翻译
     * @param {string} language 语言标识符
     * @returns {string} 翻译名称
     */
    function (language) {
        return I18nAPI.get(this.getTranslateKey(), [], language);
    };

LLSE_Item.prototype.getTranslateKey =
    /**
     * 获取物品翻译键名
     * @returns {string} 翻译键名
     */
    function () {
        return GMLIB_API.getItemTranslateKey(this);
    };

LLSE_Item.prototype.getTranslateName =
    /**
     * 获取物品翻译
     * @param {string} language 语言标识符
     * @returns {string} 翻译名称
     */
    function (language) {
        return I18nAPI.get(this.getTranslateKey(), [], language);
    };

LLSE_Block.prototype.getBlockDestroySpeed =
    /**
     * 获取方块硬度
     * @returns {number} 硬度
     */
    function () {
        return GMLIB_API.getBlockDestroySpeed(this);
    };

LLSE_Item.prototype.getDestroyBlockSpeed =
    /**
     * 获取物品挖掘方块速度
     * @param {Block} block 方块对象
     * @returns {number} 挖掘速度
     */
    function (block) {
        return GMLIB_API.getDestroyBlockSpeed(this, block);
    };

LLSE_Block.prototype.playerDestroy =
    /**
     * 使方块被玩家挖掘
     * @param {Player} player 玩家对象
     */
    function (player) {
        GMLIB_API.playerDestroyBlock(this, this.pos, player);
    };

LLSE_Item.prototype.canDestroy =
    /**
     * 物品冒险模式下是否可以挖掘方块
     * @param {Block} block 方块对象
     * @returns {boolean} 物品冒险模式下是否可以挖掘方块
     */
    function (block) {
        return GMLIB_API.itemCanDestroyBlock(this, block);
    };

LLSE_Item.prototype.canDestroyInCreative =
    /**
     * 物品是否能破坏方块
     * @returns {boolean} 是否能破坏方块
     */
    function () {
        return GMLIB_API.itemCanDestroyInCreative(this);
    };

LLSE_Item.prototype.canDestroySpecial =
    /**
     * 物品是否可以采集方块
     * @param {Block} block 方块对象
     * @returns {boolean} 是否可以采集方块
     */
    function (block) {
        return GMLIB_API.itemCanDestroySpecial(this, block);
    };

LLSE_Block.prototype.canDropWithAnyTool =
    /**
     * 
     * @returns {boolean}
     */
    function () {
        return GMLIB_API.blockCanDropWithAnyTool(this);
    };

LLSE_Block.prototype.playerWillDestroy =
    /**
     * 检测方块是否能被玩家挖掘(比如插件拦截)
     * @param {Player} player 玩家对象
     * @returns {boolean}
     */
    function (player) {
        return GMLIB_API.blockPlayerWillDestroy(this, player, this.pos);
    };

LLSE_Player.prototype.attack =
    /**
     * 使玩家攻击实体
     * @param {Entity} entity 实体对象
     * @returns {boolean}
     */
    function (entity) {
        return GMLIB_API.playerAttack(this, entity);
    };

LLSE_Player.prototype.pullInEntity =
    /**
     * 
     * @param {Entity} entity 实体对象
     */
    function (entity) {
        GMLIB_API.playerPullInEntity(this, entity);
    };

LLSE_Item.prototype.applyEnchant =
    /**
     * 添加附魔
     * @param {string} typeName 附魔的命名空间ID
     * @param {number} level 等级
     * @param {boolean} allowNonVanilla 允许非原版附魔
     * @returns {boolean} 是否附魔成功
     */
    function (typeName, level, allowNonVanilla = true) {
        return GMLIB_API.applyEnchant(this, typeName, level, allowNonVanilla);
    };

LLSE_Item.prototype.removeEnchants =
    /**
     * 删除所有附魔
     */
    function () {
        GMLIB_API.removeEnchants(this);
    };

LLSE_Item.prototype.hasEnchant =
    /**
     * 判断是否拥有附魔
     * @param {number} typeName 附魔的命名空间ID
     * @returns {boolean} 是否拥有附魔
     */
    function (typeName) {
        return GMLIB_API.hasEnchant(this, typeName);
    };

LLSE_Item.prototype.getEnchantLevel =
    /**
     * 获取附魔等级
     * @param {number} typeName 附魔ID
     * @returns {number} 附魔等级
     */
    function (typeName) {
        return GMLIB_API.getEnchantLevel(this, typeName);
    };

LLSE_Player.prototype.dropItem =
    /**
     * 使玩家丢出物品
     * @param {Item} item 物品对象
     * @param {boolean} [randomly=false] 随机丢出位置
     * @returns {boolean} 是否丢出成功
     */
    function (item, randomly = false) {
        return GMLIB_API.dropPlayerItem(this, item, randomly);
    };

LLSE_Player.prototype.getRuntimeId =
    /**
     * 获取玩家的runtimeId
     * @returns {number} 玩家的runtimeId    
     */
    function () {
        return GMLIB_API.getPlayerRuntimeId(this);
    };

LLSE_Entity.prototype.getRuntimeId =
    /**
     * 获取实体的runtimeId
     * @returns {number} 实体的runtimeId    
     */
    function () {
        return GMLIB_API.getEntityRuntimeId(this);
    };

LLSE_Entity.prototype.getNameTag =
    /**
     * 获取实体的命名
     * @returns {string} 实体的命名
     */
    function () {
        return GMLIB_API.getEntityNameTag(this);
    };

LLSE_Item.prototype.isUnbreakable =
    /**
     * 物品是否拥有不可破坏标签
     * @returns {boolean} 是否拥有
     */
    function () {
        return GMLIB_API.ItemisUnbreakable(this);
    };

LLSE_Item.prototype.setUnbreakable =
    /**
     * 设置物品不可破坏标签
     * @param {boolean} value 是否不可破坏
     */
    function (value) {
        GMLIB_API.setItemUnbreakable(this, value);
    };

LLSE_Item.prototype.getShouldKeepOnDeath =
    /**
     * 物品是否拥有死亡不掉落标签
     * @returns {boolean} 物品是否拥有死亡不掉落标签
     */
    function () {
        return GMLIB_API.getItemShouldKeepOnDeath(this);
    };

LLSE_Item.prototype.setShouldKeepOnDeath =
    /**
     * 设置物品死亡不掉落标签
     * @param {boolean} value 物品是否死亡不掉落
     */
    function (value) {
        GMLIB_API.setItemShouldKeepOnDeath(this, value);
    };

LLSE_Item.prototype.getItemLockMode =
    /**
     * 获取物品的锁定模式
     * @returns {0|1|2} 锁定的模式 0:无 1:锁定在格子里 2:锁定在背包里
     */
    function () {
        return GMLIB_API.getItemLockMode(this);
    };

LLSE_Item.prototype.setItemLockMode =
    /**
     * 设置物品的锁定模式
     * @param {0|1|2} mode 锁定的模式 0:无 1:锁定在格子里 2:锁定在背包里
     */
    function (mode) {
        GMLIB_API.setItemLockMode(this, mode);
    };

LLSE_Item.prototype.getRepairCost =
    /**
     * 获取物品的惩罚等级
     * @returns {number} 惩罚等级
     */
    function () {
        return GMLIB_API.getItemRepairCost(this);
    };

LLSE_Item.prototype.setRepairCost =
    /**
     * 设置物品的惩罚等级
     * @param {number} cost 要设置的惩罚等级
     */
    function (cost) {
        return GMLIB_API.setItemRepairCost(this, cost);
    };

LLSE_Item.prototype.getCanDestroy =
    /**
     * 获取冒险模式下能破坏的方块
     * @returns {Array.<string>} 能破坏的方块
     */
    function () {
        return GMLIB_API.getItemCanDestroy(this);
    };

LLSE_Item.prototype.setCanDestroy =
    /**
     * 设置冒险模式下能破坏的方块
     * @param {Array.<string>} blocks 能破坏的方块
     */
    function (blocks) {
        GMLIB_API.setItemCanDestroy(this, blocks);
    };

LLSE_Item.prototype.getCanPlaceOn =
    /**
     * 获取冒险模式下能放置在什么方块上
     * @returns {Array.<string>} 能放置的方块
     */
    function () {
        return GMLIB_API.getItemCanPlaceOn(this);
    };

LLSE_Item.prototype.setCanPlaceOn =
    /**
     * 设置冒险模式下能放置在什么方块上
     * @param {Array.<string>} blocks 能放置的方块
     */
    function (blocks) {
        GMLIB_API.setItemCanPlaceOn(this, blocks);
    };

LLSE_Player.prototype.getHungry =
    /**
     * 获取玩家饥饿值
     * @returns {number}
     */
    function () {
        return GMLIB_API.getPlayerHungry(this);
    };

LLSE_Player.prototype.getArmorCoverPercentage =
    /**
     * 获取玩家盔甲覆盖百分比
     * @returns {number}
     */
    function () {
        return GMLIB_API.getPlayerArmorCoverPercentage(this);
    };

LLSE_Player.prototype.getArmorValue =
    /**
     * 获取玩家盔甲值覆盖百分比
     * @returns {number}
     */
    function () {
        return GMLIB_API.getPlayerArmorValue(this);
    };

LLSE_Entity.prototype.getEntityOwner =
    /**
     * 获取实体的主人
     * @returns {Entity|null}
     */
    function () {
        const uniqueId = GMLIB_API.getEntityOwnerUniqueId(this);
        return uniqueId === -1 ? null : Minecraft.getEntityFromUniqueId(uniqueId);
    };

LLSE_Item.prototype.getCategoryName =
    /**
     * 获取物品分类名称
     * @returns {string}
     */
    function () {
        return GMLIB_API.getItemCategoryName(this);
    };

LLSE_Item.prototype.getCustomName =
    /**
     * 获取物品的命名
     * @returns {string}
     */
    function () {
        return GMLIB_API.getItemCustomName(this);
    };

LLSE_Item.prototype.getEffecName =
    /**
     * 获取物品的BUFF效果名称
     * @returns {string}
     */
    function () {
        return GMLIB_API.getItemEffecName(this);
    };

LLSE_Item.prototype.isFood =
    /**
     * 物品是否为食物
     * @returns {boolean}
     */
    function () {
        return GMLIB_API.itemIsFood(this);
    };

LLSE_Player.prototype.setPlayerUIItem =
    /**
     * 设置玩家UI栏物品
     * @param {number} slot 格子槽位
     * @param {Item} item 要设置的物品
     */
    function (slot, item) {
        GMLIB_API.setPlayerUIItem(this, slot, item);
    };

LLSE_Player.prototype.getPlayerUIItem =
    /**
     * 获取玩家UI栏物品
     * @param {number} slot 格子槽位
     * @returns {Item} 物品对象
     */
    function (slot) {
        return GMLIB_API.getPlayerUIItem(this, slot);
    };

LLSE_Player.prototype.sendInventorySlotPacket =
    /**
     * 发送更新更新物品数据包
     * @param {number} containerId 容器ID
     * @param {number} slot 格子槽位
     * @param {Item} item 物品对象
     */
    function (containerId, slot, item) {
        GMLIB_API.sendInventorySlotPacket(this, containerId, slot, item);
    };

LLSE_Player.prototype.getNetworkProtocolVersion =
    /**
     * 获取客户端版本协议
     * @returns {number}
     */
    function (containerId, slot, item) {
        GMLIB_API.getPlayerProtocolVersion(this);
    };

LLSE_Container.prototype.getContainerType =
    /**
     * 获取容器类型
     * @returns {string}
     */
    function () {
        return GMLIB_API.getContainerType(this);
    };

LLSE_Item.prototype.getMaxCount =
    /**
     * 获取物品最大堆叠数量
     * @returns {number}
     */
    function () {
        return GMLIB_API.getItemMaxCount(this);
    };

LLSE_Entity.prototype.hasFamily =
    /**
     * 实体是否拥包含在某族里
     * @param {string} family 实体族
     * @returns {boolean}
     */
    function (family) {
        return GMLIB_API.entityHasFamily(this, family);
    };

LLSE_Player.prototype.getDestroyProgress =
    /**
     * 获取玩家破坏方块所需时间
     * @param {Block} block 
     * @returns {number}
     */
    function (block) {
        return GMLIB_API.getPlayerDestroyBlockProgress(this, block);
    };

LLSE_Entity.prototype.hasEffect =
    /**
     * 实体是否拥有buff效果
     * @param {number} effectId buff效果ID
     * @returns {boolean}
     */
    function (effectId) {
        return GMLIB_API.entityHasEffect(this, effectId);
    };

LLSE_Entity.prototype.getEffectInfo =
    /**
     * 获取buff信息
     * @param {number} effectId buff效果ID
     * @returns {{Id: number, Amplifier: number, Duration: number, DurationEasy: number, DurationNormal: number, DurationHard: number, Ambient: boolean, ShowParticles: boolean} | null}
     */
    function (effectId) {
        if (!this.hasEffect(effectId)) return null;
        return {
            Id: effectId,
            Amplifier: GMLIB_API.getEntityEffectAmplifier(this, effectId),
            Duration: GMLIB_API.getEntityEffectDuration(this, effectId),
            DurationEasy: GMLIB_API.getEntityEffectDurationEasy(this, effectId),
            DurationNormal: GMLIB_API.getEntityEffectDurationNormal(this, effectId),
            DurationHard: GMLIB_API.getEntityEffectDurationHard(this, effectId),
            Ambient: GMLIB_API.getEntityEffectAmbient(this, effectId),
            ShowParticles: GMLIB_API.getEntityEffectVisible(this, effectId),
        };
    };

LLSE_Entity.prototype.getAllEffectsInfo =
    /**
     * 获取所有buff信息
     * @returns {{Id: number, Amplifier: number, Duration: number, DurationEasy: number, DurationNormal: number, DurationHard: number, Ambient: boolean, ShowParticles: boolean}[]}
     */
    function () {
        return this.getAllEffects().map(effectId => this.getEffectInfo(effectId));
    };

LLSE_Entity.prototype.isType =
    /**
     * 是否为某类型
     * @param {number} type 类型
     * @returns {boolean}
     */
    function (type) {
        return GMLIB_API.entityIsType(this, type);
    };

LLSE_Entity.prototype.hasType =
    /**
     * 是否包含某类型
     * @param {number} type 类型
     * @returns {boolean}
     */
    function (type) {
        return GMLIB_API.entityHasType(this, type);
    };

LLSE_Entity.prototype.getEntityTypeId =
    /**
     * 获取实体类型ID
     * @returns {number}
     */
    function () {
        return GMLIB_API.getEntityTypeId(this);
    };

const ActorType = Object.freeze({
    Undefined: 1,
    TypeMask: 0b11111111,
    None: 0,
    Mob: 1 << 8,
    PathfinderMob: 1 << 9 | this.Mob,
    UnknownType: 1 << 10,
    Monster: 1 << 11 | this.PathfinderMob,
    Animal: 1 << 12 | this.PathfinderMob,
    WaterAnimal: 1 << 13 | this.PathfinderMob,
    TamableAnimal: 1 << 14 | this.Animal,
    Ambient: 1 << 15 | this.Mob,
    UndeadMob: 1 << 16 | this.Monster,
    ZombieMonster: 1 << 17 | this.UndeadMob,
    Arthropod: 1 << 18 | this.Monster,
    Minecart: 1 << 19,
    SkeletonMonster: 1 << 20 | this.UndeadMob,
    EquineAnimal: 1 << 21 | this.TamableAnimal,
    Projectile: 1 << 22,
    AbstractArrow: 1 << 23,
    VillagerBase: 1 << 24 | this.PathfinderMob,

    Chicken: 10 | this.Animal,
    Cow: 11 | this.Animal,
    Pig: 12 | this.Animal,
    Sheep: 13 | this.Animal,
    Wolf: 14 | this.TamableAnimal,
    Villager: 15 | this.VillagerBase,
    MushroomCow: 16 | this.Animal,
    Squid: 17 | this.WaterAnimal,
    Rabbit: 18 | this.Animal,
    Bat: 19 | this.Ambient,
    IronGolem: 20 | this.PathfinderMob,
    SnowGolem: 21 | this.PathfinderMob,
    Ocelot: 22 | this.TamableAnimal,
    Horse: 23 | this.EquineAnimal,
    Donkey: 24 | this.EquineAnimal,
    Mule: 25 | this.EquineAnimal,
    SkeletonHorse: 26 | this.EquineAnimal | this.UndeadMob,
    ZombieHorse: 27 | this.EquineAnimal | this.UndeadMob,
    PolarBear: 28 | this.Animal,
    Llama: 29 | this.Animal,
    Parrot: 30 | this.TamableAnimal,
    Dolphin: 31 | this.WaterAnimal,
    Zombie: 32 | this.ZombieMonster,
    Creeper: 33 | this.Monster,
    Skeleton: 34 | this.SkeletonMonster,
    Spider: 35 | this.Arthropod,
    PigZombie: 36 | this.UndeadMob,
    Slime: 37 | this.Monster,
    EnderMan: 38 | this.Monster,
    Silverfish: 39 | this.Arthropod,
    CaveSpider: 40 | this.Arthropod,
    Ghast: 41 | this.Monster,
    LavaSlime: 42 | this.Monster,
    Blaze: 43 | this.Monster,
    ZombieVillager: 44 | this.ZombieMonster,
    Witch: 45 | this.Monster,
    Stray: 46 | this.SkeletonMonster,
    Husk: 47 | this.ZombieMonster,
    WitherSkeleton: 48 | this.SkeletonMonster,
    Guardian: 49 | this.Monster,
    ElderGuardian: 50 | this.Monster,
    Npc: 51 | this.Mob,
    WitherBoss: 52 | this.UndeadMob,
    Dragon: 53 | this.Monster,
    Shulker: 54 | this.Monster,
    Endermite: 55 | this.Arthropod,
    Agent: 56 | this.Mob,
    Vindicator: 57 | this.Monster,
    Phantom: 58 | this.UndeadMob,
    IllagerBeast: 59 | this.Monster,
    UNUSED60: 60,
    ArmorStand: 61 | this.Mob,
    TripodCamera: 62 | this.Mob,
    Player: 63 | this.Mob,
    ItemEntity: 64 | this.None,
    PrimedTnt: 65 | this.None,
    FallingBlock: 66 | this.None,
    MovingBlock: 67 | this.None,
    ExperiencePotion: 68 | this.Projectile,
    Experience: 69 | this.None,
    EyeOfEnder: 70 | this.None,
    EnderCrystal: 71 | this.None,
    FireworksRocket: 72 | this.None,
    Trident: 73 | this.Projectile | this.AbstractArrow,
    Turtle: 74 | this.Animal,
    Cat: 75 | this.TamableAnimal,
    ShulkerBullet: 76 | this.Projectile,
    FishingHook: 77 | this.None,
    Chalkboard: 78 | this.None,
    DragonFireball: 79 | this.Projectile,
    Arrow: 80 | this.Projectile | this.AbstractArrow,
    Snowball: 81 | this.Projectile,
    ThrownEgg: 82 | this.Projectile,
    Painting: 83 | this.None,
    MinecartRideable: 84 | this.Minecart,
    LargeFireball: 85 | this.Projectile,
    ThrownPotion: 86 | this.Projectile,
    Enderpearl: 87 | this.Projectile,
    LeashKnot: 88 | this.None,
    WitherSkull: 89 | this.Projectile,
    BoatRideable: 90 | this.None,
    WitherSkullDangerous: 91 | this.Projectile,
    UNUSED92: 92,
    LightningBolt: 93 | this.None,
    SmallFireball: 94 | this.Projectile,
    AreaEffectCloud: 95 | this.None,
    MinecartHopper: 96 | this.Minecart,
    MinecartTNT: 97 | this.Minecart,
    MinecartChest: 98 | this.Minecart,
    MinecartFurnace: 99 | this.Minecart,
    MinecartCommandBlock: 100 | this.Minecart,
    LingeringPotion: 101 | this.Projectile,
    LlamaSpit: 102 | this.Projectile,
    EvocationFang: 103 | this.Projectile,
    EvocationIllager: 104 | this.Monster,
    Vex: 105 | this.Monster,
    IceBomb: 106 | this.Projectile,
    Balloon: 107 | this.None,
    Pufferfish: 108 | this.WaterAnimal,
    Salmon: 109 | this.WaterAnimal,
    Drowned: 110 | this.ZombieMonster,
    Tropicalfish: 111 | this.WaterAnimal,
    Fish: 112 | this.WaterAnimal,
    Panda: 113 | this.Animal,
    Pillager: 114 | this.Monster,
    VillagerV2: 115 | this.VillagerBase,
    ZombieVillagerV2: 116 | this.ZombieMonster,
    Shield: 117 | this.None,
    WanderingTrader: 118 | this.PathfinderMob,
    Lectern: 119 | this.None,
    ElderGuardianGhost: 120 | this.Monster,
    Fox: 121 | this.Animal,
    Bee: 122 | this.Mob,
    Piglin: 123 | this.Mob,
    Hoglin: 124 | this.Animal,
    Strider: 125 | this.Animal,
    Zoglin: 126 | this.UndeadMob,
    PiglinBrute: 127 | this.Mob,
    Goat: 128 | this.Animal,
    GlowSquid: 129 | this.WaterAnimal,
    Axolotl: 130 | this.Animal,
    Warden: 131 | this.Monster,
    Frog: 132 | this.Animal,
    Tadpole: 133 | this.WaterAnimal,
    Allay: 134 | this.Mob,
    ChestBoatRideable: 136 | this.BoatRideable,
    TraderLlama: 137 | this.Llama,
    Camel: 138 | this.Animal,
    Sniffer: 139 | this.Animal,
    Breeze: 140 | this.Monster,
    BreezeWindChargeProjectile: 141 | this.Projectile,
    Armadillo: 142 | this.Animal,
    WindChargeProjectile: 143 | this.Projectile,
    Bogged: 144 | this.SkeletonMonster,
    OminousItemSpawner: 145,
});

module.exports = {
    StaticFloatingText,
    DynamicFloatingText,
    Minecraft,
    Recipes,
    Experiments,
    Scoreboard,
    JsonConfig,
    JsonLanguage,
    JsonI18n,
    Version,
    I18nAPI,
    UserCache,
    GMLIB_BinaryStream,
    ActorType
};