//=====================================
//
// �t�B�[���h�C���t�H�A�N�^�[[FieldInfoActor.h]
// �@�\�F�t�B�[���h��̏���\������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _FIELDINFOACTOR_H_
#define _FIELDINFOACTOR_H_

#include "../../../Framework/Renderer3D/BillboardObject.h"
#include "../../../Framework/Renderer3D/BoardPolygon.h"
#include "../../../Framework/Pattern/BaseState.h"

#include <vector>

//**************************************
// �N���X��`
//**************************************
class FieldInfoActor :
	public BillboardObject
{
public:
	/**************************************
	�A�N�^�[�̏�Ԃ�\���񋓎q
	***************************************/
	enum State
	{
		Idle,		// �ҋ@
		Create,		// �쐬
		Remove,		// �폜
		Connect,	// �����Ȃ�����
		Link,		// �����N���x�����オ����
		Congestion,	// ���G���Ă���
		Max
	};

	FieldInfoActor(const D3DXVECTOR3& pos, State state);
	~FieldInfoActor();

	void Update();
	void Draw();

	using InfoState = BaseState<FieldInfoActor, State>;
	void ChangeState(State next);	// �X�e�[�g�}�V���̐؂�ւ�


private:
	BoardPolygon* polygon;

	// �萔��`
	static const D3DXVECTOR3 ActorScale;
	static const D3DXVECTOR2 ActorSize;

	// �X�e�[�g�}�V��
	State current;
	InfoState* infoState;
	std::vector<InfoState*> fsm;
	
	// �e�X�e�[�g�N���X�̑O���錾
	class IdleFieldInfoState;
	class CreateFieldInfoState;
	class RemoveFieldInfoState;
	class ConnectFieldInfoState;
	class LinkFieldInfoState;
	class CongestionFieldInfoState;

};

#endif

