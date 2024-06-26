/** 静态悬浮字类 */
declare class StaticFloatingText {
    constructor(
        /** 生成的坐标 */
        pos: FloatPos,
        /** 显示的文本 */
        text: string,
        /** 是否启用papi变量 */
        papi: boolean | undefined
    );

    /** 发送悬浮字给玩家 */
    sendToClient(
        /** 要发送的玩家对象 */
        player: Player
    ): boolean;

    /** 发送悬浮字给所有玩家 */
    sendToClients(): boolean;

    /** 删除玩家的悬浮字 */
    removeFromClient(
        /** 要删除的玩家的玩家对象 */
        player: Player
    ): boolean;

    /** 删除所有玩家悬浮字 */
    removeFromClients(): boolean;

    /** 更新玩家的悬浮字 */
    updateClient(
        player: Player
    ): boolean;

    /** 更新所有玩家的悬浮字 */
    updateClients(): boolean;

    /** 获取悬浮字的RuntimeId */
    getRuntimeId(): number;

    /** 获取悬浮字显示的文本 */
    getText(): string;

    /** 设置悬浮字显示的文本 */
    setText(
        /** 要显示的文本 */
        text: string
    ): void;

    /** 更新所有玩家的悬浮字 */
    update(): boolean;

    /** 更新悬浮字文本 */
    updateText(
        /** 要显示的文本 */
        text: string
    ): boolean;

    /** 获取悬浮字的坐标 */
    getPos(): FloatPos;

    /** 删除悬浮字 */
    destroy(): boolean

    /** 根据RuntimeId获取静态悬浮字 */
    static getFloatingText(
        /** 悬浮字的RuntimeId */
        runtimeId: number
    ): StaticFloatingText | null;

    /** 获取所有静态悬浮字 */
    static getAllFloatingTexts(): Array<StaticFloatingText>;
}

/** 动态悬浮字类 */
declare class DynamicFloatingText extends StaticFloatingText {
    constructor(
        /** 生成的坐标 */
        pos: FloatPos,
        /** 显示的文本 */
        text: string,
        /** 更新频率(秒) */
        updateRate: number | undefined,
        /** 是否使用PAPI变量 */
        papi: boolean | undefined
    );

    /** 获取悬浮字更新频率 */
    getUpdateRate(): number

    /** 设置悬浮字更新频率 */
    setUpdateRate(
        updateRate: number | undefined
    ): void;

    /** 开始更新悬浮字 */
    startUpdate(): boolean;

    /** 停止更新悬浮字 */
    stopUpdate(): boolean;

    /** 删除悬浮字 */
    destroy(): boolean;

    /** 根据RuntimeId获取动态悬浮字 */
    static getFloatingText(
        /** 悬浮字的RuntimeId */
        runtimeId: number
    ): StaticFloatingText | null;

    /** 获取所有动态悬浮字 */
    static getAllFloatingTexts(): Array<DynamicFloatingText>;
}

/** 基础游戏API类 */
declare class Minecraft {
    private constructor();

    /** 获取服务器平均tps */
    static getServerAverageTps(): number;

    /** 获取服务器当前tps */
    static getServerCurrentTps(): number;

    /** 获取服务器mspt */
    static getServerMspt(): number;

    /** 获取所有玩家uuid */
    static getAllPlayerUuids(): Array<string>;

    /** 获取玩家NBT */
    static getPlayerNbt(
        /** 玩家uuid */
        uuid: string
    ): NbtCompound;

    /** 写入玩家NBT */
    static setPlayerNbt(
        /** 玩家uuid */
        uuid: string,
        /** 要设置的NBT数据 */
        nbt: NbtCompound,
        /** 不存在是否创建 */
        forceCreate: boolean | undefined
    ): boolean;

    /** 覆盖玩家NBT的特定Tags */
    static setPlayerNbtTags(
        /** 玩家uuid */
        uuid: string,
        /** 要设置的NBT数据 */
        nbt: NbtCompound,
        /** 要覆盖的NBT标签 */
        tags: string
    ): boolean;

