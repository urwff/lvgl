#include "src/core/device_manager.h"
#include <stdio.h>

int main(void) {
    // 初始化设备管理器
    if (device_manager_init() != 0) {
        printf("设备管理器初始化失败\n");
        return -1;
    }
    
    // 获取所有设备
    device_info_t *devices;
    uint32_t count;
    device_manager_get_all(&devices, &count);
    
    printf("找到 %d 个设备\n", count);
    for (uint32_t i = 0; i < count; i++) {
        printf("- %s (ID: %d, 类型: %d)\n", 
               devices[i].name, 
               devices[i].id,
               devices[i].type);
    }
    
    // 测试设备控制
    if (count > 0) {
        printf("\n测试控制第一个设备...\n");
        device_manager_control(devices[0].id, true, 80);
    }
    
    return 0;
}