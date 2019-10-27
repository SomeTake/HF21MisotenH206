//=====================================
//
//�|���S������[BoardPolygon.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "BoardPolygon.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/PolygonResource.h"

/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
BoardPolygon::BoardPolygon() :
	vtxBuff(nullptr),
	texture(nullptr),
	texDiv(1.0f, 1.0f),
	texSize(1.0f, 1.0f)
{
	pDevice = GetDevice();

	//�}�e���A��������
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Diffuse.g = material.Diffuse.b = material.Diffuse.a = 1.0f;
	material.Ambient.r = material.Ambient.g = material.Ambient.b = material.Ambient.a = 1.0f;
	material.Emissive.r = material.Emissive.g = material.Emissive.b = material.Emissive.a = 1.0f;
	material.Specular.r = material.Specular.g = material.Specular.b = material.Specular.a = 1.0f;
	material.Power = 0.0f;
}

/**************************************
�f�X�g���N�^
***************************************/
BoardPolygon::~BoardPolygon()
{
	SAFE_RELEASE(vtxBuff);
	SAFE_RELEASE(texture);

	if (resource != NULL)
		resource->OnRelease();
}

/**************************************
�`�揈��
***************************************/
void BoardPolygon::Draw()
{
	D3DMATERIAL9 matDef;
	pDevice->GetMaterial(&matDef);

	pDevice->SetMaterial(&material);

	pDevice->SetTexture(0, texture);

	pDevice->SetStreamSource(0, vtxBuff, 0, sizeof(VERTEX_MATERIAL));

	pDevice->SetFVF(FVF_VERTEX_MATERIAL);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetMaterial(&matDef);
}

/**************************************
UV�����ݒ菈��
***************************************/
void BoardPolygon::SetTexDiv(const D3DXVECTOR2& div)
{
	texDiv = div;
	texSize.x = 1.0f / div.x;
	texSize.y = 1.0f / div.y;
}

/**************************************
UV�C���f�b�N�X�ݒ菈��
***************************************/
void BoardPolygon::SetTextureIndex(int index)
{
	int x = index % (int)texDiv.x;
	int y = index / (int)texDiv.x;
}

/**************************************
UV�ݒ菈��
***************************************/
void BoardPolygon::SetUV(const D3DXVECTOR2 & uv)
{
	VERTEX_MATERIAL *pVtx;
	vtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(uv.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, uv.y);
	pVtx[3].tex = D3DXVECTOR2(uv.x, uv.y);

	vtxBuff->Unlock();
}