    /** 删除玩家NBT */
    static deletePlayerNbt(
        /** 玩家uuid */
        uuid: string,
    ): boolean;

    /** 获取玩家坐标 */
    static getPlayerPosition(
        /** 玩家uuid */
        uuid: string
    ): IntPos | null;

    /** 设置玩家坐标 */
    static setPlayerPosition(
        /** 玩家uuid */
        uuid: string,
        /** 玩家坐标 */
        pos: IntPos
    ): boolean;

    /** 获取世界出生点 */
    static getWorldSpawn(): IntPos;

    /** 设置世界出生点 */
    static setWorldSpawn(
        /** 要设置的出生点坐标对象 */
        pos: IntPos
    ): void;

    /** 启用教育版内容 */
    static setEducationFeatureEnabled(): void;

    /** 注册Ability命令 */
    static registerAbilityCommand(): void;

    /** 启用Xbox成就 */
    static setEnableAchievement(): void;

    /** 信任所有玩家皮肤 */
    static setForceTrustSkins(): void;

    /** 启用资源包双端共存 */
    static enableCoResourcePack(): void;

    /** 获取存档名称 */
    static getWorldName(): string;

    /** 设置存档名称 */
    static setWorldName(
        name: string
    ): boolean;

    /** 设置假种子 */
    static setFakeSeed(
        /** 要设置的假种子 */
        seed: number | undefined
    ): void;

    /** 启用错误方块清理 */
    static setUnknownBlockCleaner(): void;

    /** 强制生成实体 */
    static spawnEntity(
        /** 生成坐标 */
        pos: FloatPos,
        /** 实体命名空间 */
        name: string
    ): Entity;

    /** 射弹投射物 */
    static shootProjectile(
        /** 实体对象 */
        entity: Entity,
        /** 投射物命名空间 */
        proj: string,
        /** 速度 */
        speed: number,
        /** 偏移量 */
        offset: number
    ): boolean;

    /** 投掷实体 */
    static throwEntity(
        /** 实体对象 */
        entity: Entity,
        /** 被投掷的实体 */
        proj: Entity,
        /** 速度 */
        speed: number,
        /** 偏移量 */
        offset: number
    ): boolean;

    /** 获取服务器使用的语言 */
    static getServerLanguage(): string;

    /** 设置服务器使用的语言 */
    static setServerLanguage(
        language: string
    ): boolean;

    /** 设置资源包路径 */
    static setCustomPackPath(
        /** 要设置的路径 */
        path: string
    ): void;

    /** 翻译资源包文本 */
    static resourcePackTranslate(
        /** 键名 */
        key: string,
        /** 参数 */
        params: string[] | undefined
    ): string;

    /** 根据uuid获取玩家对象 */
    static getPlayerFromUuid(
        uuid: string
    ): Player;

    /** 根据UniqueId获取玩家对象 */
    static getPlayerFromUniqueId(
        uniqueId: string
    ): Player;

    /** 根据UniqueId获取实体对象 */
    static getEntityFromUniqueId(
        uniqueId: string
    ): Entity;

    /** 获取方块runtimeId */
    static getBlockRuntimeId(
        /** 方块命名空间 */
        block: string,
        /** 方块的特殊值 */
        legacyData: Number | undefined
    ): number;

    /** 添加虚假列表玩家 */
    static addFakeList(
        /** 虚假玩家的名字 */
        name: string,
        /** 虚假玩家的xuid */
        xuid: string
    ): boolean;

    /** 移除虚假列表玩家 */
    static removeFakeList(
        /** 虚假的玩家名字或xuid */
        nameOrXuid: string
    ): boolean;

    /** 移除所有虚假列表玩家 */
    static removeAllFakeLists(): boolean;

    /** 启用I18n修复 */
    static setFixI18nEnabled(): void;

