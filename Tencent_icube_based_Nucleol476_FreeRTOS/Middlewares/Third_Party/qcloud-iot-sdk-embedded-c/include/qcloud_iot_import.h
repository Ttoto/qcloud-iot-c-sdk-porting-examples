/*
 * Tencent is pleased to support the open source community by making IoT Hub available.
 * Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

 * Licensed under the MIT License (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://opensource.org/licenses/MIT

 * Unless required by applicable law or agreed to in writing, software distributed under the License is
 * distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef QCLOUD_IOT_IMPORT_H_
#define QCLOUD_IOT_IMPORT_H_
#if defined(__cplusplus)
extern "C" {
#endif

#include "config.h"
#include "platform.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <inttypes.h>

#define _IN_            /* 表明这是一个输入参数. */
#define _OU_            /* 表明这是一个输出参数. */

#define IOT_TRUE    (1)     /* indicate boolean value true */
#define IOT_FALSE   (0)     /* indicate boolean value false */

#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))

typedef enum _eHostType_{
	eHOST_MQTT = 0,
	eHOST_COAP = 1,
	eHOST_LOG_HTTP = 2,
	eHOST_LOG_PORT = 3,	
}eHostType;

/**
 * @brief 创建线程
 *
 * @param thread_t   线程句柄
 * @param stack_size 线程栈大小
 * @param priority	 线程优先级
 * @param fn		 线程入口函数
 * @param arg		 相关参数
 * @return 创建失败返回NULL，成功返回指针
 */
void * HAL_ThreadCreate(uint16_t stack_size, int priority, void *(*fn)(void*), void* arg);

/**
 * @brief 销毁线程
 *
 * @return 销毁失败返回QCLOUD_ERR_FAILURE，成功返回QCLOUD_ERR_SUCCESS
 */
int HAL_ThreadDestroy(void *thread_t);

/**
 * @brief 创建信号量
 *
 * @return 创建失败返回NULL，成功返回信号量句柄
 */
void *HAL_SemaphoreCreate(void);

/**
 * @brief 销毁信号量
 * @param 信号量句柄
 */
void HAL_SemaphoreDestroy(void *sem);

/**
 * @brief 发送信号量
 * @param 信号量句柄
 */
void HAL_SemaphorePost(void *sem);

/**
 * @brief 等待信号量
 * @param 信号量句柄
 * @param 超时时间
 * @return 失败返回QCLOUD_ERR_FAILURE，成功返回QCLOUD_ERR_SUCCESS
 */
int HAL_SemaphoreWait(void *sem, uint32_t timeout_ms);

/**
 * @brief 创建互斥锁
 *
 * @return 创建失败返回NULL，成功返回Mutex指针
 */
void *HAL_MutexCreate(void);

/**
 * @brief 销毁互斥锁
 *
 * @param Mutex指针
 */
void HAL_MutexDestroy(_IN_ void *mutex);

/**
 * @brief 阻塞式加锁
 *
 * @param Mutex指针
 */
void HAL_MutexLock(_IN_ void *mutex);

/**
 * @brief 非阻塞式加锁
 *
 * @param Mutex指针
 * @return 如果成功拿到锁，则返回0，否则返回错误值
 */
int HAL_MutexTryLock(_IN_ void *mutex);

/**
 * @brief 释放锁
 *
 * @param Mutex指针
 */
void HAL_MutexUnlock(_IN_ void *mutex);

/**
 * @brief 分配一块的内存，返回一个指向块开始的指针.
 *
 * @param size   用字节指定块大小.
 * @return       一个指向block开头的指针.
 */
void *HAL_Malloc(_IN_ uint32_t size);

/**
 * @brief 释放内存块
 *
 * @param ptr   指向先前分配给平台malloc的内存块的指针.
 */
void HAL_Free(_IN_ void *ptr);

/**
 * @brief 将格式化的数据写入标准输出流中.
 *
 * @param fmt   要写入的文本的字符串, 它可以选择包含嵌入的格式指定符, 它指定了随后的参数如何转换为输出.
 * @param ...   变量参数列表.
 */
void HAL_Printf(_IN_ const char *fmt, ...);

