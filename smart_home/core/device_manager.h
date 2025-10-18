#ifndef DEVICE_MANAGER_H
#define DEVICE_MANAGER_H

#include <stdint.h>
#include <stdbool.h>

// 设备类型
typedef enum {
    DEVICE_TYPE_LIGHT = 0,      // 灯光
    DEVICE_TYPE_AC,             // 空调
    DEVICE_TYPE_CURTAIN,        // 窗帘
    DEVICE_TYPE_LOCK,           // 门锁
    DEVICE_TYPE_SENSOR,         // 传感器
    DEVICE_TYPE_UNKNOWN
} device_type_t;

// 设备状态
typedef enum {
    DEVICE_STATUS_OFFLINE = 0,  // 离线
    DEVICE_STATUS_ONLINE,       // 在线
    DEVICE_STATUS_ERROR         // 故障
} device_status_t;

// 设备信息
typedef struct {
    uint32_t id;                // 设备ID
    char name[32];              // 设备名称
    device_type_t type;         // 设备类型
    device_status_t status;     // 设备状态
    uint32_t room_id;           // 所属房间ID
    bool is_on;                 // 开关状态
    int value;                  // 数值（亮度/温度等）
    char extra_data[128];       // 扩展数据（JSON格式）
} device_info_t;

// 设备回调函数
typedef void (*device_callback_t)(device_info_t *device, void *user_data);

/**
 * @brief 初始化设备管理器
 * @return 0:成功 -1:失败
 */
int device_manager_init(void);

/**
 * @brief 获取所有设备列表
 * @param devices 设备数组指针
 * @param count 返回设备数量
 * @return 0:成功 -1:失败
 */
int device_manager_get_all(device_info_t **devices, uint32_t *count);

/**
 * @brief 根据ID获取设备
 * @param id 设备ID
 * @return 设备指针，失败返回NULL
 */
device_info_t* device_manager_get_by_id(uint32_t id);

/**
 * @brief 根据房间ID获取设备列表
 * @param room_id 房间ID
 * @param devices 设备数组指针
 * @param count 返回设备数量
 * @return 0:成功 -1:失败
 */
int device_manager_get_by_room(uint32_t room_id, device_info_t **devices, uint32_t *count);

/**
 * @brief 控制设备
 * @param id 设备ID
 * @param is_on 开关状态
 * @param value 数值参数（可选）
 * @return 0:成功 -1:失败
 */
int device_manager_control(uint32_t id, bool is_on, int value);

/**
 * @brief 注册设备状态变化回调
 * @param callback 回调函数
 * @param user_data 用户数据
 * @return 0:成功 -1:失败
 */
int device_manager_register_callback(device_callback_t callback, void *user_data);

/**
 * @brief 更新设备状态（由MQTT/HTTP回调触发）
 * @param device 设备信息
 * @return 0:成功 -1:失败
 */
int device_manager_update_status(device_info_t *device);

#endif // DEVICE_MANAGER_H