    /** 保存NBT至文件 */
    static saveNbtToFile(
        /** 文件路径 */
        path: string,
        /** NBT对象 */
        nbt: NbtCompound,
        /** 是否写入为二进制 */
        isBinary: boolean | undefined
    ): boolean;

    /** 从文件读取NBT */
    static readNbtFromFile(
        /** 文件路径 */
        path: string,
        /** 是否以二进制方式读取 */
        isBinary: boolean | undefined
    ): NbtCompound;

    /** 根据命名空间获取翻译键名 */
    static getBlockTranslateKeyFromName(
        /** 方块命名空间 */
        name: string
    ): string;

    /** 获取存档种子号 */
    static getLevelSeed(): string;

    /** 获取方块亮度 */
    static getBlockLightEmission(
        /** 方块的命名空间 */
        block: string,
        /** 方块的特殊值 */
        legacyData: number
    ): number;

    /** 获取游戏规则列表 */
    static getGameRules(): { Name: string; Value: boolean | number; }[];

    /** 获取附魔名字和等级 */
    static getEnchantNameAndLevel(
        /** 附魔命名空间 */
        typeName: string,
        /** 附魔的等级 */
        level: number
    ): string;

    /** 通过附魔ID获取附魔命名空间 */
    static getMaxPlayers(
        /** 附魔ID */
        id: number
    ): string | null;

    /** 获取最大玩家数 */
    static getMaxPlayers(): number;
}

/** 合成表类 */
declare class Recipes {
    private constructor();

    /** 注销合成表 */
    static unregisterRecipe(
        /** 合成表唯一标识符 */
        recipeId: string
    ): boolean;

    /** 注册切石机合成表 */
    static registerStoneCutterRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 输入物品 */
        inputName: string,
        /** 输入物品额外数据 */
        inputAux: number,
        /** 合成结果 */
        outputName: string,
        /** 合成结果额外数据 */
        outputAux: number,
        /** 合成数量 */
        outputCount: number
    ): boolean;

    /** 注册锻造纹饰合成表 */
    static registerSmithingTrimRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 锻造模板 */
        template: string,
        /** 基础材料 */
        base: string,
        /** 纹饰材料 */
        addition: string
    ): boolean;

    /** 注册锻造配方合成表 */
    static registerSmithingTransformRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 锻造模板 */
        template: string,
        /** 基础材料 */
        base: string,
        /** 升级材料 */
        addition: string,
        /** 合成结果 */
        result: string
    ): boolean;

    /** 注册酿造容器表 */
    static registerBrewingContainerRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 输入物品 */
        input: string,
        /** 合成结果 */
        output: string,
        /** 酿造物品 */
        reagent: string
    ): boolean;

    /** 注册酿造混合表 */
    static registerBrewingMixRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 输入物品 */
        input: string,
        /** 合成结果 */
        output: string,
        /** 酿造物品 */
        reagent: string
    ): boolean;

    /** 注册熔炼合成表 */
    static registerFurnaceRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 输入物品 */
        input: string,
        /** 合成结果 */
        output: string,
        /** 材料的标签数组 */
        tags: ("furnace" | "blast_furnace" | "smoker" | "campfire" | "soul_campfire")[] | undefined
    ): boolean;

    /** 注册有序合成表 */
    static registerShapedRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 合成表摆放方式，数组元素为字符串 */
        shape: [string, string, string],
        /** 材料数组 */
        ingredients: string[],
        /** 合成结果 */
        result: string,
        /** 合成结果的数量 */
        count: number | undefined,
        /** 解锁条件(也可以填物品命名空间) */
        unlock: "AlwaysUnlocked" | "PlayerHasManyItems" | "PlayerInWater" | "None" | undefined
    ): boolean;

    /** 注册无序合成表 */
    static registerShapelessRecipe(
        /** 合成表唯一标识符 */
        recipeId: string,
        /** 合成材料 */
        ingredients: string[],
        /** 合成结果 */
        result: string,
        /** 合成结果的数量 */
        count: number | undefined,
        /** 解锁条件(也可以填物品命名空间) */
        unlock: "AlwaysUnlocked" | "PlayerHasManyItems" | "PlayerInWater" | "None" | undefined
    ): boolean;
}

