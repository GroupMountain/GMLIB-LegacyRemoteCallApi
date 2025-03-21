/** 翻译带PAPI变量文本 */
export function translate(
    /** 要翻译的文本 */
    value: String,
    /** 实体对象 */
    actor?: Entity,
    /** 目标翻译语言 */
    language?: String
): String;

/** 注册PAPI变量 */
export function registerPlaceholder(
    /** papi变量 */
    placeholder: String,
    /** 回调 */
    callback: (
        /** 实体对象 */ actor: Entity,
        /** 参数 */ params: String[],
        /** 目标翻译语言 */language: String
    ) => String | undefined
): void;

/** 注销PAPI变量 */
export function unregisterPlaceholder(
    /** papi变量 */
    placeholder: String
): Boolean;

/** 根据模组名注销PAPI变量 */
export function unregisterPlaceholderFromModName(
    /** 模组名 */
    modName: String
): Boolean;

/** 获取一个papi变量的值 */
export function getValue(
    /** papi变量名 */
    placeholder: String,
    actor?: Entity,
    params?: Record<String, String>,
    language?: string
): Boolean;