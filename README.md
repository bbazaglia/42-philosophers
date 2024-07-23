<h1 align="center">
	🍝 Philosophers
</h1>

## 💡 About the project

This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

You can read more about processes, threads, memory, and synchronization on my Medium page: https://medium.com/@beatrizbazaglia/understanding-processes-threads-memory-and-synchronization-e57887567929

## 📝 Requirements

• One or more philosophers sit at a round table with a bowl of spaghetti in the center.

• They alternate between three states: eating, thinking, and sleeping.

• Each philosopher requires two forks to eat.

• Philosophers must not starve; they need to eat regularly.

• The simulation stops if a philosopher dies of starvation.

• They do not communicate and do not know when another philosopher is about to starve.

## 📋 Testing

To compile, go to the project path and run:

```shell
$ make 
```

Then, execute the program with the following arguments:

```shell
$ ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep]

* optional and last parameter: [number_of_times_each_philosopher_must_eat]
```

Disclaimer: The main purpose of this repository is to expose my code and help other students to understand what was done in each function. Therefore, this work should be used for academic reasons, by those who aim to learn, and not merely copy.