/** 实验性功能类 */
declare class Experiments {
    private constructor();

    /** 获取所有实验的id */
    static getAllExperimentIds(): number[];

    /** 获取实验性功能文本的键名 */
    static getExperimentTranslateKey(
        /** 实验性功能的id */
        id: number
    ): string;

    /** 获取实验性功能启用状态 */
    static getExperimentEnabled(
        /** 实验性功能的id */
        id: number
    ): boolean;

    /** 设置实验性功能启用状态 */
    static setExperimentEnabled(
        /** 实验性功能的id */
        id: number,
        /** 实验性功能是否开启 */
        value: boolean | undefined
    ): void;

    /** 设置实验性依赖 */
    static registerExperimentsRequire(
        /** 实验性功能的id */
        id: number,
    ): void
}

/** 计分板类 */
declare class Scoreboard {
    private constructor();

    /** 获取所有跟踪实体 */
    static getAllTrackedEntities(): string[];

    /** 获取所有跟踪的玩家 */
    static getAllTrackedPlayers(): string[];

    /** 获取所有跟踪的字符串 */
    static getAllTrackedFakePlayers(): string[];

    /** 获取所有跟踪目标 */
    static getAllTrackedTargets(): ({ Type: "Player"; Uuid: string; } | { Type: "FakePlayer"; Name: string; } | { Type: "Entity"; UniqueId: string; })[]

    /** 创建计分板 */
    static addObjective(
        /** 计分板名字 */
        name: string,
        /** 显示名称 */
        displayName: string,
    ): boolean;

    /** 移除计分板 */
    static removeObjective(
        /** 计分板名字 */
        name: string
    ): boolean;

    /** 获取所有计分板名字 */
    static getAllObjectives(): string[];

    /** 获取计分板显示名称 */
    static getDisplayName(
        /** 计分板名字 */
        objective: string
    ): string;

    /** 设置计分板显示名称 */
    static setDisplayName(
        /** 计分板名字 */
        objective: string,
        /** 显示名称 */
        displayName: string
    ): boolean;

    /** 设置计分板显示 */
    static setDisplay(
        /** 计分板名字 */
        objective: string,
        /** 显示位置 */
        slot: "sidebar" | "list" | "belowName",
        /** 排序方式 */
        order: 0 | 1
    ): void;

    /** 清除计分板显示 */
    static clearDisplay(
        /** 计分板名字 */
        objective: string
    ): void;

    /** 获取玩家在计分板中的值 */
    static getPlayerScore(
        /** 玩家的uuid */
        uuid: string,
        /** 计分板名字 */
        objective: string
    ): number | null;

    /** 增加玩家在计分板中的值 */
    static addPlayerScore(
        /** 玩家的uuid */
        uuid: string,
        /** 计分板名字 */
        objective: string,
        /** 增加的值 */
        value: number
    ): boolean;

    /** 减少玩家在计分板中的值 */
    static reducePlayerScore(
        /** 玩家的uuid */
        uuid: string,
        /** 计分板名字 */
        objective: string,
        /** 减少的值 */
        value: number
    ): boolean;

    /** 设置玩家在计分板中的值 */
    static setPlayerScore(
        /** 玩家的uuid */
        uuid: string,
        /** 计分板名字 */
        objective: string,
        /** 设置的值 */
        value: number
    ): boolean;

    /** 重载玩家在计分板中的数据 */
    static resetPlayerScore(
        /** 玩家的uuid */
        uuid: string,
        /** 计分板名字 */
        objective: string
    ): boolean;

    /** 重置玩家所有计分板的数据 */
    static resetPlayerScores(
        /** 玩家的uuid */
        uuid: string
    ): boolean;

    /** 获取字符串在计分板中的值 */
    static getFakePlayerScore(
        /** 字符串名字 */
        name: string,
        /** 计分板名字 */
        objective: string
    ): number | null;