/**
 * @brief 将格式化的数据写入字符串.
 *
 * @param str   目标字符串.
 * @param len   将被写入字符的最大长度
 * @param fmt   要编写的文本的格式，它可以选择包含嵌入的格式指定符, 它指定了随后的参数如何转换为输出.
 * @param ...   变量参数列表，用于格式化并插入到生成的字符串中，替换它们各自的指定符.
 * @return      成功写入字符串的字节数.
 */
int HAL_Snprintf(_IN_ char *str, const int len, const char *fmt, ...);

/**
 * @brief 将格式化的数据写入字符串.
 *
 * @param [out] str: 目标字符串.
 * @param [in] len: 将被写入字符的最大长度.
 * @param [in] fmt: 要编写的文本的格式.
 * @param [in] ap:  参数列表.
 * @return 成功写入字符串的字节数.
 */
int HAL_Vsnprintf(_OU_ char *str, _IN_ const int len, _IN_ const char *fmt, _IN_ va_list ap);

/**
 * @brief 检索自系统启动以来已运行的毫秒数.
 *
 * @return 返回毫秒数.
 */
uint32_t HAL_UptimeMs(void);


/**
 * @brief 阻塞延时，单位毫秒.
 *
 */

void HAL_DelayMs(_IN_ uint32_t ms);


/**
 * @brief 休眠.
 *
 * @param ms 休眠的时长, 单位毫秒.
 */
void HAL_SleepMs(_IN_ uint32_t ms);

/**
 * @brief 获取产品ID.
 *
 * @param pProductId 读取产品ID的存放buff
 * @param maxlen 	 buff长度
 * @return          返回QCLOUD_ERR_SUCCESS, 表示读取成功，否则读取失败
 */
int HAL_GetProductID(char *pProductId, uint8_t maxlen);	

/**
 * @brief 获取产品密钥，动态设备注册需要.
 *
 * @param pProductKey 读取产品Key的存放buff
 * @param maxlen 	 buff长度
 * @return          返回QCLOUD_ERR_SUCCESS, 表示读取成功，否则读取失败
 */
int HAL_GetProductKey(char *pProductKey, uint8_t maxlen);

/**
 * @brief 获取设备名，若动态设备注册使能，且未注册，需要实现设备名的生成方法.
 *
 * @param pDevName  读取设备名的存放buff
 * @param maxlen 	buff长度
 * @return          返回QCLOUD_ERR_SUCCESS, 表示读取成功，否则读取失败
 */
int HAL_GetDevName(char *pDevName, uint8_t maxlen);

/**
 * @brief 设置产品ID
 *
 * @param pProductId  待设置的产品ID
 * @return            返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_SetProductID(const char *pProductId);

/**
 * @brief 设置产品Key
 *
 * @param pProductKey  待设置的产品Key
 * @return             返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_SetProductKey(const char *pProductKey);

/**
 * @brief 设置设备名
 *
 * @param pDevName  待设置的设备名
 * @return          返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_SetDevName(const char *pDevName);
#ifdef AUTH_MODE_CERT
/**
 * @brief 获取设备端证书文件名
 *
 * @param pDevCert  证书文件名的存放buff
 * @param maxlen 	buff长度
 * @return          返回QCLOUD_ERR_SUCCESS, 表示读取成功，否则读取失败
 */
int HAL_GetDevCertName(char *pDevCert, uint8_t maxlen);

/**
 * @brief 获取设备端证书文件名
 *
 * @param pDevPrivateKey  证书文件名的存放buff
 * @param maxlen 		buff长度
 * @return          返回QCLOUD_ERR_SUCCESS, 表示读取成功，否则读取失败
 */

int HAL_GetDevPrivateKeyName(char *pDevPrivateKey, uint8_t maxlen);

/**
 * @brief 设置设备端证书文件名
 *
 * @param pDevCert  待设置的设备端证书文件名
 * @return          返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_SetDevCertName(char *pDevCert);

/**
 * @brief 设置设备私钥文件名
 *
 * @param pDevPrivateKey  待设置的设备私钥文件名
 * @return          返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_SetDevPrivateKeyName(char *pDevPrivateKey);
#else
/**
 * @brief 获取设备psk，TLS PSK认证方式
 *
 * @param pDevSec  待设置的设备psk
 * @return         返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_GetDevSec(char *pDevSec, uint8_t maxlen);

/**
 * @brief 设置设备psk
 *
 * @param pDevSec  待设置的设备psk
 * @return         返回QCLOUD_ERR_SUCCESS, 表示设置成功，否则设置失败
 */
