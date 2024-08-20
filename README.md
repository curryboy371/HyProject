# HyProject

## 모듈 그래프
![Uml](https://github.com/user-attachments/assets/31c626c9-3ff6-43eb-ada5-f6e949633695)


## 1. 모듈화

### 목적 
- 

### 사용방법
- 각 기능을 모듈단위로 나누어, 사용할 모듈에서만 private 참조하여 사용함



## 0. 주요 모듈

### GameModule | HyProject
-게임 모듈

### Plugin | HyFramework
- 프레임워크 플러그인

### Plugin | HyTable
- 테이블 플러그인

## 1. 모듈 설명

### Game 

### HyProject (Game-MainModule)
- 클래스 접두어 Hy
- 게임 모듈

###


### Plugin 

### HyFramework (Plugin)

### HyFramework (Plugin-MainModule)

- 클래스 접두어 Hy
- HyFramework Plugin 메인 모듈
- 게임의 프레임워크를 구현한 것으로 gamemode, gameinstance 등의 base가 존재


### HyCore (Plugin-Module)
- 클래스 접두어 HyCore
- HyFramework plugin의 core 기능

- 로깅 클래스를 가지고 있어 모든 모듈 ( 게임 모듈, 플러그인 모듈)에서 이 모듈을 참조하여 로깅에 활용할 것
- 로그를 남기는 시간을 줄이기 위해 매크로, variadic template 함수를 활용하였음.


### ActionsSystem (Plugin-Module)
- 클래스 접두어 Actions, Hy
- 캐릭터 상태를 관리할 FSM과 유사하게 사용할 시스템, State = Action
- GameplayTags로 Action을 구분하여 각 Action을 계층별로 관리할 수 있게 함

### HyUISystem (Plugin-Module)

- 클래스 접두어 HyUI
- UI 시스템 모듈을 분리하기 위해 사용.
- UI Base가 되는 추상 클래스들만 넣어두고, 실제 사용하는 UI는 Game or HyFramework 모듈에 넣어 사용할 것
- UI는 Game과 상호작용하는 부분이 많다보니 단순히 UI의 추상 클래스만 넣어둔다고 보면 됨.


### HyFXSystem (Plugin-Module)

- 클래스 접두어 HyFX, Hy
- 이펙트, 사운드 등을 한 모듈에서만 관리하기 위해 생성함.


### CharacterControlSystem (Plugin-Module)

- 클래스 접두어 CControl, Hy
- 캐릭터 컨트롤과 관련된 시스템을 관리
- 애니메이션인스턴스, 애님 레이어, 무브먼트 등 
- Input 기능 포함, CharacterBase단에서 상속할 Input Interface 제공


###

### Plugins | HyTable

### HyTableSystem (Plugin-MainModule)
- 클래스 접두어 HyTable
- Unreal Data를 csv로 관리하기 위한 테이블