    /** 增加字符串在计分板中的值 */
    static addFakePlayerScore(
        /** 字符串名字 */
        name: string,
        /** 计分板名字 */
        objective: string,
        /** 增加的值 */
        value: number
    ): boolean;

    /** 减少字符串在计分板中的值 */
    static reduceFakePlayerScore(
        /** 字符串名字 */
        name: string,
        /** 计分板名字 */
        objective: string,
        /** 减少的值 */
        value: number
    ): boolean;

    /** 设置字符串在计分板中的值 */
    static setFakePlayerScore(
        /** 字符串名字 */
        name: string,
        /** 计分板名字 */
        objective: string,
        /** 设置的值 */
        value: number
    ): boolean;

    /** 重载字符串在计分板中的数据 */
    static resetFakePlayerScore(
        /** 字符串名字 */
        name: string,
        /** 计分板名字 */
        objective: string
    ): boolean;

    /** 重载字符串所有计分板数据 */
    static resetAllFakePlayerScores(
        /** 字符串名字 */
        name: string
    ): boolean;

    /** 获取实体在计分板中的值 */
    static getEntityScore(
        /** 实体的uniqueId */
        uniqueId: string,
        /** 计分板名字 */
        objective: string
    ): number | null;

    /** 增加实体在计分板中的值 */
    static addEntityScore(
        /** 实体的uniqueId */
        uniqueId: string,
        /** 计分板名字 */
        objective: string,
        /** 增加的值 */
        value: number
    ): boolean;

    /** 减少实体在计分板中的值 */
    static reduceEntityScore(
        /** 实体的uniqueId */
        uniqueId: string,
        /** 计分板名字 */
        objective: string,
        /** 减少的值 */
        value: number
    ): boolean;

    /** 设置实体在计分板中的值 */
    static setEntityScore(
        /** 实体的uniqueId */
        uniqueId: string,
        /** 计分板名字 */
        objective: string,
        /** 设置的值 */
        value: number
    ): boolean;

    /** 重载实体在计分板中的数据 */
    static resetEntityScore(
        /** 实体的uniqueId */
        uniqueId: string,
        /** 计分板名字 */
        objective: string
    ): boolean;

    /** 重载实体所有计分板数据 */
    static resetAllEntityScores(
        /** 实体的uniqueId */
        uniqueId: string
    ): boolean;
}

/** 仿LSE的JsonConfigFile类 */
declare class JsonConfig {
    constructor(
        /** 文件路径 */
        path: string,
        /** 默认数据 */
        defaultData: object | undefined
    );

    /** 初始化文件 */
    init(): void;

    /** 保存文件 */
    save(
        /** 缩进 */
        format: number | undefined
    ): void;

    /** 获取所有数据 */
    getData(): object;

    /** 读取数据 */
    get(
        /** 键名 */
        key: string,
        /** 不存在返回值 */
        defaultValue: any
    ): any;

    /** 设置数据 */
    set(
        /** 键名 */
        key: string,
        /** 值 */
        value: any
    ): void;

    /** 删除数据 */
    delete(
        /** 键名 */
        key: string
    ): void;
}

declare class JsonLanguage extends JsonConfig {
    /** 创建或打开一个 Json 语言文件 */
    constructor(
        /** 文件路径 */
        path: string,
        /** 默认数据 */
        defaultData: object | undefined
    );

    /** 翻译键名 */
    translate(
        /** 键名 */
        key: string,
        /** 替换参数 */
        data: string[]
    ): string;
}

declare class JsonI18n {
    /** 加载翻译数据目录 */
    constructor(
        /** 目录 */
        path: string,
        /** 默认语言 */
        localLangCode: string | undefined
    );

    /** 加载所有语言 */
    loadAllLanguage(): void;

    /** 加载语言 */
    loadLanguage(
        /** 语言标识符 */
        langCode: string,
        /** 默认数据 */
        defaultData: object | undefined
    ): void;

    /** 设置语言 */
    chooseLanguage(
        /** 语言标识符 */
        langCode: string
    ): void;

