//=====================================
//
//PlaceActorController.h
//�@�\:�v���C�X�A�N�^�[�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _PLACEACTORCONTROLLER_H_
#define _PLACEACTORCONTROLLER_H_

#include "../../main.h"
#include "Place\PlaceConfig.h"
#include "FieldConfig.h"

#include <vector>
#include <unordered_map>

/**************************************
�O���錾
***************************************/
class PlaceActor;
class TaskHandle;
class PassengerController;

namespace Field::Model
{
	class PlaceModel;
	class RouteModel;
}

namespace Field::Along
{
	class AlongController;
}

namespace Field::Route
{
	class AStarController;
}

namespace Field::Actor
{
	/**************************************
	�^�G�C���A�X
	***************************************/
	using RouteModelPtr = std::shared_ptr<Field::Model::RouteModel>;
	using ActorContainer = std::unordered_map<unsigned, std::unique_ptr<PlaceActor>>;

	class BackGroundContainer;

	/**************************************
	�N���X��`
	***************************************/
	class PlaceActorController
	{
	public:
		PlaceActorController(Field::FieldLevel level);
		~PlaceActorController();

		//�X�V�����A�`�揈��
		void Update();
		void Draw();

		void LoadResource();

		//�A�N�^�[��������
		void SetActor(const Model::PlaceModel* place, int delay = 0);
		void SetActor(const RouteModelPtr routeModel);

		//�A�N�^�[�؂�ւ�����
		//���ɃA�N�^�[�𐶐����Ă���ꍇ�͂��������Ă�
		void ChangeActor(const Model::PlaceModel* place);

		//�A�N�^�[���ŏ���
		bool DestroyActor(const Model::PlaceModel* place);

		//�������̃��f����������
		void GrowthAlongObject(const D3DXVECTOR3& position);

		//�X���q������
		void OnConnectedTown(const Model::PlaceModel *place);

		//�p�b�Z���W���[�o������
		void DepartPassenger(const Model::PlaceModel* start, const Model::PlaceModel* goal, const Model::PlaceModel* town);
		
		//�������{�[�i�X�擾�ݒ�
		float GetSideWayBonus() const;

		//�C���ǂ����̔���
		bool IsSeaPlace(const FieldPosition& position) const;

		//�萔�����o
		static const D3DXVECTOR3 PositionEmitSmog;		//���������̉������ʒu
		static const float PlacePositionOffset;			//�A�N�^�[���m�̔z�u�Ԋu
		static const unsigned ReserveGround;			//�n�ʃA�N�^�[�p�ɗ\�񂷂�R���e�i�T�C�Y

	private:
		//�A�N�^�[�p�^�[���񋓎q
		enum ActorPattern
		{
			City,
			CrossJunction,
			TJunction,
			Curve,
			StarightRoad,
			Mountain,
			River,
			Bridge,
			None,
			Max
		};

		//�t�B�[���h���x��
		Field::FieldLevel currentLevel;

		//�A�N�^�[�R���e�i
		ActorContainer actorContainer;
		ActorContainer poolDestroy;

		//�w�i�A�N�^�[�R���e�i
		BackGroundContainer *bgContainer;

		//�������̏��R���e�i
		Along::AlongController *alongController;

		//A*�R���g���[��
		Route::AStarController *aStarController;

		//�p�b�Z���W���[�R���g���[��
		PassengerController *passengerController;

		//�����̔��W�{�[�i�X
		float bonusSideWay;

		//�e�A�N�^�[��������
		void SetRoad(const Model::PlaceModel* place, int delay);
		void SetTown(const Model::PlaceModel* place);
		void SetBridge(const Model::PlaceModel* place);
		void SetJunction(const Model::PlaceModel* place);
		void SetMountain(const Model::PlaceModel* place);

		//�R���e�i�ǉ��A�폜����
		void AddContainer(unsigned key, PlaceActor* actor);
		bool EraseFromContainer(unsigned key);

		//�A�j���[�V�����Z�b�g����
		void SetRoadGenerateAnimation(PlaceActor* actor, const D3DXVECTOR3 actorPos, int delay = 0);
	};
}
#endif