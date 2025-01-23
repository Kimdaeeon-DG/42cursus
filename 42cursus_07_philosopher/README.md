# Philosophers Project

## 목차
1. [프로젝트 개요](#프로젝트-개요)
2. [기술적 개념](#기술적-개념)
3. [프로그램 구조](#프로그램-구조)
4. [주요 함수 설명](#주요-함수-설명)
5. [실행 방법](#실행-방법)
6. [에지 케이스 처리](#에지-케이스-처리)
7. [구현 시 고려사항](#구현-시-고려사항)

## 프로젝트 개요

이 프로젝트는 운영체제의 고전적인 동기화 문제인 '식사하는 철학자들(Dining Philosophers)' 문제를 해결하는 것입니다. 이 문제는 프로세스 동기화, 교착 상태(deadlock), 자원 경쟁 등의 개념을 이해하고 해결하는 것을 목표로 합니다.

### 문제 설명
- N명의 철학자가 원형 테이블에 앉아있습니다.
- 각 철학자 사이에는 포크가 하나씩 있습니다.
- 철학자들은 다음 세 가지 행동을 합니다:
  - 먹기 (양쪽의 포크를 사용)
  - 자기
  - 생각하기
- 철학자가 일정 시간 동안 먹지 못하면 죽게 됩니다.

## 기술적 개념

### 스레드(Threads)
- 각 철학자는 독립적인 스레드로 구현됩니다.
- 스레드는 프로세스 내에서 실행되는 가장 작은 실행 단위입니다.
- `pthread_create`를 사용하여 생성하고, `pthread_join`으로 종료를 대기합니다.

### 뮤텍스(Mutex)
- 포크는 뮤텍스로 구현되어 상호 배제를 보장합니다.
- `pthread_mutex_init`으로 초기화하고, `pthread_mutex_destroy`로 정리합니다.
- `pthread_mutex_lock`과 `pthread_mutex_unlock`으로 접근을 제어합니다.

### 교착 상태 방지
- 짝수 번호 철학자는 왼쪽 포크를, 홀수 번호 철학자는 오른쪽 포크를 먼저 집도록 구현
- 식사 시간에 약간의 지연을 두어 동시 접근을 방지

## 프로그램 구조

### 주요 구조체
```c
typedef struct s_philo
{
    int             id;             // 철학자 ID
    int             left_fork;      // 왼쪽 포크 인덱스
    int             right_fork;     // 오른쪽 포크 인덱스
    int             eat_count;      // 식사 횟수
    long long       last_meal_time; // 마지막 식사 시간
    pthread_t       thread;         // 철학자 스레드
    pthread_mutex_t meal_mutex;     // 식사 시간 보호 뮤텍스
    t_data          *data;         // 공유 데이터 포인터
} t_philo;

typedef struct s_data
{
    int             num_of_philos;  // 철학자 수
    int             time_to_die;    // 죽는 시간
    int             time_to_eat;    // 먹는 시간
    int             time_to_sleep;  // 자는 시간
    int             must_eat_count; // 필수 식사 횟수
    long long       start_time;     // 시작 시간
    int             someone_died;   // 죽음 플래그
    pthread_mutex_t *forks;         // 포크 뮤텍스 배열
    pthread_mutex_t print_mutex;    // 출력 보호 뮤텍스
    pthread_mutex_t death_mutex;    // 죽음 플래그 보호 뮤텍스
    t_philo         *philos;       // 철학자 배열
} t_data;
```

## 주요 함수 설명

### 초기화 함수들
```c
int init_data(t_data *data, int argc, char **argv)
// 프로그램 인자를 파싱하고 기본 데이터 구조를 초기화

int init_mutex(t_data *data)
// 모든 뮤텍스(포크, 출력, 죽음 플래그)를 초기화

int init_philos(t_data *data)
// 각 철학자의 데이터 구조를 초기화
```

### 철학자 행동 함수들
```c
void *philosopher(void *arg)
// 각 철학자의 메인 루틴을 구현
// 식사, 수면, 생각하기를 반복

void eating(t_philo *philo)
// 철학자의 식사 행동을 구현
// 포크를 집고, 식사하고, 포크를 내려놓음
```

### 모니터링 함수
```c
void *death_monitor(void *arg)
// 철학자들의 상태를 모니터링
// 죽음 조건 검사 및 프로그램 종료 조건 확인
```

## 실행 방법

프로그램은 다음과 같은 인자를 받습니다:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

예시:
```bash
./philo 4 800 200 200 5
```
- 4명의 철학자
- 800ms 동안 먹지 않으면 죽음
- 식사에 200ms 소요
- 수면에 200ms 소요
- 각 철학자가 5번 식사해야 함

## 에지 케이스 처리

1. **철학자가 1명인 경우**
   - 포크가 하나뿐이므로 철학자는 결국 죽게 됨

2. **음수 또는 잘못된 입력**
   - 모든 입력값은 양수여야 함
   - 잘못된 입력 시 에러 메시지 출력

3. **메모리 할당 실패**
   - 모든 동적 할당은 실패 여부 체크
   - 실패 시 이전 할당 해제 후 종료

## 구현 시 고려사항

### 1. 데이터 레이스 방지
- 공유 자원 접근 시 항상 뮤텍스 사용
- 각 철학자의 마지막 식사 시간은 개별 뮤텍스로 보호

### 2. 교착 상태 방지
- 포크 집는 순서 최적화
- 식사 시간 지연으로 동시성 제어

### 3. 성능 최적화
- 불필요한 뮤텍스 락 최소화
- 효율적인 시간 체크 구현

### 4. 자원 관리
- 모든 뮤텍스 적절히 초기화 및 해제
- 메모리 누수 방지를 위한 철저한 정리
