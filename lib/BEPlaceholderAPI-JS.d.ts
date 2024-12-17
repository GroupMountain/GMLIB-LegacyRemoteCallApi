export class PAPI {
    /** 注册一个玩家PAPI变量 */
    static registerPlayerPlaceholder(
        /** PAPI调用函数 */
        func: (
            /** 玩家对象 */
            player: Player,
            /** 变量参数 */
            param: null | object.<string, string>
        ) => string,
        /** 插件名字 */
        pluginsName: string,
        /** PAPI变量 */
        PAPIName: string
    ): boolean;

    /** 注册一个服务器PAPI变量 */
    static registerServerPlaceholder(
        /** PAPI调用函数 */
        func: (
            /** 变量参数 */
            param: null | object.<string, string>
        ) => string,
        /** 插件名字 */
        pluginsName: string,
        /** PAPI变量 */
        PAPIName: string
    ): boolean;

    /** 注册一个静态PAPI变量 */
    static registerStaticPlaceholder(
        /** PAPI调用函数 */
        func: () => string,
        /** 插件名字 */
        pluginsName: string,
        /** PAPI变量 */
        PAPIName: string,
        /** 更新时间 */
        UpdateInterval: number
    ): boolean;

    /** 获取一个服务器变量的值 */
    static getValue(
        /** PAPI名 */
        key: string
    ): string;

    /** 获取一个玩家变量的值 */
    static getValueByPlayer(
        /** PAPI名 */
        key: string,
        /** 玩家对象 */
        pl: Player
    ): string;

    /** 翻译带PAPI变量的字符串 */
    static translateString(
        /** 要翻译的字符串 */
        str: string,
        /** 玩家对象 */
        pl: Player | undefined
    ): string;

    /** 注销一个PAPI变量 */
    static unRegisterPlaceholder(
        /** PAPI名 */
        str: string
    ): boolean;

    /** 获取所有已注册的PAPI变量 */
    static getAllPAPI(): string[];
}
