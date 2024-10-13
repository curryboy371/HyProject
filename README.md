# HyProject

- Unreal5.4버전으로 제작한 모듈화 시스템 프레임 워크입니다.
- 프레임워크는 플러그인으로 제작하였고, 기능 별로( 애니메이션, FSM, AI, Core 등 ) 플러그인의 하위 모듈로 모듈화 하여 만들었습니다.
- 모듈의 의존성 관계는 UML 그림으로 표현했습니다.
- 모듈의 기능별로 설명 및 예시 코드를 첨부해두었고 Git Wiki의 내용을 기반으로 작성한 문서이므로 [Link-Wiki](https://github.com/curryboy371/HyProject/wiki) 에서 보는 것을 추천드립니다.


## Framework Graph
![Uml_v1](https://github.com/user-attachments/assets/6e484ce5-ca61-4479-8017-c3b3b84a158c)


## 주요 기능

### Framework
- 시스템별 모듈화, 프레임워크 플러그인화

### Animation
- 애니메이션 Layer화, DistanceMatch, FootSync 등의 기능을 사용하여 자연스러운 애니메이션 구현

### FSM
- FGameplayTag를 활용하여 상태 계층적 구분, Montage와 혼합하여 상태와 Anim을 한번에 관리하는 System 구현

### AI
- Behavior Tree와 FSM을 혼용하여 AI System 구현

### Logging
- 모듈에 따라 카테고리를 구분하는 로그 시스템 구현