    /** 设置默认语言 */
    setDefaultLanguage(
        /** 语言标识符 */
        langCode: string
    ): void;

    /** 翻译键名 */
    translate(
        /** 键名 */
        key: string,
        /** 替换参数 */
        data: string[],
        /** 语言标识符 */
        langCode: string | undefined
    ): string;
}

/** 版本类 */
declare class Version {
    /** 创建版本对象 */
    constructor(
        /** 主版本号 */
        major: number,
        /** 次版本号 */
        minor: number,
        /** 修订版本号 */
        revision: number,
    );

    /** 转换成字符串 */
    toString(
        /** 是否添加前缀"v" */
        prefix: boolean | undefined
    ): string;

    /** 转换成数组 */
    toArray(): [number, number, number];

    /** 转换成数字 */
    valueOf(): number;

    /** 从字符串中创建版本对象 */
    static fromString(
        /** 字符串 */
        version: string
    ): Version;

    /** 从数组中创建版本对象 */
    static fromArray(
        /** 数组 */
        version: [number, number, number]
    ): Version;

    /** 检测LRCA版本是否大于或等于此版本 */
    static isPluginVersionMatched(
        /** 比较版本号 */
        version: Version
    );

    /** 获取LRCA版本对象 */
    static getLrcaVersion(): Version;

    /** 获取GMLIB版本对象 */
    static getGmlibVersion(): Version;
}

declare class I18nAPI {
    private constructor();

    /** 获取键翻译 */
    static get(
        /** 键名 */
        key: string,
        /** 翻译参数 */
        params: string[] | undefined,
        /** 语言标识符 */
        langCode: string | undefined
    ): string;

    /** 获取键翻译 */
    static translate(
        /** 键名 */
        key: string,
        /** 翻译参数 */
        params: string[] | undefined,
        /** 语言标识符 */
        langCode: string | undefined
    ): string;

    /** 获取支持的语言标识符 */
    static getSupportedLanguages(): string[];

    /** 获取资源包默认语言 */
    static getCurrentLanguage(): string;

    /** 设置资源包默认语言 */
    static chooseLanguage(
        /** 要设置的语言标识符 */
        language: string
    ): void;

    /** 加载语言数据 */
    static loadLanguage(
        /** 语言数据 */
        code: string,
        /** 语言标识符 */
        language: string
    ): void;

    /** 更新或创建语言文件 */
    static updateOrCreateLanguageFile(
        /** 语言数据 */
        code: string,
        /** 语言标识符 */
        language: string,
        /** 文件路径 */
        path: string
    ): void;

    /** 加载语言目录 */
    static loadLanguageDirectory(
        /** 语言数据目录 */
        path: string
    ): void;
}

declare class UserCache {
    private constructor();

    /** 根据uuid查xuid */
    static getXuidByUuid(
        /** uuid */
        uuid: string
    ): string;

    /** 根据xuid查uuid */
    static getUuidByXuid(
        /** xuid */
        xuid: string
    ): string;

    /** 根据xuid查玩家名 */
    static getNameByUuid(
        /** xuid */
        xuid: string
    ): string;

    /** 根据xuid查玩家名 */
    static getNameByXuid(
        /** xuid */
        xuid: string
    ): string;

    /** 根据玩家名查xuid */
    static getXuidByName(
        /** 玩家名 */
        name: string
    ): string;

    /** 根据玩家名查uuid */
    static getUuidByName(
        /** 玩家名 */
        name: string
    ): string;

    /** 获取玩家信息 */
    static getPlayerInfo(
        /** 玩家名 或 xuid 或 uuid */
        playerIdentifier: string
    ): { Xuid: String, Uuid: string, Name: string } | null;

    /** 获取所有玩家信息 */
    static getAllPlayerInfo(): { Xuid: String; Uuid: string; Name: string; }[]
}

interface Player {
    /** (GMLIB)转换成实体对象 */
    toEntity(): Entity;

