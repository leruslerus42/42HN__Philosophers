# Philosophers
## GENERAL
A project to learn the basics of multithreading and resource sharing.
This project is based on the "dining philosophers problem", originally formulated by Edsger Dijkstra and making a simulation about it.

![Dining_philosophers-987x1024](https://user-images.githubusercontent.com/85942176/198934151-d746832e-2ccf-499c-9ce6-af36519b5620.png)

## REQUIREMENTS
One or more philosophers sit around a round table. Each philosopher has their own place at the table with a plate and a fork on its right-hand side.
The dish served is a very difficult kind of spaghetti, that has to be eaten with two forks. 
To archieve this the philosophers have to also use the fork of their neighbor. 
As a consequence philosophers sitting next to each other can not eat simultaneously.
The philosophers are alternatively eating, sleeping or thinking. When a philosopher has finished eating, they put the forks back on the table and start sleeping. Once awake, they start thinking. The simulation stops when a philosopher dies of starvation. This should be avoided. However philosophers don’t speak with each other and don’t know if another philosopher is about to die.


## RULES
- Global variables are forbidden.
- Each philosopher has a number ranging from 1 to n, where n is the toatal number of the philosophers.
- Philosopher number 1 sits next to philosopher number n. Any other philosopher sits between philosopher number 1 and philosopher n.
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
- Each philosopher should be a thread.

## OUTPUT
Any state change of a philosopher must be formatted as follows (with "X" as the number of the philosopher and "timestamp_in_ms" as current timestamp in milliseconds):
- "timestamp_in_ms" "X" has taken a fork
- "timestamp_in_ms" "X" is eating
- "timestamp_in_ms" "X" is sleeping
- "timestamp_in_ms" "X" is thinking
- "timestamp_in_ms" "X" died

![68747470733a2f2f692e696d6775722e636f6d2f4f4668716e71772e706e67](https://user-images.githubusercontent.com/85942176/198947571-f09a347f-3ced-4d5b-880f-42781724a9bf.png)

# ARGUMENTS
Arguments
The program should take the following arguments:
- number_of_philosophers: The number of philosophers and also the number of forks.
- time_to_die: The time (in milliseconds) since the beginning of the last meal or the beginning of the simulation, after which a philosopher will die of starvation.
- time_to_eat: The time (in milliseconds) it takes for a philosopher to eat. During that time, they will need to hold two forks.
- time_to_sleep: The time a philosopher will spend sleeping.
- number_of_times_each_philosopher_must_eat(optional): If all philosophers have eaten at least "x" times, the simulation stops, otherwise when a philosopher dies.

## APPROACH
Basically every philosopher (thread) is going to executing an infinite while loop with the philosopher's routine (eat-sleep-think-repeat, as described above), until one of them dies of starvation or all of them have eaten the number of required meals.
The tricky part of this project comes with the parallelism and the use of shared resources (in this case the forks). To prevent data races the shared resources have to be protected using mutex_locks. This has to be coordinated in a way that no deadlocks can occure.

## NORMINETTE

As all other C projects at the 42 school, the code has to written in accordance with the norm:
- only 25 lines per function
- only 5 functions per file
- the only predefined functions allowed for this project are: memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock.

## RESULT 

<img width="846" alt="Screenshot 2022-11-01 at 07 15 40" src="https://user-images.githubusercontent.com/85942176/199170889-bdf34cca-c572-418c-83f3-70b55a45b89e.png">

