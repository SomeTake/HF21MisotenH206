//=====================================
//
// �p�b�Z���W���[�A�N�^�[[PassengerActor.h]
// �@�\�F�t�B�[���h����s��������A�N�^�[
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PASSENGERACTOR_H_
#define _PASSENGERACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"
#include "../../../Framework/Tween/Tween.h"
#include "../../Field/FieldConfig.h"

#include <functional>

//**************************************
// �񋓎q�ݒ�
//**************************************
namespace FModel = Field::Model;

//**************************************
// �N���X��`
//**************************************
class PassengerActor :
	public GameObject
{
	friend class Tween;
public:
	PassengerActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~PassengerActor();

	virtual void Update();
	void Draw();

	// ���b�V���̏�Ԃ�\���X�e�[�g
	enum State
	{
		Car,
		Ship,
		Train,
		SpaceShip,
	};

	State GetType();						// ���݂̃��b�V���̏�Ԃ��擾
	void SetType(State next);				// ���̃��b�V���̏�ԂɃ^�O���Z�b�g
	void ChangeMesh(const char* nextTag);	// ���b�V���؂�ւ�
	void MoveDest(const D3DXVECTOR3 dest, std::function<void(void)> callback = nullptr);	// �ړI�n�܂ł̈ړ�(���B������callback��Ԃ�)

private:
	State current;			// ���݂̃��b�V���̏��

	MeshContainer* mesh;
	D3DXVECTOR3 dest;		// �ړI�n

	// �萔��`
	static const D3DXVECTOR3 ActorScale;
	static const D3DXVECTOR3 InitForward;
};

#endif
