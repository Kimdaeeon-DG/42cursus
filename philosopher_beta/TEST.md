# Philosophers Project - 평가 테스트 가이드

## 1. 철학자 당 하나의 스레드 확인

### 테스트 방법
1. 코드 검증:
```c
// main.c의 create_threads 함수 확인
i = -1;
while (++i < data->num_of_philos)
{
    if (pthread_create(&data->philos[i].thread, NULL,
        philosopher, &data->philos[i]))
        return (1);
}
```

2. 실행 중 스레드 확인:
```bash
# 프로그램 실행
./philo 4 800 200 200

# 별도의 터미널에서 프로세스 ID 확인
ps aux | grep philo

# 해당 프로세스의 스레드 확인
ps -M <프로세스_ID>
# 또는
top -H -p <프로세스_ID>
```

### 확인 포인트
- 각 철학자마다 별도의 스레드 ID가 할당되어 있는지 확인
- thread 수가 철학자 수와 일치하는지 확인 (모니터링 스레드 1개 추가)

## 2. 철학자 당 하나의 포크 확인

### 테스트 방법
1. 코드 검증:
```c
// init.c의 init_mutex 함수 확인
data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);

// init.c의 init_philos 함수에서 포크 할당 확인
data->philos[i].left_fork = i;
data->philos[i].right_fork = (i + 1) % data->num_of_philos;
```

2. 실행 테스트:
```bash
# 철학자 2명으로 테스트
./philo 2 800 200 200
# 포크가 2개만 있는지, 각자 하나씩만 사용하는지 확인
```

### 확인 포인트
- 포크의 개수가 철학자의 수와 정확히 일치하는지 확인
- 각 철학자가 자신의 왼쪽과 오른쪽 포크만 사용하는지 확인

## 3. 포크 당 뮤텍스 확인

### 테스트 방법
1. 코드 검증:
```c
// philo.c의 eating 함수 확인
pthread_mutex_lock(&data->forks[philo->left_fork]);
print_status(data, philo->id, "has taken a fork");
pthread_mutex_lock(&data->forks[philo->right_fork]);
print_status(data, philo->id, "has taken a fork");

// 식사 후 포크 반납
pthread_mutex_unlock(&data->forks[philo->right_fork]);
pthread_mutex_unlock(&data->forks[philo->left_fork]);
```

2. 실행 테스트:
```bash
# 철학자 3명으로 테스트하여 포크 경쟁 상황 생성
./philo 3 800 200 200
```

### 확인 포인트
- 각 포크에 대한 뮤텍스가 독립적으로 존재하는지 확인
- 포크 사용 시 항상 뮤텍스를 통한 접근이 이루어지는지 확인
- 동시에 두 철학자가 같은 포크를 사용하지 않는지 확인

## 4. 출력 스크램블 방지 확인

### 테스트 방법
1. 코드 검증:
```c
// utils.c의 print_status 함수 확인
void print_status(t_data *data, int id, char *status)
{
    pthread_mutex_lock(&data->print_mutex);
    if (!data->someone_died)
        printf("%lld %d %s\n", get_time() - data->start_time, id, status);
    pthread_mutex_unlock(&data->print_mutex);
}
```

2. 실행 테스트:
```bash
# 많은 수의 철학자로 테스트하여 출력 충돌 가능성 높이기
./philo 20 800 200 200 > output.txt
# output.txt 파일 검사
cat output.txt | grep -v "^[0-9]* [0-9]* .*$"
```

### 확인 포인트
- 모든 출력이 한 줄씩 깔끔하게 이루어지는지 확인
- 출력이 섞이거나 깨지는 현상이 없는지 확인
- 타임스탬프가 순차적으로 증가하는지 확인

## 5. 철학자 죽음 확인 및 보호

### 테스트 방법
1. 코드 검증:
```c
// monitor.c의 check_death 함수 확인
pthread_mutex_lock(&data->philos[i].meal_mutex);
if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
{
    pthread_mutex_lock(&data->death_mutex);
    data->someone_died = 1;
    pthread_mutex_unlock(&data->death_mutex);
    // ... 죽음 출력 ...
    return (1);
}
pthread_mutex_unlock(&data->philos[i].meal_mutex);

// philo.c의 eating 함수에서 식사 시간 업데이트 확인
pthread_mutex_lock(&philo->meal_mutex);
philo->last_meal_time = get_time();
pthread_mutex_unlock(&philo->meal_mutex);
```

2. 실행 테스트:
```bash
# 극단적인 시간 설정으로 테스트
./philo 4 310 300 300  # 죽음이 발생하는 상황
./philo 4 400 200 200  # 죽음이 발생하지 않는 상황
```

### 확인 포인트
- meal_mutex로 마지막 식사 시간 접근이 보호되는지 확인
- death_mutex로 죽음 상태 변경이 보호되는지 확인
- 철학자가 죽은 후 추가 식사가 발생하지 않는지 확인
- 정확한 시간에 죽음이 감지되는지 확인

### 추가 테스트 시나리오
1. 극단적인 상황 테스트:
```bash
# 매우 짧은 죽음 시간
./philo 4 100 200 200

# 매우 긴 식사/수면 시간
./philo 4 800 600 600

# 1명의 철학자
./philo 1 800 200 200

# 많은 수의 철학자
./philo 200 800 200 200
```

2. 에러 케이스 테스트:
```bash
# 잘못된 인자
./philo 0 800 200 200
./philo 4 -800 200 200
./philo 4 800 0 200
./philo 4 800 200 -200
```

각 테스트 케이스에서 프로그램이 적절히 동작하고, 모든 동기화가 올바르게 이루어지는지 확인해야 합니다.
