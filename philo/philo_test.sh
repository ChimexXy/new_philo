#!/bin/bash

# Number of fuzz runs
NUM_RUNS=50
MARGIN=10  # ms margin between death and (eat+sleep)

echo "🚀 Starting strict fuzzing mode: $NUM_RUNS runs"
echo "🧠 Detecting invalid deaths (philosophers died when they shouldn't)"

for i in $(seq 1 $NUM_RUNS); do
    PHILOS=$((RANDOM % 6 + 2))            # Between 2 and 7 philosophers
    DIE=$((RANDOM % 300 + 400))           # 400 - 699
    EAT=$((RANDOM % 100 + 100))           # 100 - 199
    SLEEP=$((RANDOM % 100 + 100))         # 100 - 199
    MEALS=$((RANDOM % 3 + 3))             # 3 - 5 meals

    CMD="./philo $PHILOS $DIE $EAT $SLEEP $MEALS"

    echo -e "\n🌀 RUN $i"
    echo "▶️ $CMD"
    OUT=$($CMD | tail -n 1)

    # Logic: if time_to_die > (eat + sleep + margin) ⇒ no one should die
    if [ $DIE -gt $(($EAT + $SLEEP + $MARGIN)) ]; then
        if echo "$OUT" | grep -q "died"; then
            echo "❌ Invalid death detected!"
            echo "❗️ $OUT"
        else
            echo "✅ Passed (no death as expected)"
        fi
    else
        echo "ℹ️ time_die too short, death allowed"
    fi
done