int HAL_SetDevSec(const char *pDevSec);
#endif

/**
 * @brief 获取设备信息
 *
 * @param devInfo  待获取的设备信息指针
 * @return         返回QCLOUD_ERR_SUCCESS, 表示获取成功，否则获取失败
 */

int HAL_GetDevInfo(void *devInfo);


/**
 * 定义特定平台下的一个定时器结构体,
 */
struct Timer {
#if defined(__linux__) && defined(__GLIBC__)
	struct timeval end_time;
#else
	uintptr_t end_time;
#endif
};

typedef struct Timer Timer;

/**
 * @brief 获取系统ms时间戳
 *
 * @return   返回ms时间戳
 */
uint32_t HAL_GetTimeMs(void);

/**
 * @brief 判断定时器时间是否已经过期
 *
 * @param timer     定时器结构体
 * @return          返回true, 表示定时器已过期
 */
bool HAL_Timer_expired(Timer *timer);


/**
 * @brief 根据定时器开始计时, 单位:ms
 *
 * @param timer         定时器结构体
 * @param timeout_ms    超时时间, 单位:ms
 */
void HAL_Timer_countdown_ms(Timer *timer, unsigned int timeout_ms);

/**
 * @brief 根据定时器开始计时, 单位:ms
 *
 * @param timer   定时器结构体
 * @param timeout 超时时间, 单位:s
 */
void HAL_Timer_countdown(Timer *timer, unsigned int timeout);

/**
 * @brief 检查给定定时器还剩下多少时间
 *
 * @param timer     定时器结构体
 * @return          返回剩余时间
 */
int HAL_Timer_remain(Timer *timer);

/**
 * @brief 初始化定时器结构体
 *
 * @param timer 定时器结构体
 */
void HAL_Timer_init(Timer *timer);

/**
 * @brief 获取当前时间格式化字符串 %Y-%m-%d %z %H:%M:%S
 *
 * @return 当前时间格式化字符串
 */
char* HAL_Timer_current(void);

/**
 * @brief 获取当前时间秒数
 *
 * @return 当前时间的秒级类型
 */
long HAL_Timer_current_sec(void);

#ifdef AT_TCP_ENABLED
int HAL_AT_TCP_Init(void);
uintptr_t HAL_AT_TCP_Connect(const char *host, uint16_t port);
int HAL_AT_TCP_Disconnect(uintptr_t fd);
int HAL_AT_TCP_Write(uintptr_t fd, const unsigned char *buf, uint32_t len, uint32_t timeout_ms, size_t *written_len);	
int HAL_AT_TCP_Read(uintptr_t fd, uint8_t *buf, uint32_t len, uint32_t timeout_ms, uint32_t *read_len);
int at_device_init(void);
int HAL_AT_Uart_Init(void);
int HAL_AT_Uart_Deinit(void);
int HAL_AT_Uart_Send(void *data, uint32_t size);
int HAL_AT_Uart_Recv(void *data, uint32_t expect_size, uint32_t *recv_size, uint32_t timeout);

int at_device_init(void);
#endif

#ifndef AUTH_WITH_NOTLS
/**
 * @brief TLS连接相关参数定义
 *
 * 在初始化时, 必须要将ca证书、客户端证书、客户端私钥文件及服务器域名带上来
 */
typedef struct {
    const char		 *ca_crt;
    uint16_t 		 ca_crt_len;

#ifdef AUTH_MODE_CERT
	/**
	 * 非对称加密
	 */
    const char       *cert_file;            // 客户端证书
    const char       *key_file;             // 客户端私钥
#else
    /**
     * 对称加密
     */
    const char       *psk;                  // 对称加密密钥
    const char       *psk_id;               // psk密钥ID
#endif

    size_t           psk_length;            // psk长度

    unsigned int     timeout_ms;            // SSL握手超时时间

} SSLConnectParams;

/********** TLS network **********/
typedef SSLConnectParams TLSConnectParams;

