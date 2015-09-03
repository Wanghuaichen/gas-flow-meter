/** 
 * @file     main.c
 * @brief    ����������
 * @details  
 * @author   ����
 * @email    591881218@qq.com
 * @date     2015
 * @version  vX.XX
 * @par Copyright (c):  
 *           ���ֵ���
 * @par History:          
 *   version: author, date, desc\n 
 */

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                    
OS_STK                 App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE];
OS_STK                 App_TaskKeyStk[APP_CFG_TASK_KEY_STK_SIZE];

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void           App_TaskStart                (void *p_arg);

static  void           App_MemAlloc                 (void);
static  void           App_TaskCreate               (void);
static  void           App_EventCreate              (void);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This the main standard entry point.
*
* Note(s)     : none.
*********************************************************************************************************
*/
int  main(void)
{   
    INT8U err;
    

    BSP_IntDisAll();                                            /* Disable all interrupts until we are ready to accept them */
    
    App_MemAlloc();
    
    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt((void (*)(void *)) App_TaskStart,           /* Create the start task                                    */
                    (void           *) 0,
                    (OS_STK         *)&App_TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_START_PRIO,
                    (INT16U          ) APP_CFG_TASK_START_PRIO,
                    (OS_STK         *)&App_TaskStartStk[0],
                    (INT32U          ) APP_CFG_TASK_START_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskNameSet(APP_CFG_TASK_START_PRIO, "Start", &err);

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)       */
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg   is the argument passed to 'App_TaskStart()' by 'OSTaskCreateExt()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Notes       : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/
static  void  App_TaskStart (void *p_arg)
{
    INT32U count = 0;

    
    (void)p_arg;                                                /* See Note #1                                              */

    BSP_Init();                                                 /* Initialize BSP functions                                 */

    OS_CPU_SysTickInit();                                       /* Initialize the SysTick                                   */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                                   */
#endif   

    App_EventCreate();                                          /* Create application events                                */

    App_TaskCreate();                                           /* Create application tasks                                 */
        
    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop            */
        if(!(count % LED_RUN_TOGGLE_PERIOD))
        {
            LED_RUN_TOGGLE();

            clr_wdt();      
        }

        count++;
        
        OSTimeDlyHMSM(0, 0, 0, 50);
    }
}

/*
*********************************************************************************************************
*                                      App_MemAlloc
*
* Description :  Allocs the application memories.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  Main().
*
* Note(s)     :  none.
*********************************************************************************************************
*/
static  void  App_MemAlloc (void)
{
}

/*
*********************************************************************************************************
*                                      App_EventCreate
*
* Description :  Creates the application events.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/
static  void  App_EventCreate (void)
{  
    g_key_para.sem = OSSemCreate(0);
}

/*
*********************************************************************************************************
*                                      App_TaskCreate()
*
* Description :  This function creates the application tasks.
*
* Argument(s) :  none.
*
* Return(s)   :  none.
*
* Caller(s)   :  App_TaskStart().
*
* Note(s)     :  none.
*********************************************************************************************************
*/
static  void  App_TaskCreate (void)
{       
    INT8U err;
    

    OSTaskCreateExt((void (*)(void *)) App_TaskKey,
                    (void           *) 0,
                    (OS_STK         *)&App_TaskKeyStk[APP_CFG_TASK_KEY_STK_SIZE - 1],
                    (INT8U           ) APP_CFG_TASK_KEY_PRIO,
                    (INT16U          ) APP_CFG_TASK_KEY_PRIO,
                    (OS_STK         *)&App_TaskKeyStk[0],
                    (INT32U          ) APP_CFG_TASK_KEY_STK_SIZE,
                    (void           *) 0,
                    (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskNameSet(APP_CFG_TASK_KEY_PRIO, "Key", &err);
}

