# API说明(未测试)

## Uart类

### init

```c
/**
 * @brief 选择uart端口号
 * 
 * @param uart_num uart端口号{UART_NUM_0,UART_NUM_1.....}
 */
void Uart::init(uart_port_t uart_num)
```

内容

1. 先判断该端口是否使用如删除,`uart_is_driver_installed()`
2. `uart_param_config` 配置uart相关设置
3. `uart_driver_install`,配置缓存区大小

 

### set_pin

```c
/**
 * @brief 分配给 GPIO 引脚。
 * 
 * @param UART_TXD  TX 引脚 GPIO 编号。
 * @param UART_RXD  RX 引脚 GPIO 编号
 * @param UART_RTS  RTS 引脚 GPIO 编号
 * @param UART_CTS CTS 引脚 GPIO 编号
 */
void Uart::set_pin(int UART_TXD, int UART_RXD, int UART_RTS=-1, int UART_CTS=-1)
```

内容

1. uart_set_pin()设置引脚(-1代表未使用)

### send_data

```c
/**
 * @brief 发送数据
 * 
 * @param data 数据内容
 * @param TAG 调试输出(方便调试)
 */
void Uart::send_data(const char *data,const char *TAG= "uart")
```
内容

### create_receive_task

```c
/**
 * @brief 创建一个接收任务
 * 
 * @param uart 自己new的类
 * @param Priority 优先级
 */
void Uart::create_receive_task(void* uart,unsigned int Priority)
```

### uart_delete
```c
/**
 * @brief 清除uart
 * 
 */
void Uart::uart_delete()
```

# 变量结构体说明

## Uart类

### 宏定义(可根据个人修改)
```c
```

### 变量



# 待补充

对于任务(task)中创建,删除还需学习完善