/**
 * @brief 为MQTT客户端建立TLS连接
 *
 * 主要步骤如下:
 *     1. 初始化工作, 例如mbedtls库初始化, 相关证书文件加载等
 *     2. 建立TCP socket连接
 *     3. 建立SSL连接, 包括握手, 服务器证书检查等
 *
 * @param   pConnectParams TLS连接初始化参数
 * @host    连接域名
 * @port    连接端口
 * @return  返回0 表示TLS连接成功
 */
uintptr_t HAL_TLS_Connect(TLSConnectParams *pConnectParams, const char *host, int port);

/**
 * @brief 断开TLS连接, 并释放相关对象资源
 *
 * @param pParams TLS连接参数
 */
void HAL_TLS_Disconnect(uintptr_t handle);

/**
 * @brief 通过TLS连接写数据
 *
 * @param handle        TLS连接相关数据结构
 * @param data          写入数据
 * @param totalLen      写入数据长度
 * @param timeout_ms    超时时间, 单位:ms
 * @param written_len   已写入数据长度
 * @return              若写数据成功, 则返回写入数据的长度
 */
int HAL_TLS_Write(uintptr_t handle, unsigned char *data, size_t totalLen, uint32_t timeout_ms,
                                 size_t *written_len);

/**
 * @brief 通过TLS连接读数据
 *
 * @param handle        TLS连接相关数据结构
 * @param data          读取数据
 * @param totalLen      读取数据的长度
 * @param timeout_ms    超时时间, 单位:ms
 * @param read_len      已读取数据的长度
 * @return              若读数据成功, 则返回读取数据的长度
 */
int HAL_TLS_Read(uintptr_t handle, unsigned char *data, size_t totalLen, uint32_t timeout_ms,
                                size_t *read_len);

/********** TCP network **********/
/**
 * @brief 为MQTT客户端建立TCP连接
 *
 * @host	连接域名
 * @port	连接端口
 * @return	返回0 表示TCP连接失败；返回 > 0 表示TCP连接描述符FD值
 */
uintptr_t HAL_TCP_Connect(const char *host, uint16_t port);

/**
 * @brief 断开TCP连接
 *
 * @param fd TCP Socket描述符
 * @return	返回0 表示TCP断连成功
 */
int HAL_TCP_Disconnect(uintptr_t fd);

/**
 * @brief 通过TCP Socket写数据
 *
 * @param fd				TCP Socket描述符
 * @param buf				写入数据
 * @param len				写入数据长度
 * @param timeout_ms		超时时间
 * @param written_len		已写入数据长度
 * @return					若写数据成功, 则返回写入数据的长度
 */
int HAL_TCP_Write(uintptr_t fd, const unsigned char *buf, uint32_t len, uint32_t timeout_ms,
				size_t *written_len);

/**
 * @brief 通过TCP Socket读数据
 *
 * @param fd				TCP Socket描述符
 * @param buf				读入数据
 * @param len				读入数据长度
 * @param timeout_ms		超时时间
 * @param written_len		已读入数据长度
 * @return					若读数据成功, 则返回读入数据的长度
 */
int HAL_TCP_Read(uintptr_t fd, unsigned char *buf, uint32_t len, uint32_t timeout_ms,
				size_t *read_len);



/********** DTLS network **********/
#ifdef COAP_COMM_ENABLED
typedef SSLConnectParams DTLSConnectParams;

/**
 * @brief 为CoAP客户端建立DTLS连接
 *
 * 主要步骤如下:
 *     1. 初始化工作, 例如mbedtls库初始化, 相关证书文件加载等
 *     2. 建立UDP socket连接
 *     3. 建立SSL连接, 包括握手, 服务器证书检查等
 *
 * @param pConnectParams DTLS连接初始化参数
 * @host    连接域名
 * @port    连接端口
 * @return  返回0 表示DTLS连接成功
 */
uintptr_t HAL_DTLS_Connect(DTLSConnectParams *pConnectParams, const char *host, int port);

/**
 * @brief 断开DTLS连接
 *
 * @param handle DTLS连接相关数据结构
 * @return  返回0 表示DTLS断连
 */
void HAL_DTLS_Disconnect(uintptr_t handle);

