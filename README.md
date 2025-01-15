# UE5 학습한 내용

# 1. 캐릭터 및 이동
Pawn, Charactor

PlayerControlRotation와 MovementComponent

이동방식 컨트롤 변경과 UNiagaraSystem(커서)

이동 방식 컨트롤 변경을 위해 애니메이션 Asset정리

# 2. 입력 처리
Input (Input Mapping Context와 InputAction)

# 3. 애니메이션
애니메이션 블루프린터 (State Machine, New Save Cached Pos, Blend Space 등)

리타게팅과 새로운 Asset 추가, 애니메이션 사이트 추천

애니메이션 몽타주와 상하체 애니메이션 분리

Animation Event(AnimNotify) 사용하여 이벤트 발생

# 4. 충돌과 후처리
충돌과 델리게이트

충돌(Collision)과 Preset, Trace

PostProcess와 Material로 외곽선 후처리 사용하기

# 5. 게임 플레이 데이터 관리
GamePlayTags, AssetManager, DataAsset과 PrimaryDataAsset

AssetManager와 Load

GameplayAbility와 skill 관리

GameplayEffect

GameplayAttribute와 Stats 통합관리

AbilitySystem과 GAS, PlayerStateClass, GAS 참조 사이트

# 6. AI
AI#1 - AIController, NavMeshBoundsVolume을 사용한 기본적인 길찾기

AI#2 - Behavior Tree와 BlackBoard와 Task

AI#3 - Behavior Tree와 Service, Decorator

AI#4 - Task, Decorator, Service C++로 개발

# 7. UI
UI#1

UI#2-1 HpBar 블루프린트로 연동

UI#2-2 HpBar C++ 연동, UPROPERTY(meta = (BindWidget))

UI#3 인벤토리 UI 마우스 이벤트

UI#4 인벤토리 WorldSubsystem, GameModeBase

UI#5 인벤토리 끝 드래그 드롭하면 미리보기 위젯 생성, 드롭하면 영역에 아이템 생성

UI#5 인벤토리 아이템 생성과 인벤토리에 실질적 배치

# 8. 기타 게임 메커니즘
추격과 공격

오브젝트 선택 외곽선 처리 (Highlight)
