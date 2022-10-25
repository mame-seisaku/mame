#include "all.h"

int stage_state[STAGE_MAX];
    
// init deinit �����ꂢ�Ȍ`�ŌĂ΂�ĂȂ�����
// stage�I�����ɌĂԕK�v�����邩��

/// <summary>
/// �����ݒ�
/// </summary>
void stage_init()
{
    stage0_init();
    stage1_init();
}

/// <summary>
/// �I������
/// </summary>
void stage_deinit()
{
    stage0_deinit();
    stage1_deinit();
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="s">�X�e�[�W�ԍ�</param>
void stage_update(int s)
{
    switch (s)
    {
    case 0:
        stage0_update();
        break;
    case 1:
        stage1_update();
        break;
    }
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="s">�X�e�[�W�ԍ�</param>
void stage_render(int s)
{
    switch (s)
    {
    case 0:
        stage0_render();
        break;
    case 1:
        stage1_render();
        break;
    }
}