/**
 * @brief 通过DTLS连接写数据
 *
 * @param pParams           DTLS连接相关数据结构
 * @param data              写入数据
 * @param datalen           写入数据长度
 * @param written_len       已写入数据长度
 * @return                  若写数据成功, 则返回写入数据的长度
 */
int HAL_DTLS_Write(uintptr_t handle, const unsigned char *data, size_t datalen, size_t *written_len);

/**
 * @brief 通过DTLS连接读数据
 *
 * @param handle            DTLS连接相关数据结构
 * @param data              读取数据
 * @param timeout_ms        超时时间, 单位:ms
 * @param datalen   	    读取数据的长度
 * @param read_len          已读取数据的长度
 * @return                  若读数据成功, 则返回读取数据的长度
 */
int HAL_DTLS_Read(uintptr_t handle, unsigned char *data, size_t datalen, uint32_t timeout_ms,
                  size_t *read_len);

#endif //CoAP Enabled

#else
/********** TCP network **********/
/**
 * @brief 为MQTT客户端建立TCP连接
 *
 * @host    连接域名
 * @port    连接端口
 * @return  返回0 表示TCP连接失败；返回 > 0 表示TCP连接描述符FD值
 */
uintptr_t HAL_TCP_Connect(const char *host, uint16_t port);

/**
 * @brief 断开TCP连接
 *
 * @param fd TCP Socket描述符
 * @return  返回0 表示TCP断连成功
 */
int HAL_TCP_Disconnect(uintptr_t fd);

/**
 * @brief 通过TCP Socket写数据
 *
 * @param fd           		TCP Socket描述符
 * @param buf              	写入数据
 * @param len           	写入数据长度
 * @param timeout_ms		超时时间
 * @param written_len       已写入数据长度
 * @return                  若写数据成功, 则返回写入数据的长度
 */
int HAL_TCP_Write(uintptr_t fd, const unsigned char *buf, uint32_t len, uint32_t timeout_ms,
                size_t *written_len);

/**
 * @brief 通过TCP Socket读数据
 *
 * @param fd           		TCP Socket描述符
 * @param buf              	读入数据
 * @param len           	读入数据长度
 * @param timeout_ms		超时时间
 * @param written_len       已读入数据长度
 * @return                  若读数据成功, 则返回读入数据的长度
 */
int HAL_TCP_Read(uintptr_t fd, unsigned char *buf, uint32_t len, uint32_t timeout_ms,
                size_t *read_len);

/********** UDP network **********/
#ifdef COAP_COMM_ENABLED
/**
 * @brief 建立UDP连接
 *
 * @host    连接域名
 * @port    连接端口
 * @return  返回0 表示UDP连接失败；返回 > 0 表示UDP连接描述符FD值
 */
uintptr_t HAL_UDP_Connect(const char *host, unsigned short port);

/**
 * @brief 断开UDP连接
 *
 * @param fd UDP Socket描述符
 * @return
 */
void HAL_UDP_Disconnect(uintptr_t fd);

/**
 * @brief 通过UDP Socket写数据
 *
 * @param fd           		UDP Socket描述符
 * @param buf              	写入数据
 * @param len           	写入数据长度
 * @return                  若写数据成功, 则返回写入数据的长度
 */
int HAL_UDP_Write(uintptr_t fd, const unsigned char *p_data, unsigned int datalen);

/**
 * @brief 通过TCP Socket读数据
 *
 * @param fd           		UDP Socket描述符
 * @param buf              	读入数据
 * @param len           	读入数据长度
 * @return                  若读数据成功, 则返回读入数据的长度
 */
int HAL_UDP_Read(uintptr_t fd, unsigned char *p_data, unsigned int datalen);

/**
 * @brief 通过TCP Socket读数据
 *
 * @param fd           		UDP Socket描述符
 * @param buf              	读入数据
 * @param len           	读入数据长度
 * @param timeout_ms		超时时间
 * @return                  若读数据成功, 则返回读入数据的长度
 */
int HAL_UDP_ReadTimeout(uintptr_t fd, unsigned char *p_data, unsigned int datalen, unsigned int timeout_ms);
#endif
#endif //NOTLS Enabled

#if defined(__cplusplus)
}
#endif
#endif  /* QCLOUD_IOT_IMPORT_H_ */

