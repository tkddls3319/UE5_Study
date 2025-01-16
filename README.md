# UE5 학습 내용 정리

## 1. 캐릭터 및 이동
- **사용 클래스**: `Pawn`, `Character`
- **핵심 개념**:
  - `PlayerControlRotation`과 `MovementComponent` 활용
  - 이동 방식 컨트롤 변경 및 `UNiagaraSystem`으로 커서 구현
  - 애니메이션 Asset 정리로 이동 방식 최적화

## 2. 입력 처리
- **Input 시스템**:
  - `Input Mapping Context`와 `InputAction`을 사용한 입력 처리

## 3. 애니메이션
- **애니메이션 블루프린트**:
  - State Machine, New Save Cached Pos, Blend Space 활용
- **리타게팅 및 Asset 추가**:
  - 새로운 애니메이션 Asset 추가 및 추천 사이트 소개
- **애니메이션 몽타주**:
  - 상하체 애니메이션 분리
  - `Animation Event(AnimNotify)`를 사용하여 이벤트 트리거

## 4. 충돌과 후처리
- **충돌 처리**:
  - 충돌과 델리게이트
  - Collision Preset과 Trace 활용
- **후처리**:
  - `PostProcess`와 Material로 외곽선 후처리 구현

## 5. 게임 플레이 데이터 관리
- **Gameplay 시스템**:
  - `GamePlayTags`, `AssetManager`, `DataAsset`, `PrimaryDataAsset` 관리
  - `AssetManager`와 `Load` 동작
- **Gameplay Ability System(GAS)**:
  - `GameplayAbility`와 스킬 관리
  - `GameplayEffect`를 통한 효과 구현
  - `GameplayAttribute`와 Stats 통합 관리
  - `PlayerStateClass`와 GAS 참조 사이트 활용

## 6. AI
- **AI 기본**:
  - `AIController`와 `NavMeshBoundsVolume`을 사용한 길찾기
- **Behavior Tree**:
  - BlackBoard와 Task 구현
  - Service 및 Decorator 활용
- **C++ 개발**:
  - Task, Decorator, Service를 C++로 구현

## 7. UI
- **UI 블루프린트**:
  - `HpBar` 블루프린트를 사용한 연동 (`UI#2-1`)
- **UI C++ 연동**:
  - `HpBar`를 C++로 연동 (`UI#2-2`)
  - `UPROPERTY(meta = (BindWidget))` 활용
- **인벤토리 시스템**:
  - 인벤토리 UI 마우스 이벤트 처리 (`UI#3`)
  - `WorldSubsystem` 및 `GameModeBase`와 연동 (`UI#4`)
  - 드래그 앤 드롭으로 미리보기 위젯 생성 및 아이템 배치 (`UI#5`)
  - 인벤토리에 아이템 생성 및 실질적 배치

## 8. 기타 게임 메커니즘
- **추격과 공격**:
  - 적 추격 및 공격 로직 개발
- **오브젝트 선택**:
  - Highlight 기능 구현 및 외곽선 처리
