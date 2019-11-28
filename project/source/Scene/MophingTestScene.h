//=====================================
//
//MophingTestScene.h
//�@�\:���[�t�B���O�e�X�g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _MOPHINGTESTSCENE_H_
#define _MOPHINGTESTSCENE_H_

#include "../../main.h"
#include "../../Framework/Core/BaseScene.h"
#include <vector>

/**************************************
�O���錾
***************************************/
class MophingEffect;
class MeshContainer;

namespace Field
{
	class FieldSkyBox;
}
/**************************************
�N���X��`
***************************************/
class MophingTestScene : public BaseScene
{
	using BaseScene::BaseScene;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	LPDIRECT3DVERTEXBUFFER9 vtx1, vtx2;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	LPDIRECT3DTEXTURE9 texture;
	DWORD fvf, fvf2;
	LPDIRECT3DVERTEXDECLARATION9 declare;

	std::vector<D3DXATTRIBUTERANGE> attributeTable;

	MophingEffect *effect;

	std::vector<D3DMATERIAL9> materials;
	DWORD materialNum;

	Field::FieldSkyBox *skybox;
	MeshContainer *meshContainer;

};
#endif