//=====================================
//
//MophingTestScene.cpp
//�@�\:���[�t�B���O�e�X�g�V�[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "MophingTestScene.h"
#include "../../Framework/Effect/MophingEffect.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Renderer3D/MeshContainer.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../../Framework/Renderer3D/MophingMeshContainer.h"

#include "../Field/Object/FieldSkyBox.h"

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

	//�אڏ����쐬���čœK��
	std::vector<DWORD> adjList;
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

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

		for (int j = i; j < i * 2; j++)
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

	//�אڏ����쐬���čœK��
	adjList.resize(3 * mesh->GetNumFaces());
	mesh->GenerateAdjacency(1.0f / 512, &adjList[0]);
	mesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT, &adjList[0], 0, 0, 0);

	//�e�o�b�t�@���擾
	mesh->GetVertexBuffer(&vtx2);	
	fvf2 = mesh->GetFVF();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/MODEL/Mophing/ishi.bmp", &texture);

	SAFE_RELEASE(mesh);
	SAFE_RELEASE(tmpMaterial);

	effect = new MophingEffect();

	sceneCamera = new Camera();
	Camera::SetMainCamera(sceneCamera);

	skybox = new Field::FieldSkyBox(Field::FieldLevel::World);

	ResourceManager::Instance()->LoadMesh("ishi", "data/MODEL/Mophing/ishi.x");
	ResourceManager::Instance()->LoadMesh("ishi2", "data/MODEL/Mophing/ish2.x");

	morphContainer = new MorphingMeshContainer();
	ResourceManager::Instance()->GetMesh("ishi", morphContainer);
	morphContainer->RegisterVertex(0);

	ResourceManager::Instance()->GetMesh("ishi2", morphContainer);
	morphContainer->RegisterVertex(1);

	morphContainer->SetCurrent(0);
	morphContainer->SetNext(1);
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

	SAFE_DELETE(sceneCamera);

	SAFE_DELETE(morphContainer);
}

/**************************************
�X�V����
***************************************/
void MophingTestScene::Update()
{
	sceneCamera->Update();
}

/**************************************
�`�揈��
***************************************/
void MophingTestScene::Draw()
{
	sceneCamera->Set();

	skybox->Draw();
	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetStreamSource(0, vtx1, 0, D3DXGetFVFVertexSize(fvf));
	pDevice->SetStreamSource(1, vtx2, 0, D3DXGetFVFVertexSize(fvf2));

	UINT freq0, freq1;
	pDevice->GetStreamSourceFreq(0, &freq0);
	pDevice->GetStreamSourceFreq(1, &freq1);

	pDevice->SetIndices(indexBuff);

	pDevice->SetVertexDeclaration(declare);

	static Transform transform;
	static D3DXVECTOR3 pos = Vector3::Forward * 1000.0f, scale = Vector3::One;
	static float t = 0.0f;

	Debug::Begin("Mophing");
	Debug::Slider("pos", pos, Vector3::One * -1000.0f, Vector3::One * 1000.0f);
	Debug::Slider("scl", scale, Vector3::Zero, Vector3::One * 20.0f);
	Debug::Slider("t", t, 0.0f, 1.0f);
	Debug::End();

	transform.SetPosition(pos);
	transform.SetScale(scale);

	morphContainer->SetChange(t);
	morphContainer->Draw(transform.GetMatrix());

	//effect->SetWorld(transform.GetMatrix());
	//effect->SetTime(t);

	//for (unsigned i = 0; i < materialNum; i++)
	//{
	//	effect->SetMaterial(materials[i]);

	//	pDevice->SetTexture(0, texture);

	//	effect->Begin();
	//	effect->BeginPass(0);

	//	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
	//		0,
	//		attributeTable[i].VertexStart,
	//		attributeTable[i].VertexCount,
	//		attributeTable[i].VertexStart * 3,
	//		attributeTable[i].FaceCount);

	//	effect->EndPass();
	//	effect->End();
	//}

	//transform.SetWorld();
	//meshContainer->Draw();
}
