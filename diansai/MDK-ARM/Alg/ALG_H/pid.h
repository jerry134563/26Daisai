#ifndef __PID_H
#define __PID_H
#include <stdint.h>
#include <stddef.h>
#include <main.h>
/* PID �������ṹ�� */
typedef struct {
    float kp;               /* �������� */
    float ki;               /* �������� */
    float kd;               /* ΢������ */
    int16_t out_max;        /* ����޷�������ֵ�� */

    float target_value;     /* ��ǰĿ��ֵ���趨�㣩 */
    float feedback_value;   /* ��ǰ����ֵ������ֵ�� */
    float error[3];         /* �����ʷ��[0]=��ǰ���, [1]=��һ����� */

    float p_out;            /* ��������� */
    float i_out;            /* ��������� */
    float d_out;            /* ΢������� */

    int16_t output;         /* PID ������� */
} PidController_t;
void pid_init(PidController_t *pid, float kp, float ki, float kd, int16_t out_max);

int16_t pid_calculate(PidController_t *pid, float target_value, float feedback_value,
                      float output_dead_zone, float i_clear_zone,float i_out_max );
int16_t pid_calculate_increment(PidController_t *pid,
                                float target_value,
                                float feedback_value,
                                float output_dead_zone,
                                float i_clear_zone);
PidController_t *pid_get_speed_controller(void);

#endif
