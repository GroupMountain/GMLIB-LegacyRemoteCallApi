/// <reference path="d:\dts/dts/helperlib/src/index.d.ts"/> 

/** 事件监听接口 */
declare class Event {
    /** 生物捡起物品 */
    static listen(
        /** 事件名 */
        event: "onMobDie",
        /** 监听函数 */
        listener: (
            /** 尝试捡起物品的实体对象 */
            entity: Entity,
            /** 掉落物实体对象 */
            itemEntity: Entity
        ) => boolean | void
    ): boolean;

    /** 客户端登录后事件(不可以拦截) */
    static listen(
        /** 事件名 */
        event: "onClientLogin",
        /** 监听函数 */
        listener: (
            /** 玩家的游戏名字 */
            realName: string,
            /** 玩家的uuid */
            uuid: string,
            /** 玩家在服务端的xuid */
            serverXuid: string,
            /** 玩家在客户端的xuid */
            clientXuid: string
        ) => void
    ): boolean;

    /** 天气改变事件事件 */
    static listen(
        /** 事件名 */
        event: "onWeatherChange",
        /** 监听函数 */
        listener: (
            /** 雷暴天气等级 */
            lightningLevel: number,
            /** 雨天天气等级 */
            rainLevel: number,
            /** 雷暴持续时间（刻） */
            lightningLastTick: number,
            /** 雨天持续时间(刻) */
            rainingLastTick: number
        ) => boolean | void
    ): boolean;

    /** 掉落物尝试生成 */
    static listen(
        event: "onItemTrySpawn",
        listener: (
            /** 物品对象 */
            item: Item,
            /** 尝试生成的坐标对象 */
            pos: FloatPos,
            /** 创建掉落物的实体对象 */
            spawnerEntity: Entity
        ) => boolean | void
    ): boolean;

    /** 掉落物生成完毕(不可以拦截) */
    static listen(
        /** 事件名 */
        event: "onItemTrySpawn",
        /** 回调函数 */
        listener: (
            /** 物品对象 */
            item: Item,
            /** 掉落物实体对象 */
            entity: Entity,
            /** 实体生成的坐标 */
            pos: FloatPos,
            /** 创建掉落物的实体对象 */
            spawnerEntity: Entity
        ) => void
    ): boolean;

    /** 实体切换维度 */
    static listen(
        /** 事件名 */
        event: "onEntityChangeDim",
        /** 回调函数 */
        listener: (
            /** 切换维度的实体对象 */
            entity: Entity,
            /** 前往到的维度ID */
            dimid: number
        ) => boolean | void
    ): boolean;

    /** 实体切换维度后(不可拦截) */
    static listen(
        /** 事件名 */
        event: "onEntityChangeDimAfter",
        /** 回调函数 */
        listener: (
            /** 切换维度的实体对象 */
            entity: Entity,
            /** 前往到的维度ID */
            fromDimid: number
        ) => void
    ): boolean;

    /** 玩家下床 */
    static listen(
        /** 事件名 */
        event: "onLeaveBed",
        /** 回调函数 */
        listener: (
            /** 下床的玩家对象 */
            player: Player
        ) => boolean | void
    ): boolean;

    /** 触发死亡信息(不可以拦截) */
    static listen(
        /** 事件名 */
        event: "onDeathMessage",
        /** 回调函数 */
        listener: (
            /** 死亡信息键名 */
            deathMsgKey: string,
            /** 死亡信息翻译参数 */
            deathMsgParams: Array.<string>,
            /** 死亡实体的实体对象 */
            entity: Entity
        ) => void
    ): boolean;

    /** 实体受伤后事件 */
    static listen(
        /** 事件名 */
        event: "onMobHurted",
        /** 回调函数 */
        listener: (
            /** 受伤的实体对象 */
            entity: Entity,
            /** 造成伤害的实体对象 */
            source: Entity,
            /** 伤害值 */
            damage: number,
            /** 伤害类型 */
            cause: number
        ) => void
    ): boolean;

    /** 末影人搬起方块 */
    static listen(
        /** 事件名 */
        event: "onEndermanTake",
        /** 回调函数 */
        listener: (
            /** 末影人实体对象 */
            entity: Entity
        ) => boolean | void
    ): boolean;

    /** 末影龙重生事件 */
    static listen(
        /** 事件名 */
        event: "DragonRespawn",
        /** 回调函数 */
        listener: (
            /** 末影龙重生后的UniqueID */
            uniqueID: number
        ) => boolean | void
    ): boolean;

    /** 弹射物实体尝试创建 */
    static listen(
        /** 事件名 */
        event: "ProjectileTryCreate",
        /** 回调函数 */
        listener: (
            /** 弹射物实体对象 */
            entity: Entity,
            /** 创建弹射的实体的uniqueID */
            uniqueId: number
        ) => boolean | void
    ): boolean;

    /** 弹射物实体成功后(不可拦截) */
    static listen(
        /** 事件名 */
        event: "ProjectileCreate",
        /** 回调函数 */
        listener: (
            /** 弹射物实体对象 */
            entity: Entity,
            /** 创建弹射的实体的uniqueID */
            uniqueId: number
        ) => void
    ): boolean;

    /** 生成流浪商人 */
    static listen(
        /** 事件名 */
        event: "SpawnWanderingTrader",
        /** 回调函数 */
        listener: (
            /** 生成的坐标 */
            pos: IntPos
        ) => boolean | void
    ): boolean;

    /** 处理物品请求 */
    static listen(
        /** 事件名 */
        event: "HandleRequestAction",
        /** 回调函数 */
        listener: (
            /** 请求玩家 */
            player: Player,
            /** 请求类型 */
            actionType: string,
            /** 容器ID */
            ContainerNetId: string,
            /** 请求的槽位 */
            slot: number
        ) => boolean | void
    ): boolean;
}