    /** (GMLIB)获取玩家重生坐标 */
    getSpawnPoint(): IntPos;

    /** (GMLIB)设置玩家重生坐标 */
    setSpawnPoint(
        /** 要设置的坐标对象 */
        pos: IntPos
    ): void;

    /** (GMLIB)清除玩家重生点 */
    clearSpawnPoint(): void;

    /** 丢出玩家物品 */
    dropItem(
        /** 物品对象 */
        item: Item,
        /** 随机丢出位置 */
        randomly: boolean | undefined
    ): boolean;
}

interface Entity {
    /** (GMLIB)射弹投射物 */
    shootProjectile(
        /** 投射物命名空间 */
        proj: string,
        /** 速度 */
        speed: number | undefined,
        /** 偏移量 */
        offset: number | undefined
    ): boolean;

    /** (GMLIB)投掷实体 */
    throwEntity(
        /** 投掷的实体对象 */
        proj: Entity,
        /** 速度 */
        speed: number | undefined,
        /** 偏移量 */
        offset: number | undefined
    ): boolean;

    /** (GMLIB)获取实体翻译键名 */
    getTranslateKey(): string;

    /** (GMLIB)获取实体名字翻译 */
    getTranslateName(
        /** 要翻译的语言 */
        langCode: string
    ): string;

    /** (GMLIB)使玩家攻击实体 */
    attack(
        /** 攻击的实体对象 */
        entity: Entity
    ): boolean;

    /** (GMLIB) */
    pullInEntity(
        /** 实体对象 */
        entity: Entity
    ): boolean;
}

interface Block {
    /** (GMLIB)获取方块翻译键名 */
    getTranslateKey(): string;

    /** (GMLIB)获取方块名字翻译 */
    getTranslateName(
        /** 要翻译的语言 */
        langCode: string
    ): string;

    /** (GMLIB)获取方块硬度 */
    getBlockDestroySpeed(): number;

    /** (GMLIB)使方块被玩家挖掘 */
    playerDestroy(
        /** 挖掘的玩家对象 */
        player: Player
    ): void;

    /** (GMLIB) */
    canDropWithAnyTool(): boolean;

    /** (GMLIB)方块是否不需要工具采集 */
    isAlwaysDestroyable(): boolean;

    /** (GMLIB)检测方块是否能被玩家挖掘(比如插件拦截) */
    playerWillDestroy(
        /** 挖掘的玩家对象 */
        player: Player
    ): boolean;
}

interface Item {
    /** (GMLIB)获取方块翻译键名 */
    getTranslateKey(): string;

    /** (GMLIB)获取方块名字翻译 */
    getTranslateName(
        /** 要翻译的语言 */
        langCode: string
    ): string;

    /** (GMLIB)获取物品挖掘方块速度 */
    getDestroyBlockSpeed(
        /** 挖掘的方块对象 */
        block: Block
    ): number;

    /** (GMLIB)物品冒险模式下是否可以挖掘方块 */
    canDestroy(
        /** 挖掘的方块对象 */
        block: Block
    ): boolean;

    /** (GMLIB)物品是否能破坏方块 */
    canDestroyInCreative(): boolean;

    /** (GMLIB)物品是否可以采集方块 */
    canDestroySpecial(
        /** 挖掘的方块对象 */
        block: Block
    ): boolean;

    /** 获取物品可以拥有的附魔 */
    getLegalEnchants(): string[]

    /** 添加附魔 */
    applyEnchant(
        /** 附魔的命名空间 */
        typeName: string,
        /** 附魔等级 */
        level: number,
        /** 允许非原版附魔 */
        allowNonVanilla: boolean | null
    ): boolean;

    /** 删除所有附魔 */
    removeEnchants(): void;

    /** 判断是否拥有附魔 */
    hasEnchant(
        /** 附魔的命名空间 */
        typeName: string
    ): boolean;

    /** 获取附魔等级 */
    getEnchantLevel(
        /** 附魔的命名空间 */
        typeName: string
    ): number;
}