#include "pid.h"
PidController_t g_pid_forward;


void pid_init(PidController_t *pid, float kp, float ki, float kd, int16_t out_max)
{
    if (pid == NULL) return;

    pid->kp      = kp;
    pid->ki      = ki;
    pid->kd      = kd;
    pid->out_max = out_max;

    /* �����ڲ�״̬ */
    pid->target_value   = 0.0f;
    pid->feedback_value = 0.0f;
    pid->error[0]       = 0.0f;
    pid->error[1]       = 0.0f;
    pid->p_out          = 0.0f;
    pid->i_out          = 0.0f;
    pid->d_out          = 0.0f;
    pid->output         = 0;
}

int16_t pid_calculate(PidController_t *pid, float target_value, float feedback_value,
                      float output_dead_zone, float i_clear_zone,float i_out_max )
{
    float error;

    if (pid == NULL) return 0;

    /* ����Ŀ��ֵ�ͷ���ֵ */
    pid->target_value   = target_value;
    pid->feedback_value = feedback_value;

    /* ���������ʷ����������� */
    pid->error[1] = pid->error[0];
    pid->error[0] = target_value - feedback_value;
    error = pid->error[0];

    /* === ������ === */
    pid->p_out = pid->kp * error;

    /* === ������������ֱ��ͣ� === */
    pid->i_out += pid->ki * error;

    /* �������޷� [-50, +50] */
    if (pid->i_out > i_out_max) {
        pid->i_out = i_out_max;
    } else if (pid->i_out < -i_out_max) {
        pid->i_out = i_out_max;
    }

    /* ������������ʱ������� */
    if (error > -i_clear_zone && error < i_clear_zone) {
        pid->i_out = 0.0f;
    }

    /* === ΢���� === */
    pid->d_out = pid->kd * (pid->error[0] - pid->error[1]);

    /* === �ϲ�������޷� === */
    pid->output = (int16_t)(pid->p_out + pid->i_out + pid->d_out);

    /* �޷��� [-out_max, +out_max] */
    if (pid->output > pid->out_max) {
        pid->output = pid->out_max;
    } else if (pid->output < -pid->out_max) {
        pid->output = -pid->out_max;
    }

    /* Ӧ��������� */
    if (error > -output_dead_zone && error < output_dead_zone) {
        pid->output = 0;
    }

    return pid->output;
}
int16_t pid_calculate_increment(PidController_t *pid,
                                float target_value,
                                float feedback_value,
                                float output_dead_zone,
                                float i_clear_zone)
{
    float error;
    float delta_output;
    float d_temp;

    if(pid == NULL)
        return 0;

    /* ����Ŀ��ֵ */
    pid->target_value = target_value;
    pid->feedback_value = feedback_value;

    /* ���������ʷ */
    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->error[0] = target_value - feedback_value;

    error = pid->error[0];

    /* =====================
       P��
       ===================== */
    pid->p_out = pid->kp *
                (pid->error[0] - pid->error[1]);

    /* =====================
       I����ַ��룩
       ����Сʱ�رջ���
       ===================== */
    if(fabs(error) > i_clear_zone)
    {
        pid->i_out = pid->ki * pid->error[0];
    }
    else
    {
        pid->i_out = 0;
    }



    /* PID���� */
    delta_output =
            pid->p_out
          + pid->i_out
          + pid->d_out;

    /* ����ۼ� */
    pid->output += delta_output;

    /* ����޷� */
    if(pid->output > pid->out_max)
        pid->output = pid->out_max;

    if(pid->output < -pid->out_max)
        pid->output = -pid->out_max;

    /* ������� */
    if(fabs(error) < output_dead_zone)
    {
        pid->output = 0;
    }

    return (int16_t)(pid->output);
}
PidController_t *pid_get_speed_controller(void)
{
    return &g_pid_forward;
}
