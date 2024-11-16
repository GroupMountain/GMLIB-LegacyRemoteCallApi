export namespace Event {
    /** 事件优先级 */
    export enum EventPriority {
        /** 最高 */
        Highest = 0,
        /** 高 */
        High = 100,
        /** 正常(推荐) */
        Normal = 200,
        /** 低 */
        Low = 300,
        /** 最低 */
        Lowest = 400
    }

    /** 获取所有事件订阅 */
    export function getListener(): Record<string, number[]>;

    /** 获取事件订阅列表 */
    export function getListener(
        /** 事件名 */
        eventName:
            "ll::ServerStoppingEvent"
            | "gmlib::ClientLoginAfterEvent"
            | "gmlib::WeatherUpdateBeforeEvent"
            | "gmlib::MobPickupItemBeforeEvent"
            | "gmlib::ItemActorSpawnBeforeEvent"
            | "gmlib::ItemActorSpawnAfterEvent"
            | "gmlib::ActorChangeDimensionBeforeEvent"
            | "gmlib::PlayerStopSleepBeforeEvent"
            | "gmlib::DeathMessageAfterEvent"
            | "gmlib::MobHurtAfterEvent"
            | "gmlib::EndermanTakeBlockBeforeEvent"
            | "gmlib::ActorChangeDimensionAfterEvent"
            | "gmlib::DragonRespawnBeforeEvent"
            | "gmlib::ProjectileCreateBeforeEvent"
            | "gmlib::ProjectileCreateAfterEvent"
            | "gmlib::SpawnWanderingTraderBeforeEvent"
            | "gmlib::HandleRequestActionBeforeEvent"
            | "gmlib::ContainerClosePacketSendAfterEvent"
    ): number[];

    /** 订阅事件是否存在 */
    export function hasListener(
        /** 事件ID */
        eventId: number
    ): boolean;

    /** 取消事件订阅 */
    export function removeListener(
        /** 事件ID */
        eventId: number
    ): boolean;

    /** 获取订阅事件优先级 */
    export function getListenerPriority(
        /** 事件ID */
        eventId: number
    ): EventPriority | undefined;

    /** 设置事件异常处理回调 */
    export function setErrorHanlerCallback(
        /** 回调 */
        callback: (
            /** 错误 */
            error: Error,
            /** 事件名 */
            eventName: string,
            /** 事件ID */
            eventId: number,
            /** 插件名 */
            pluginName: string
        ) => void
    ): boolean;

    /** 监听事件(兼容旧版) */
    export function listen(
        /** 事件名 */
        eventName: "onServerStopping"
            | "onClientLogin"
            | "onWeatherChange"
            | "onMobPick"
            | "onItemTrySpawn"
            | "onItemSpawned"
            | "onEntityTryChangeDim"
            | "onLeaveBed"
            | "onDeathMessage"
            | "onMobHurted"
            | "onEndermanTake"
            | "onEntityChangeDim"
            | "onDragonRespawn"
            | "onProjectileTryCreate"
            | "onProjectileCreate"
            | "onSpawnWanderingTrader"
            | "onHandleRequestAction"
            | "onSendContainerClosePacket",
        /** 回调 */
        callback: Function
    ): boolean;

    /** 订阅事件 */
    export function emplaceListener(
        /** 事件名 */
        eventName: string,
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: any[],
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(服务器关闭事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "ll::ServerStoppingEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {},
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(客户端登录后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ClientLoginAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 玩家名 */
                0: string,
                /** 玩家uuid */
                1: string,
                /** 玩家服务端xuid */
                2: string,
                /** 玩家客户端xuid */
                3: string,
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(天气更新前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::WeatherUpdateBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 雨天等级 */
                0: number,
                /** 雨天时间(tick) */
                1: number,
                /** 暴雨等级 */
                2: number,
                /** 暴雨时间(tick) */
                3: number,
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(天气更新后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::WeatherUpdateAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 雨天等级 */
                0: number,
                /** 雨天时间(tick) */
                1: number,
                /** 暴雨等级 */
                2: number,
                /** 暴雨时间(tick) */
                3: number,
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(实体捡起物品前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::MobPickupItemBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 捡起物品的实体 */
                0: Entity,
                /** 掉落物 */
                1: Entity
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(实体捡起物品后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::MobPickupItemAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 捡起物品的实体 */
                0: Entity,
                /** 掉落物 */
                1: Entity
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(掉落物生成前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ItemActorSpawnBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 物品 */
                0: Item,
                /** 生成坐标坐标 */
                1: FloatPos,
                /** 生成此物品主人的uniqueId (-1为不存在) */
                2: number
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(掉落物生成后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ItemActorSpawnAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 物品 */
                0: Item,
                /** 生成坐标坐标 */
                1: FloatPos,
                /** 生成此物品主人的uniqueId (-1为不存在) */
                2: number
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(实体切换维度前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ActorChangeDimensionBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 切换维度的实体 */
                0: Entity,
                /** 前往的维度ID */
                1: number
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(事件切换维度后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ActorChangeDimensionAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 切换维度的实体 */
                0: Entity,
                /** 原来的维度ID */
                1: number,
                /** 前往的维度ID */
                2: number
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(玩家开始睡觉前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::PlayerStartSleepBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 睡觉的玩家 */
                0: Player,
                /** 床的坐标 */
                1: IntPos
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(玩家开始睡觉后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::PlayerStartSleepAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 睡觉的玩家 */
                0: Player,
                /** 床的坐标 */
                1: IntPos,
                /** 睡觉的结果 */
                2: number
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(玩家停止睡觉前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::PlayerStopSleepBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 睡觉的玩家 */
                0: Player,
                /** forcefulWakeUp */
                1: boolean,
                /** updateLevelList */
                2: boolean
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(玩家停止睡觉后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::PlayerStopSleepAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 睡觉的玩家 */
                0: Player,
                /** forcefulWakeUp */
                1: boolean,
                /** updateLevelList */
                2: boolean
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(生成死亡消息后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::DeathMessageAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 键名 */
                0: string,
                /** 翻译参数 */
                1: string[],
                /** 死亡的实体 */
                2: Entity
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(实体受伤后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::MobHurtAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 受伤的实体 */
                0: Entity,
                /** 伤害来源 */
                1: Entity,
                /** 伤害值 */
                2: number,
                /** 伤害类型 */
                3: DamageCause
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(末影人搬运方块前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::EndermanTakeBlockBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 末影人实体 */
                0: Entity
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(末影龙复活前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::DragonRespawnBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 末影龙复活后的uniqueId */
                0: number
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(末影龙复活后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::DragonRespawnAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 末影人实体 */
                0: Entity
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(投射物创建前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ProjectileCreateBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 投射物实体 */
                0: Entity,
                /** 创建投射物实体的uniqueId */
                1: number
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(投射物创建后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ProjectileCreateAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 投射物实体 */
                0: Entity,
                /** 创建投射物实体的uniqueId */
                1: number
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(生成流浪商人前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::SpawnWanderingTraderBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 出现的坐标 */
                0: IntPos
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(生成流浪商人后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::SpawnWanderingTraderAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 出现的坐标 */
                0: IntPos
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(处理物品请求前事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::HandleRequestActionBeforeEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 请求的玩家 */
                0: Player,
                /** 请求类型 */
                1: string,
                /** 请求数量 */
                2: number,
                /** 请求原容器类型 */
                3: string,
                /** 请求原容器槽位 */
                4: number,
                /** 请求前往的容器类型 */
                5: string,
                /** 请求前往的槽位 */
                6: number
            },
            /** 拦截事件 */
            cancel: () => void,
            /** 设置拦截状态 */
            setCancelled: (
                /** 是否拦截  */
                value: boolean
            ) => void,
            /** 是否被拦截 */
            isCancelled: () => boolean,
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(处理物品请求后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::HandleRequestActionAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 请求的玩家 */
                0: Player,
                /** 请求类型 */
                1: string,
                /** 请求数量 */
                2: number,
                /** 请求原容器类型 */
                3: string,
                /** 请求原容器槽位 */
                4: number,
                /** 请求前往的容器类型 */
                5: string,
                /** 请求前往的槽位 */
                6: number
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;

    /** 订阅事件(玩家关闭容器后事件) */
    export function emplaceListener(
        /** 事件名 */
        eventName: "gmlib::ContainerClosePacketSendAfterEvent",
        /** 回调 */
        callback: (event: {
            /** 事件参数 */
            params: {
                /** 关闭的玩家 */
                0: Player,
                /** 容器会话ID */
                1: number,
                /** 由服务器关闭 */
                2: boolean
            },
            /** 获取事件ID */
            getId: () => number,
            /** 获取事件类型 */
            getEventType: () => string
        }) => void,
        /** 优先级 */
        priority?: Event.EventPriority,
        /** 插件名 */
        pluginName?: string
    ): number;
}