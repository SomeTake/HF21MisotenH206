//=====================================
//
//MophingTestScene.cpp
//�@�\:���[�t�B���O�e�X�g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MophingTestScene.h"
#include "../../Framework/Effect/MophingEffect.h"

/**************************************
����������
***************************************/
void MophingTestScene::Init()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	LPD3DXBUFFER tmpMaterial;
	LPD3DXMESH mesh;

	//X�t�@�C���ǂݍ���1
	HRESULT res = D3DXLoadMeshFromX("data/MODEL/Mophing/ishi.x",
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&tmpMaterial,
		NULL,
		&materialNum,
		&mesh);

	if (res != S_OK)
		return;

	//�e�o�b�t�@���擾
	mesh->GetVertexBuffer(&vtx1);
	mesh->GetIndexBuffer(&indexBuff);
	fvf = mesh->GetFVF();

	//�����e�[�u���擾
	attributeTable.resize(materialNum);
	mesh->GetAttributeTable(&attributeTable[0], NULL);

	//�}�e���A����D3DXMATERIAL�Ƃ��čœK��
	materials.resize(materialNum);
	D3DXMATERIAL* matBuffer = (D3DXMATERIAL*)tmpMaterial->GetBufferPointer();
	for (DWORD i = 0; i < materialNum; i++)
	{
		materials[i] = matBuffer[i].MatD3D;
	}

	//���_�錾�쐬
	D3DVERTEXELEMENT9 elem[65];
	ZeroMemory(&elem[0], sizeof(D3DVERTEXELEMENT9) * 65);
	mesh->GetDeclaration(elem);

	for (int i = 0; i < 65; i++)
	{
		if (elem[i].Type != D3DDECLTYPE_UNUSED)
			continue;

		for (int j = 0; j < i * 2; j++)
		{
			elem[j] = elem[j - i];
			elem[j].Stream = 1;
			elem[j].UsageIndex = 1;
		}
		elem[i * 2] = D3DDECL_END();
		break;
	}

	pDevice->CreateVertexDeclaration(elem, &declare);

	//X�t�@�C���ǂݍ���2
	SAFE_RELEASE(mesh);
	res = D3DXLoadMeshFromX("data/MODEL/Mophing/ishi2.x",
		D3DXMESH_MANAGED,
		pDevice,
		NULL,
		&tmpMaterial,
		NULL,
		&materialNum,
		&mesh);

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/MODEL/Mophing/ishi.bmp", &texture);

	SAFE_RELEASE(mesh);
	SAFE_RELEASE(tmpMaterial);

	effect = new MophingEffect();
}

/**************************************
�I������
***************************************/
void MophingTestScene::Uninit()
{
	SAFE_RELEASE(vtx1);
	SAFE_RELEASE(vtx2);
	SAFE_RELEASE(indexBuff);
	SAFE_RELEASE(texture);
	SAFE_RELEASE(declare);

	attributeTable.clear();
	materials.clear();
	materialNum = 0;

	SAFE_DELETE(effect);
}

/**************************************
�X�V����
***************************************/
void MophingTestScene::Update()
{
}

/**************************************
�`�揈��
***************************************/
void MophingTestScene::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, vtx1, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, vtx2, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetIndices(indexBuff);

	Transform transform;
	effect->SetWorld(transform.GetMatrix());

	for (unsigned i = 0; i < materialNum; i++)
	{
		effect->SetMaterial(materials[i]);
		
		effect->SetTime(0.0f);

		pDevice->SetTexture(0, texture);

		effect->Begin();
		effect->BeginPass(0);

		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0,
			attributeTable[i].VertexStart,
			attributeTable[i].VertexCount,
			attributeTable[i].VertexStart * 3,
			attributeTable[i].FaceCount);

		effect->EndPass();
		effect->End();
	}
}
