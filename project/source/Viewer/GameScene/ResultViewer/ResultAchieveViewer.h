//=====================================
//
//ResultAchieveViewer.h
//�@�\:���U���g��ʂ̎��уr���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _RESULTACHIEVEVIEWER_H_
#define _RESULTACHIEVEVIEWER_H_

#include "../../../../main.h"
#include "../../Framework/BaseViewer.h"
#include "../../../Reward/RewardConfig.h"

#include <functional>
#include <vector>

/**************************************
�O���錾
***************************************/
class TextureDrawer;
class TextViewer;

/**************************************
�N���X��`
***************************************/
class ResultAchieveViewer : public BaseViewer
{
public:
	ResultAchieveViewer();
	~ResultAchieveViewer();

	void Update();
	void Draw();

	void SetReward(std::vector<RewardConfig::Type>& rewardContainer);
	void StartAnim(std::function<void()> callback = nullptr);
	
	static const D3DXVECTOR3 InitTitlePos;
	static const D3DXVECTOR3 DestTitlePos;
	static const D3DXVECTOR3 InitTextPos;
	static const D3DXVECTOR3 InitIconPos;
	static const int SizeTextFont;
private:
	TextureDrawer *bg;
	TextureDrawer *title;
	std::vector<TextViewer*> textContainer;
	std::vector<TextureDrawer*> NewIconContainer;

	void SlideinText();
};

#endif