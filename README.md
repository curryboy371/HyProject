# HyProject

## 1. 모듈화

### 목적 
- 

### 사용방법
- 각 기능을 모듈단위로 나누어, 사용할 모듈에서만 private 참조하여 사용함




## 1. 모듈 종류

### Game | HyProject
- 클래스 접두어 Hy
- 게임 모듈



### Plugins | Main | HyFramework
- 클래스 접두어 Hy
- HyFramework Plugin 메인 모듈
- 게임의 프레임워크를 구현한 것으로 gamemode, gameinstance 등의 base가 존재


### Plugins | Core | HyCore
- 클래스 접두어 HyCore
- HyFramework plugin의 core 기능

- 로깅 클래스를 가지고 있어 모든 모듈 ( 게임 모듈, 플러그인 모듈)에서 이 모듈을 참조하여 로깅에 활용할 것
- 로그를 남기는 시간을 줄이기 위해 매크로, variadic template 함수를 활용하였음.

### Plugins | LoggingSystem
- 클래스 접두어 Logging


### Plugins | ActionsSystem
- 클래스 접두어 Actions
- 캐릭터 상태를 관리할 FSM과 유사하게 사용할 시스템, State = Action
- GameplayTags로 Action을 구분하여 각 Action을 계층별로 관리할 수 있게 함


### Plugins | HyFXSystem
- 클래스 접두어 HyFX
- 이펙트, 사운드 등을 한 모듈에서만 관리하기 위해 생성함.

