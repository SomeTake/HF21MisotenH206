//=====================================
//
// ���o�[�A�N�^�[[RiverActor.h]
// �@�\�F��i����f��j�p3D���f���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _RIVERACTOR_H_
#define _RIVERACTOR_H_

#include "PlaceActor.h"
//**************************************
// �O���錾
//**************************************
namespace Field::Actor
{
	class RiverEffect;
}
//**************************************
// �N���X��`
//**************************************
class RiverActor :
	public PlaceActor
{
public:
	enum FlowDirection
	{
		None,
		Forward = 1,
		Right,
		Back,
		Left
	};

	RiverActor(const D3DXVECTOR3& pos, Field::FieldLevel currentLevel);
	~RiverActor();

	void Update() override;
	void Draw() override;

	void SetDirection(FlowDirection direction);

	static void UpdateHeight();

private:
	static const int AnimationPeriod;
	static const float MaxWaveHeight;
	static float heightWave;
	static int cntWaveAnimation;

	FlowDirection direction;
	D3DXVECTOR2 uv;
	Field::Actor::RiverEffect *effect;
};

#endif
