#ifndef __UART_H__
#define __UART_H__

#ifdef __cplusplus
 extern "C" {
#endif


#define UART_DEBUG_EN               0u //���ڵ���ʹ��
#define DEBUG_INFO_PRINT_EN         0u //���Դ�ӡʹ��

#if (DEBUG_INFO_PRINT_EN > 0u)
#define DEBUG_WARN(s)         printf s
#define DEBUG_PRINT(s)        printf s
#else
#define DEBUG_WARN(s)
#define DEBUG_PRINT(s)           
#endif

#define CHECK_TIME_255B_2400      900u //2400bps��255�ֽڴ��䳬ʱʱ�䣬��λms
#define CHECK_TIME_255B_4800      500u //4800bps��255�ֽڴ��䳬ʱʱ�䣬��λms
#define CHECK_TIME_255B_9600      300u //9600bps��255�ֽڴ��䳬ʱʱ�䣬��λms
#define CHECK_TIME_255B_19200     200u //19200bps��255�ֽڴ��䳬ʱʱ�䣬��λms
#define CHECK_TIME_255B_38400      80u //38400bps��255�ֽڴ��䳬ʱʱ�䣬��λms
#define CHECK_TIME_255B_312500     10u //312500bps��255�ֽڴ��䳬ʱʱ�䣬��λms
#define MAX_SEND_PKT_CHECK_TIME      CHECK_TIME_255B_4800

#define MAX_UART_RECV_BUF_LEN       (24) //���ڽ��ջ���������
#define UART_RX_AF_THRESHOLD      0xfa //���ڽ�������
#define UART_TRANSMIT_TIMEOUT       (40 / (1000 / SYS_TICKS_PER_SEC)) //���ڷ��͡�����һ�ֽڵĳ�ʱʱ��
#define MAX_RECV_PKT_CHECK_TIME     (1000ul * 60) //60s

typedef struct {
    struct {                        //�������ݽṹ
        u16 *addr;                  //���ͻ�������ַ
        u16 bytes;                  //�����ֽ���
        bool completed;             //������ɱ�־
        u32 check_time;             //255�ֽڷ��ͳ�ʱʱ��
    } tx;
    
    struct {
        u8 buf[MAX_UART_RECV_BUF_LEN]; //���ջ�����
        u8 * volatile write_index;  //д����
        u8 * volatile read_index;   //������
        volatile u16 bytes;         //�������ִ��ֽ���
        u32 start_time;             //��ʼ����ʱ��
        u8 timeout;                 //�����ֽڵĳ�ʱʱ��
    } rx;

    void *ext;                      //��չָ��
    
#if (UART_DEBUG_EN > 0u)
    bool recv_pkt_overflow;         //���հ������־
    u16 send_timeout_times;         //���ͳ�ʱ����
#endif
} UART_PARAM;

#define MAX_COM_BUF_LEN              24 //������������󳤶�

typedef struct {
    volatile u8 len;                //���������������ֽ�
    u8 buf[MAX_COM_BUF_LEN];        //����������
} COM_PARAM;

extern COM_PARAM g_com_param;

u8 uart_send_data(u16 *tx_buf, u16 tx_num);
u16 get_bytes(void);
u8 get_char(void);
void uart_send_end_callback(void);


#ifdef __cplusplus
}
#endif

#endif
