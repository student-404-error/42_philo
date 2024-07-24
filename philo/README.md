# Design
- How to avoid deadlock?
- Pseudo-code
- Parsing
- Mutex Init
- Philo Init
- Implement eating
- Implement sleep
- Implement thinking
- Check_die

## How to avoid deadlock?


인자 입력받은거 파싱해서 할당해주고
각 철학자들 초기화해주고
Create thread해주고
다 초기화 되면 하나하나 thread join해주고
mutex로 포크 배열에 두개씩 잠금걸어서 막아주고


필요한 변수

- t\_philo	:	struct
	- philo\_num	:	int
	- left		:	pthread\_mutex\_t or int
	- right		:	pthread\_mutex\_t or int
	- eat\_count	:	int
	- last\_eat\_time	:	long long
	- thread	:	pthread\_t

- t\_arg	:	struct
	- num\_of\_philo	:	int
	- time\_to\_die	:	int
	- time\_to\_eat	:	int
	- time\_to\_sleep	:	int
	- num\_of\_max\_eat:	int	(optional)

- fork	:	pthread\_mutex\_t \*

---
## Pseudo-code

thread 작업 함수
{
	**여기에 deadlock 회피 알고리즘 구현**
	pthread_mutex_lock(&fork[left]);
	pthread_mutex_lock(&fork[right]);
	먹기 ms동안
	pthread_mutex_unlock(&fork[left]);
	pthread_mutex_unlock(&fork[right]);
	꿀잠 ms동안
	생각 ms동안
}

create\_philo
{
	philo.philo_num = i
	philo.left = fork[i]
	philo.right = fork[(i + 1) % arg->num_of_philo]
	philo.eat_count = arg->eat_count or -1
	philo.last_eat_time = 0
	pthread_create(&thread, NULL, thread 작업 함수, philo[i])
}

create\_t\_arg
{
	already impliment
}

