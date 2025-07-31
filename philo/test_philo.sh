#!/bin/bash

# fuzz_simple.sh

PHILO_BIN=./philo
RUNS=10

MIN_PHILO=1
MAX_PHILO=10
MIN_TIME=100
MAX_TIME=500

for ((i = 1; i <= RUNS; i++)); do
	echo "🌀 RUN $i"

	# Generate random inputs
	num_philo=$((RANDOM % (MAX_PHILO - MIN_PHILO + 1) + MIN_PHILO))
	time_die=$((RANDOM % (MAX_TIME - MIN_TIME + 1) + MIN_TIME))
	time_eat=$((RANDOM % (MAX_TIME - MIN_TIME + 1) + MIN_TIME))
	time_sleep=$((RANDOM % (MAX_TIME - MIN_TIME + 1) + MIN_TIME))

	# Optional meals count
	if (( RANDOM % 2 == 0 )); then
		meals=$((RANDOM % 5 + 1))
		ARGS="$num_philo $time_die $time_eat $time_sleep $meals"
	else
		ARGS="$num_philo $time_die $time_eat $time_sleep"
	fi

	echo "▶️ ./philo $ARGS"

	# Run the binary and capture output
	$PHILO_BIN $ARGS > output.log 2>&1 &

	PID=$!
	TIMEOUT=3 # seconds
	sleep $TIMEOUT

	# If still running after timeout, kill it (freeze detection)
	if ps -p $PID > /dev/null; then
		echo "⛔️ Hanging... Killing process"
		kill $PID
	else
		echo "✅ Finished normally"
	fi

	# Optional: show death or final output
	if grep -q "died" output.log; then
		echo "💀 One of the philosophers died (as expected?)"
	fi

done

echo "🔁 Done $RUNS fuzz runs"
