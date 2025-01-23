# Philosophers Project - 상세 코드 분석

## 목차
1. [파일 구조](#파일-구조)
2. [핵심 자료구조](#핵심-자료구조)
3. [주요 함수 상세 분석](#주요-함수-상세-분석)
4. [동기화 메커니즘](#동기화-메커니즘)
5. [시간 관리](#시간-관리)
6. [메모리 관리](#메모리-관리)

## 파일 구조

### philo.h
헤더 파일에는 프로그램에서 사용되는 모든 구조체 정의와 함수 선언이 포함되어 있습니다.
```c
// 필수 헤더 파일들
#include <pthread.h>    // 스레드 관련 함수들
#include <sys/time.h>   // gettimeofday 함수
#include <stdio.h>      // 입출력 함수들
#include <stdlib.h>     // malloc, free 등
#include <unistd.h>     // usleep 함수
```

### main.c
프로그램의 진입점과 초기화, 정리 로직을 포함합니다.

### init.c
모든 초기화 관련 함수들이 있습니다.

### philo.c
철학자의 행동을 구현한 코어 로직이 있습니다.

### monitor.c
감시자 스레드의 로직이 구현되어 있습니다.

### utils.c
유틸리티 함수들이 구현되어 있습니다.

## 핵심 자료구조 상세 설명

### t_data 구조체
```c
typedef struct s_data
{
    int num_of_philos;      // 철학자의 수
    int time_to_die;        // 마지막 식사 후 죽는 시간 (ms)
    int time_to_eat;        // 식사하는데 걸리는 시간 (ms)
    int time_to_sleep;      // 수면하는데 걸리는 시간 (ms)
    int must_eat_count;     // 각 철학자가 먹어야 하는 횟수 (-1: 무제한)
    long long start_time;   // 프로그램 시작 시간 (ms)
    int someone_died;       // 철학자 사망 플래그
    pthread_mutex_t *forks; // 포크 뮤텍스 배열
    pthread_mutex_t print_mutex;  // 출력 동기화용 뮤텍스
    pthread_mutex_t death_mutex;  // 사망 플래그 접근 동기화용 뮤텍스
    t_philo *philos;       // 철학자 구조체 배열
} t_data;
```

### t_philo 구조체
```c
typedef struct s_philo
{
    int id;                // 철학자 ID (1부터 시작)
    int left_fork;         // 왼쪽 포크 인덱스
    int right_fork;        // 오른쪽 포크 인덱스
    int eat_count;         // 현재까지 식사한 횟수
    long long last_meal_time; // 마지막 식사 시간
    pthread_t thread;      // 철학자 스레드
    pthread_mutex_t meal_mutex; // 식사 시간 접근 동기화용 뮤텍스
    t_data *data;         // 공유 데이터 구조체 포인터
} t_philo;
```

## 주요 함수 상세 분석

### 초기화 함수들

#### init_data
```c
int init_data(t_data *data, int argc, char **argv)
{
    // 인자 파싱 및 기본값 설정
    data->num_of_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->must_eat_count = (argc == 6) ? ft_atoi(argv[5]) : -1;

    // 유효성 검사
    if (data->num_of_philos <= 0 || data->time_to_die <= 0
        || data->time_to_eat <= 0 || data->time_to_sleep <= 0
        || (argc == 6 && data->must_eat_count <= 0))
        return (1);
    return (0);
}
```

#### init_mutex
```c
int init_mutex(t_data *data)
{
    int i;

    // 포크 뮤텍스 배열 할당
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
    if (!data->forks)
        return (1);

    // 각 포크 뮤텍스 초기화
    i = -1;
    while (++i < data->num_of_philos)
        if (pthread_mutex_init(&data->forks[i], NULL))
            return (1);

    // 공용 뮤텍스 초기화
    if (pthread_mutex_init(&data->print_mutex, NULL))
        return (1);
    if (pthread_mutex_init(&data->death_mutex, NULL))
        return (1);
    return (0);
}
```

### 철학자 행동 함수

#### philosopher
```c
void *philosopher(void *arg)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;

    // 초기 시간 설정
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);

    // 교착 상태 방지를 위한 시차 부여
    if (philo->id % 2)
        smart_sleep(data->time_to_eat / 2, data);

    // 메인 루프
    while (!data->someone_died)
    {
        eating(philo);
        if (data->must_eat_count != -1 && 
            philo->eat_count >= data->must_eat_count)
            break;
        print_status(data, philo->id, "is sleeping");
        smart_sleep(data->time_to_sleep, data);
        print_status(data, philo->id, "is thinking");
        usleep(100); // 리소스 과다 사용 방지
    }
    return (NULL);
}
```

#### eating
```c
void eating(t_philo *philo)
{
    t_data *data = philo->data;

    // 포크 잡기
    pthread_mutex_lock(&data->forks[philo->left_fork]);
    print_status(data, philo->id, "has taken a fork");
    pthread_mutex_lock(&data->forks[philo->right_fork]);
    print_status(data, philo->id, "has taken a fork");

    // 식사 시작
    pthread_mutex_lock(&philo->meal_mutex);
    print_status(data, philo->id, "is eating");
    philo->last_meal_time = get_time();
    pthread_mutex_unlock(&philo->meal_mutex);

    // 식사 시간
    smart_sleep(data->time_to_eat, data);
    philo->eat_count++;

    // 포크 내려놓기
    pthread_mutex_unlock(&data->forks[philo->right_fork]);
    pthread_mutex_unlock(&data->forks[philo->left_fork]);
}
```

### 모니터링 함수

#### death_monitor
```c
void *death_monitor(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while (!data->someone_died && !check_all_ate(data))
    {
        i = -1;
        while (++i < data->num_of_philos && !data->someone_died)
        {
            if (check_death(data, i))
                return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}
```

## 동기화 메커니즘

### 1. 포크 접근 동기화
- 각 포크는 개별 뮤텍스로 보호됩니다.
- 철학자는 항상 왼쪽 포크를 먼저 집습니다.
- 짝수/홀수 ID에 따라 시차를 두어 교착 상태를 방지합니다.

### 2. 출력 동기화
```c
void print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->print_mutex);
    if (!data->someone_died)
        printf("%lld %d %s\n", 
            get_time() - data->start_time, id, status);
    pthread_mutex_unlock(&data->print_mutex);
}
```

### 3. 사망 상태 동기화
```c
int check_death(t_data *data, int i)
{
    pthread_mutex_lock(&data->philos[i].meal_mutex);
    if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
    {
        pthread_mutex_lock(&data->death_mutex);
        data->someone_died = 1;
        pthread_mutex_unlock(&data->death_mutex);
        pthread_mutex_lock(&data->print_mutex);
        printf("%lld %d died\n",
            get_time() - data->start_time, data->philos[i].id);
        pthread_mutex_unlock(&data->print_mutex);
        pthread_mutex_unlock(&data->philos[i].meal_mutex);
        return (1);
    }
    pthread_mutex_unlock(&data->philos[i].meal_mutex);
    return (0);
}
```

## 시간 관리

### get_time 함수
```c
long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
```

### smart_sleep 함수
```c
void smart_sleep(long long time, t_data *data)
{
    long long start;

    start = get_time();
    while (!data->someone_died)
    {
        if (get_time() - start >= time)
            break;
        usleep(500);
    }
}
```

## 메모리 관리

### 1. 할당
- 포크 뮤텍스 배열
- 철학자 구조체 배열
- 각종 뮤텍스들

### 2. 해제
```c
static void clean_program(t_data *data)
{
    int i;

    // 포크 뮤텍스 해제
    if (data->forks)
    {
        i = -1;
        while (++i < data->num_of_philos)
            pthread_mutex_destroy(&data->forks[i]);
        free(data->forks);
    }

    // 철학자 관련 메모리 해제
    if (data->philos)
    {
        i = -1;
        while (++i < data->num_of_philos)
            pthread_mutex_destroy(&data->philos[i].meal_mutex);
        free(data->philos);
    }

    // 공용 뮤텍스 해제
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
}
```

이 코드 리뷰 문서는 프로그램의 모든 주요 컴포넌트에 대한 상세한 설명을 제공합니다. 각 함수의 동작 방식, 동기화 메커니즘, 시간 관리, 메모리 관리 등이 자세히 설명되어 있습니다.
