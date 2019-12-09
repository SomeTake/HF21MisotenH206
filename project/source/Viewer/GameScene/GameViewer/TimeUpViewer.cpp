//=====================================
//
//TimeUpViewer.cpp
//�@�\:�^�C���A�b�v�r���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "TimeUpViewer.h"
#include "../../Framework/ViewerDrawer/TextureDrawer.h"

/**************************************
�R���X�g���N�^
***************************************/
TimeUpViewer::TimeUpViewer() :
	cntFrame(0),
	active(false),
	callback(nullptr)
{
	tex = new TextureDrawer({ 800.0f, 200.0f }, false);
	tex->SetPosition({ SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f });
	tex->LoadTexture("data/TEXTURE/Viewer/GameViewer/TimeUpViewer/timeup.png");
}

/**************************************
�f�X�g���N�^
***************************************/
TimeUpViewer::~TimeUpViewer()
{
	SAFE_DELETE(tex);
}

/**************************************
�X�V����
***************************************/
void TimeUpViewer::Update()
{
	if (!active)
		return;

	cntFrame++;

	//�\������
	const int FrameFinish = 90;
	if (cntFrame == FrameFinish)
	{
		tex->Close(15, CloseType::FromLeftRight, EaseType::OutCubic, [&]()
		{
			active = false;
			tex->SetVisible(false);

			if(callback != nullptr)
				callback();
		});
	}

	tex->Update();
}

/**************************************
�`�揈��
***************************************/
void TimeUpViewer::Draw()
{
	tex->Draw();
}

/**************************************
�Z�b�g����
***************************************/
void TimeUpViewer::Set(std::function<void()> callback)
{
	cntFrame = 0;
	active = true;
	tex->Expand(15, ExpandType::ToLeftRight, EaseType::OutCubic);
	tex->SetVisible(true);
	this->callback = callback;
}
